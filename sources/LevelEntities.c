#include <stdlib.h>
#include "../headers/LevelEntities.h"
#include "../headers/shared.h"

Position* create_Position(int x, int y){

    Position* p = malloc(sizeof(Position));

    p->x = x;
    p->y = y;

    return p;
}

void destroy_Position(Position* p){
    p = NULL;
    free(p);
}

Bloc* create_Bloc(BlocType bbt, int x, int y) {

  Bloc* b = malloc(sizeof(Bloc));

  Position pos = {.x = x, .y = y};
  b->pos = pos;

  if(bbt == WALL){
    b->canBeActive = false;
    b->baseValue = 1;
    b->curValue = 1;
  }else if(bbt == GOAL){
    b->canBeActive = true;
    b->baseValue = 4;
    b->curValue = 4;
  }else{
    b->canBeActive = true;
    b->baseValue = 0;
    b->curValue = 0;
  }
  return b;
}

void destroy_Bloc(Bloc* b){
    b = NULL;
    free(b);
}

void definePlayer(Bloc* player){
    if(player->baseValue == 4){
        player->curValue = 6;
    }else{
        player->curValue = 5;
    }
}

void init_Matrix(){
    //lvl->matrix = (Bloc***)malloc(lvl->matrixHeight * lvl->matrixWidth * sizeof(Bloc));

    lvl->matrix = calloc(lvl->matrixWidth ,sizeof(Bloc*));
    Bloc  *b = calloc(lvl->matrixWidth * lvl->matrixHeight ,sizeof(Bloc));

    for (int i = 0; i < lvl->matrixWidth; i++){
        lvl->matrix[i] = &b[i * lvl->matrixHeight];
    }

    lvl->boxIndices = calloc(lvl->nbBoxes ,sizeof(Position));

    /*for (int i = 0; i < lvl->matrixWidth; i++)
        for (int j = 0; j < lvl->matrixHeight; j++)
            a[i][j] = 0;*/

    /*free(b);
    free(a);*/
}
