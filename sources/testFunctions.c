#include <stdlib.h>
#include <stdio.h>
#include "../headers/testFunctions.h"
#include "../headers/LevelEntities.h"

void DEBUG_PRINT_ERROR(const TestFail &msg, const Level &lvl, const int x, const int y, const Bloc &bloc){
    switch(msg){
        case POSITION_ERROR:
            printf("Position error at [%d][%d] : \n expected %d and %d \ngot %d, and %d", x, y, x, y, bloc.pos.x, bloc.pos.y);
            break;
        case IS_PLAYER_ERROR:
            printf("Bloc property error at [%d][%d] : \n Bloc type: %d \n expected bloc.isPlayer = %s \n got bloc.isPlayer = %s", x, y, bloc.id, !bloc.id ? "true" : "false" , bloc.id ? "true" : "false");
            break;
        case IS_MOVABLE_ERROR:
            break;
        case MOVEMENT_ERROR:
            break;
        case TRANSFORMATION_ERROR:
            break;
        case LEVEL_MATRIX_ERROR:
            break;
        default:
            printf("unknown error");
    }
}

int checkBlocProperties(const Level &lvl){
    for(size_t i = 0; i < lvl.matrixWidth; ++i){
        for(size_t j = 0; j < lvl.matrixWidth; ++j){

            Bloc curBloc = lvl.matrix[i][j];

            if(curBloc.pos.x != i || curBloc.pos.y != j){
                return 0;
            }

            switch(curBloc.id){
                case 0:
                case 1:
                case 4:
                    if(curBloc.isMovable){
                        return 0;
                    }
                    if(curBloc.isPlayer){
                        return 0;
                    }
                    break;
                case 2:
                case 3:
                    if(!curBloc.isMovable){
                        return 0;
                    }
                    if(curBloc.isPlayer){
                        return 0;
                    }
                    break;
                case 5:
                case 6:
                    if(!curBloc.isMovable){
                        return 0;
                    }
                    if(!curBloc.isPlayer){
                        return 0;
                    }
                    break;
                default:
                    return 0;
            }

        }
    }
    return 1;
}
