/**************************************************************************************************
 * \brief   The different entities and "objects" (struct) presents in the game
 *
 *          This file contains the definitions of the different structs and
 *          enums used in the game.
 * \author  Maret Kilian, Hugo Patin
 * \date    28/09/2017
 * @
 *************************************************************************************************/
#ifndef LEVELENTITIES_H_INCLUDED
#define LEVELENTITIES_H_INCLUDED

typedef enum { false, true } bool;
typedef enum Movement { UP, DOWN, LEFT, RIGHT } Movement;

typedef struct Position{
    int x;
    int y;
} Position;

typedef struct Bloc{
    int id;
    Position pos;
    bool isMovable;
    bool isPlayer;
    char asciiTexture;
} Bloc;

Bloc* create_Bloc(int id, int x, int y);
void destroy_Bloc(Bloc* b);

typedef struct Level{
    const char* levelName;
    const int matrixWidth;
    const int matrixHeight;
    Bloc** matrix;
} Level;

#endif // LEVELENTITIES_H_INCLUDED
