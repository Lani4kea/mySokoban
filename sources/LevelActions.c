#include <stdlib.h>
#include <stdio.h>
#include "LevelAction.h"

/*
 * Steps to execute for every move of the player :
 *  - 1) Check the bloc's type (either 5 or 6)
 *  - 2) Check the type of bloc where the player wants to go
 *      --> If bloc.id = 0 ==> Old bloc.id = 0/4, new bloc.id = 5 (player)
 *      --> If bloc.id = 1 ==> Movement impossible
 *      --> If bloc.id = 2 ==> Check for the type of bloc next to the box (same direction)
 *          --> If bloc.id = 1, 2, 3 ==> Movement impossible
 *          --> If bloc.id = 0 ==> Old bloc.id = 0, new bloc.id = 5, new bloc+1.id = 2
 *          --> If bloc.id = 4 ==> Old bloc.id = 0, new bloc.id = 5, new bloc+1.id = 3
 *      --> If bloc.id = 3 ==> Check for the type of bloc next to the box (same direction)
 *          --> If bloc.id = 1, 2, 3 ==> Movement impossible
 *          --> If bloc.id = 0 ==> Old bloc.id = 0, new bloc.id = 6, new bloc+1.id = 2
 *          --> If bloc.id = 4 ==> Old bloc.id = 0, new bloc.id = 6, new bloc+1.id = 3
 *      --> If bloc.id = 4 ==> Old bloc.id = 0/4, new bloc.id = 6 (player)
 *      --> If bloc.id = 5 or 6 ==> There might be a problem ?
 */
int movePlayer(Level &level, Movement &mov, Bloc &oldBloc){

    Bloc * newBloc = NULL;        // This bloc refers to the bloc where the player should be after the move
    Bloc * nextNewBloc = NULL;    // This bloc is next to the future position of the player (if he moves a box for example)
    int res = 0;

    res = checkValidMove(level, mov, oldBloc);

    if(res){
        // the adjacent blocs are stored according to the next move
        switch(mov){
            case UP:
                newBloc = &(level.matrix[oldBloc.pos.x][oldBloc.pos.y-1]);
                nextNewBloc = (res == 2) ? &(level.matrix[oldBloc.pos.x][oldBloc.pos.y-2]) : NULL;
                break;
            case DOWN:
                newBloc = &(level.matrix[oldBloc.pos.x][oldBloc.pos.y+1]);
                nextNewBloc = (res == 2) ? &(level.matrix[oldBloc.pos.x][oldBloc.pos.y+2]) : NULL;
                break;
            case LEFT:
                newBloc = &(level.matrix[oldBloc.pos.x-2][oldBloc.pos.y]);
                nextNewBloc = (res == 2) ? &(level.matrix[oldBloc.pos.x-2][oldBloc.pos.y]) : NULL;
                break;
            case RIGHT:
                newBloc = &(level.matrix[oldBloc.pos.x+1][oldBloc.pos.y]);
                nextNewBloc = (res == 2) ? &(level.matrix[oldBloc.pos.x+2][oldBloc.pos.y]) : NULL;
                break;
            default:
                return 0;
        }


        // If oldBloc.id == 5, the current bloc to move is a player
        // we already checked if the movement was valid, therefore, we don't need further verification
        if(oldBloc.id == 5){

            switch(newBloc.id){
                case 0: swapBlocs(level, oldBloc.pos, mov);
                    break;
                case 2:
                case 3:
                case 4:
                default :

            }


        // If oldBloc.id == 6, the current bloc to move is a player on a "goal" bloc
        }else if(oldBloc.id == 6){

        // Else, the current bloc is not a player bloc and therefore can't move directly
        }else{
            return 0;
        }
    }
}
// NON FORMAL DOCUMENTATION
// return a value depending of the type of bloc being moved :
// return 0 if the move is not valid (id == 1 or something preventing a box move)
// return 1 if the player move on an empty case / goal case (id == 0 || id == 4)
// return 2 if the player push a box / placed box (id == 2 || id == 3)
int checkValidMove(Level &level, Movement &mov, Bloc &blocToMove){


    int &x = blocToMove.pos.x;
    int &y = blocToMove.pos.y;

    switch(mov){
        case UP:

            if(!y){
                return 0;
            }

            if(level.matrix[x][y-1].id == 1){
                return 0;
            }

            if(level.matrix[x][y-1] == 2 ||
               level.matrix[x][y-1] == 3 ){

                if(!(y-1)){
                    return 0;
                }

                if(level.matrix[x][y-2] >= 1 ||
                   level.matrix[x][y-2] <= 3 ){
                    return 0;
                }
                return 2;
            }

            return 1;
        case DOWN:

            if(!(y == level.matrixHeight - 1)){
                return 0;
            }

            if(level.matrix[x][y+1].id == 1){
                return 0;
            }

            if(level.matrix[x][y+1] == 2 ||
               level.matrix[x][y+1] == 3 ){

                if(!(y+1 == level.matrixHeight - 1)){
                    return 0;
                }

                if(level.matrix[x][y+2] >= 1 ||
                   level.matrix[x][y+2] <= 3 ){
                    return 0;
                }
                return 2;
            }

            return 1;
        case LEFT:

            if(!x){
                return 0;
            }

            if(level.matrix[x-1][y].id == 1){
                return 0;
            }

            if(level.matrix[x-1][y] == 2 ||
               level.matrix[x-1][y] == 3 ){

                if(!(x-1)){
                    return 0;
                }

                if(level.matrix[x-2][y] >= 1 ||
                   level.matrix[x-2][y] <= 3 ){
                    return 0;
                }
                return 2;
            }

            return 1;
        case RIGHT:

            if(!(x == level.matrixWidth - 1)){
                return 0;
            }

            if(level.matrix[x+1][y].id == 1){
                return 0;
            }

            if(level.matrix[x+1][y] == 2 ||
               level.matrix[x+1][y] == 3 ){

                if(!(x+1 == level.matrixWidth - 1)){
                    return 0;
                }

                if(level.matrix[x+2][y] >= 1 ||
                   level.matrix[x+2][y] <= 3 ){
                    return 0;
                }
                return 2;
            }

            return 1;
        default:
            return 0;
    }
}

// this function swaps two blocs in a level based on their position
int swapBlocs(Level &level, Position &oldPos, const Movement &mov){

    Position newPos = oldPos;

    switch(mov){
        case UP: --newPos.y;
            break;
        case DOWN: ++newPos.y;
            break;
        case LEFT: --newPos.x;
            break;
        case RIGHT: ++newPos.x;
            break;
        default: return 0;
    }

    if(oldPos.x < 0 || oldPos.y < 0 || newPos.x < 0 || newPos.y < 0 ||
       oldPos.x >= level.matrixWidth || oldPos.y >= level.matrixWidth ||
       newPos.x >= level.matrixWidth || newPos.y >= level.matrixWidth){

       return 0;

    }

    Bloc tempBloc = level.matrix[oldPos.x][oldPos.y];
    level.matrix[oldPos.x][oldPos.y] = level.matrix[newPos.x][newPos.y];
    level.matrix[newPos.x][newPos.y] = tempBloc;

    Position tempPos = level.matrix[oldPos.x][oldPos.y].pos;
    level.matrix[oldPos.x][oldPos.y].pos = newPos;
    level.matrix[newPos.x][newPos.y].pos = tempPos;
}

int pushBox(Level &level, Position &playerPos, Position &oldBlocPos, Position &newBlocPos, const Movement &mov){

    Position oldBlocPos = playerPos;
    Position newBlocPos = playerPos;

    switch(mov){
        case UP:
            oldBlocPos.y -= 1;
            newBlocPos.y -= 2;
            break;
        case DOWN:
            oldBlocPos.y += 1;
            newBlocPos.y += 2;
            break;
        case LEFT:
            oldBlocPos.x -= 1;
            newBlocPos.x -= 2;
            break;
        case RIGHT:
            oldBlocPos.x += 1;
            newBlocPos.x += 2;
            break;
        default: return 0;
    }

    if(oldPos.x < 0 || oldPos.y < 0 || newPos.x < 0 || newPos.y < 0 ||
       playerPos.x  >= level.matrixWidth || playerPos.y  >= level.matrixWidth ||
       oldBlocPos.x >= level.matrixWidth || oldBlocPos.y >= level.matrixWidth ||
       newBlocPos.x >= level.matrixWidth || newBlocPos.y >= level.matrixWidth){

       return 0;

    }

    if(level.matrix[playerPos.x][playerPos.y].id == 5){

        level.matrix[playerPos.x][playerPos.y] = *create_Bloc(0, playerPos.x, playerPos.y);

    }else if(level.matrix[playerPos.x][playerPos.y].id == 6){



    }else{
        return 0;
    }

}
