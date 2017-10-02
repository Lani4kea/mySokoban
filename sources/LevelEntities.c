#include "../headers/LevelEntities.h"

Bloc* create_Bloc(int id, int x, int y) {
  Bloc* b = malloc(sizeof(Bloc));
  Position pos = Position();
  pos.x = x;
  pos.y = y;
  b->id = id;
  b->pos = pos;

  switch(id){
    case 0:
        b->isMovable = false;
        b->isPlayer = false;
        b->asciiTexture = ' ';
        break;
    case 1:
        b->isMovable = false;
        b->isPlayer = false;
        b->asciiTexture = ' ';
        break;
    case 4:
        b->isMovable = false;
        b->isPlayer = false;
        b->asciiTexture = ' ';
        break;
    case 2:
        b->isMovable = true;
        b->isPlayer = false;
        b->asciiTexture = ' ';
        break;
    case 3:
        b->isMovable = true;
        b->isPlayer = false;
        b->asciiTexture = ' ';
        break;
    case 5:
        b->isMovable = true;
        b->isPlayer = true;
        b->asciiTexture = ' ';
        break;
    case 6:
        b->isMovable = true;
        b->isPlayer = true;
        b->asciiTexture = ' ';
        break;
    default:
        b = NULL;
  }

  return b;
}

void destroy_Bloc(Bloc* b){
    b->pos = NULL;
    free((void*)b);
}
