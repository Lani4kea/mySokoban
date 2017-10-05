#ifndef LEVELDRAWER_H_INCLUDED
#define LEVELDRAWER_H_INCLUDED

#include "LevelEntities.h"

void updateMatrix();
void findPlayer(Bloc *player);
void const ASCIIDrawLevel();
char const idToASCIIValue(BlocType bt);

#endif // LEVELDRAWER_H_INCLUDED
