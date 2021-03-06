#include <stdlib.h>
#include <stdio.h>
#include "../headers/LevelDrawer.h"
#include "../headers/shared.h"


void updateMatrix(){

    for(size_t i = 0; i < lvl->matrixHeight; ++i){
        for(size_t j = 0; j < lvl->matrixWidth; ++j){
            lvl->matrix[i][j]->pos.x = i;
            lvl->matrix[i][j]->pos.y = j;
            if(lvl->matrix[i][j]->curValue == PLAYER || lvl->matrix[i][j]->curValue == PLAYER_ON_GOAL){
                lvl->player = lvl->matrix[i][j];
            }
        }
    }

    for(size_t i = 0; i < lvl->nbBoxes; ++i){
        Position * curPos = lvl->boxIndices[i];
        if(curPos != NULL){
            if(lvl->matrix[curPos->x][curPos->y]->baseValue == FLOOR){
                lvl->matrix[curPos->x][curPos->y]->curValue = BOX;
            }else if(lvl->matrix[curPos->x][curPos->y]->baseValue == GOAL){
                lvl->matrix[curPos->x][curPos->y]->curValue = BOX_ON_GOAL;
            }else{
                printf("Error while updating the matrix");
            }
        }else{
            printf("Error while updating the matrix : NULL Position in array");
            return;
        }
    }

}

void const ASCIIDrawLevel(){
    char * str = calloc(lvl->matrixWidth, sizeof(char));
    for(size_t i = 0; i < lvl->matrixHeight; ++i){
        for(size_t j = 0; j < lvl->matrixWidth; ++j){
            str[j] = idToASCIIValue(lvl->matrix[i][j]->curValue);
        }
        printf("%s\n", str);
    }
}

char const idToASCIIValue(BlocType bt){
    switch(bt){
        case FLOOR: return ' ';
        case WALL : return 178;
        case BOX: return 254;
        case BOX_ON_GOAL : return 176;
        case GOAL : return 43;
        case PLAYER: return 94;
        case PLAYER_ON_GOAL: return 226;
        default: return '#';
    }
    return '#';
}
