#include "LevelEntities.h"

#ifndef LEVELACTIONS_H_INCLUDED
#define LEVELACTIONS_H_INCLUDED

bool movePlayer(Movement *mov, Bloc *oldBloc);
bool checkValidMove(Level *level, Movement *mov, Bloc *blocToMove);
int swapBlocs(Level *level, Position oldPos, const Movement *mov);

#endif // LEVELACTIONS_H_INCLUDED
