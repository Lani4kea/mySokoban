#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/LevelActions.h"
#include "../headers/shared.h"

int movePlayer(Movement* mov, Bloc* player){

    int res = checkValidMove(lvl, mov, player); // at this point, we know if the next move is valid. No need for further verif
    if(res){

        Bloc* nextBloc      = calloc(1,sizeof(Bloc));   // the bloc adjacent to the current one being moved in the direction
                                                        // of the movement (n+1)
        Bloc* nextBlocN2    = calloc(1,sizeof(Bloc));   // the bloc adjacent to the previous bloc (n+2)
        const Position pos  = player->pos;

        switch(*mov){

            case UP:

                nextBloc    = lvl->matrix[pos.x-1][pos.y];
                nextBlocN2  = !(pos.x-1) ? NULL : lvl->matrix[pos.x-2][pos.y];

                break;
            case DOWN:

                nextBloc    = lvl->matrix[pos.x+1][pos.y];
                nextBlocN2  = (pos.x+1 == lvl->matrixHeight - 1) ? NULL : lvl->matrix[pos.x+2][pos.y];

                break;
            case LEFT:

                nextBloc    = lvl->matrix[pos.x][pos.y-1];
                nextBlocN2  = !(pos.y-1) ? NULL : lvl->matrix[pos.x][pos.y-2];

                break;
            case RIGHT:

                nextBloc    = lvl->matrix[pos.x][pos.y+1];
                nextBlocN2  = (pos.y+1 == lvl->matrixWidth - 1) ? NULL : lvl->matrix[pos.x][pos.y+2];

                break;
            default:
                return 0;
        }

        switch(nextBloc->curValue){
            case FLOOR:

                nextBloc->curValue = PLAYER;
                player->curValue = player->baseValue;
                break;

            case BOX:

                if(nextBlocN2->curValue == FLOOR){

                    nextBlocN2->curValue = BOX;

                }else{

                    nextBlocN2->curValue = BOX_ON_GOAL;

                }

                nextBloc->curValue = PLAYER;
                player->curValue = player->baseValue;

                for(size_t i = 0; i < lvl->nbBoxes; ++i){
                    if(lvl->boxIndices[i]->x == nextBloc->pos.x && lvl->boxIndices[i]->y == nextBloc->pos.y){
                        lvl->boxIndices[i] = &nextBlocN2->pos;
                        break;
                    }
                }

                break;

            case BOX_ON_GOAL:

                if(nextBlocN2->curValue == FLOOR){

                    nextBlocN2->curValue = BOX;

                }else{

                    nextBlocN2->curValue = BOX_ON_GOAL;

                }

                nextBloc->curValue = PLAYER_ON_GOAL;
                player->curValue = player->baseValue;

                for(size_t i = 0; i < lvl->nbBoxes; ++i){
                    if(lvl->boxIndices[i]->x == nextBloc->pos.x && lvl->boxIndices[i]->y == nextBloc->pos.y){
                        lvl->boxIndices[i] = &nextBlocN2->pos;
                        break;
                    }
                }

                break;

            case GOAL:

                nextBloc->curValue = PLAYER_ON_GOAL;
                player->curValue = player->baseValue;
                break;

            default:
                return 0;
        }
    }
    return res;
}

int checkValidMove(Level* lvl, Movement* mov, Bloc* blocToMove){

    Bloc* nextBloc      = calloc(1,sizeof(Bloc));       // the bloc adjacent to the current one being moved in the direction
                                                        // of the movement (n+1)
    Bloc* nextBlocN2    = calloc(1,sizeof(Bloc));       // the bloc adjacent to the previous bloc (n+2)
    const Position pos  = blocToMove->pos;

    switch(*mov){
        case UP:

            if(!pos.x) return 0;

            nextBloc    = lvl->matrix[pos.x-1][pos.y];
            nextBlocN2  = !(pos.x-1) ? NULL : lvl->matrix[pos.x-2][pos.y];
            break;

        case DOWN:

            if(pos.x == lvl->matrixHeight - 1) return 0;

            nextBloc    = lvl->matrix[pos.x+1][pos.y];
            nextBlocN2  = (pos.x+1 == lvl->matrixHeight - 1) ? NULL : lvl->matrix[pos.x+2][pos.y];
            break;

        case LEFT:

            if(!pos.y) return 0;

            nextBloc    = lvl->matrix[pos.x][pos.y-1];
            nextBlocN2  = !(pos.y-1) ? NULL : lvl->matrix[pos.x][pos.y-2];
            break;

        case RIGHT:

            if(pos.y == lvl->matrixWidth - 1) return 0;

            nextBloc    = lvl->matrix[pos.x][pos.y+1];
            nextBlocN2  = (pos.y+1 == lvl->matrixWidth - 1) ? NULL : lvl->matrix[pos.x][pos.y+2];
            break;

        default:
            return 0;
    }

    if(!nextBloc->canBeActive) return 0;    // if the next bloc is a wall

    if(nextBloc->curValue == BOX || nextBloc->curValue == BOX_ON_GOAL){     // if the next bloc is a box

        if(nextBlocN2 == NULL || !nextBlocN2->canBeActive || nextBlocN2->curValue == BOX || nextBlocN2->curValue == BOX_ON_GOAL) return 0; // if the n+2 bloc can't be moved

    }

    return 1;
}

Level* create_Level(const char* levelName, const int matrixHeight, const int matrixWidth, const int nbBoxes){
    Level level = {.levelName = levelName, .matrixHeight = matrixHeight, .matrixWidth = matrixWidth, .nbBoxes = nbBoxes};
    lvl = malloc(sizeof *lvl);

    if (lvl == NULL) abort();
    memcpy(lvl, &level, sizeof *lvl);

    return lvl;
}
void destroy_Level(Level* level);
