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

bool definePlayer(Bloc* player){

    if(player->baseValue == GOAL){

        player->curValue = PLAYER_ON_GOAL;

    }else if(player->baseValue == FLOOR){

        player->curValue = PLAYER;

    }else{

        return false;

    }
    return true;
}

void init_Matrix(){

    lvl->matrix = calloc(lvl->matrixWidth ,sizeof(Bloc*));
    Bloc  *b    = calloc(lvl->matrixWidth * lvl->matrixHeight ,sizeof(Bloc));

    for (int i = 0; i < lvl->matrixHeight; i++){
        lvl->matrix[i] = &b[i * lvl->matrixWidth];
    }

    lvl->boxIndices = calloc(lvl->nbBoxes ,sizeof(Position));
}
