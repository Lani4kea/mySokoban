#include "LevelEntities.h"

#ifndef LEVELACTIONS_H_INCLUDED
#define LEVELACTIONS_H_INCLUDED

int checkValidMove(Level *level, Movement *mov, Bloc *blocToMove);
int swapBlocs(Level *level, Position oldPos, const Movement *mov);
int pushBox(Level *level, Position playerPos, const Movement *mov);

#endif // LEVELACTIONS_H_INCLUDED
