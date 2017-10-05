#ifndef TESTFUNCTIONS_H_INCLUDED
#define TESTFUNCTIONS_H_INCLUDED

#include "../headers/LevelEntities.h"

typedef enum TestFail{
    POSITION_ERROR,
    IS_PLAYER_ERROR,
    IS_MOVABLE_ERROR,
    MOVEMENT_ERROR,
    TRANSFORMATION_ERROR,
    LEVEL_MATRIX_ERROR
} TestFail;

void DEBUG_PRINT_ERROR(const TestFail msg, const Level *lvl, const int x, const int y, const Bloc *bloc);
int checkBlocProperties(const Level *lvl);

#endif // TESTFUNCTIONS_H_INCLUDED
