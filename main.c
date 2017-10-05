#include <stdio.h>
#include <stdlib.h>

#include "headers/LevelEntities.h"
#include "headers/LevelActions.h"
#include "headers/LevelDrawer.h"
#include "headers/MenuDisplay.h"
#include "headers/shared.h"

Level* lvl;

int main()
{

    lvl = create_Level("Level 1", 11,19,6);

    int elems[209] =   {0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
                        0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
                        0,0,0,0,1,2,0,0,1,0,0,0,0,0,0,0,0,0,0,
                        0,0,1,1,1,0,0,2,1,1,0,0,0,0,0,0,0,0,0,
                        0,0,1,0,0,2,0,2,0,1,0,0,0,0,0,0,0,0,0,
                        1,1,1,0,1,0,1,1,0,1,0,0,0,1,1,1,1,1,1,
                        1,0,0,0,1,0,1,1,0,1,1,1,1,1,0,0,4,4,1,
                        1,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,4,4,1,
                        1,1,1,1,1,0,1,1,1,0,1,5,1,1,0,0,4,4,1,
                        0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
                        0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0};

    init_Matrix(lvl);
    int nbBoxes = 0;

    for(size_t i = 0; i < lvl->matrixHeight; ++i){
        for(size_t j = 0; j < lvl->matrixWidth; ++j){
            lvl->matrix[i][j] = create_Bloc((BlocType)elems[i*19 + j], i, j);
            if(elems[i*19 + j] == 2 || elems[i*19 + j] == 3){
                lvl->boxIndices[i] = create_Position(i,j);
            }
            if(elems[i*19 + j] == 2 || elems[i*19 + j] == 3){
                lvl->boxIndices[nbBoxes] = create_Position(i,j);
                ++nbBoxes;
            }
            if(elems[i*19 + j] == 5){
                lvl->player = lvl->matrix[i][j];
                definePlayer(lvl->player);
            }
        }
    }
    updateMatrix();

    Bloc * playerBloc = lvl->matrix[6][2];

    bool isGameWon = false;

    while(!isGameWon){

        updateMatrix();
        ASCIIDrawLevel();

        unsigned char nextCharMove = 255;
        scanf("%c", &nextCharMove);

        if(nextCharMove != 255){

            Movement myMove = ERROR;

            switch(nextCharMove){
                case 'z':
                case 'Z':
                    myMove = UP;
                    break;
                case 'q':
                case 'Q':
                    myMove = LEFT;
                    break;
                case 's':
                case 'S':
                    myMove = DOWN;
                    break;
                case 'd':
                case 'D':
                    myMove = RIGHT;
                    break;
                case 'e':
                case 'E':
                    isGameWon = true;
                    break;
                default:
                    break;
            }
            if(myMove != ERROR){
                bool res = movePlayer(&myMove, lvl->player);
            }
        }
    }
}
