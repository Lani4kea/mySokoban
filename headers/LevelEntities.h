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
typedef enum BlocType{ FLOOR, WALL, BOX, BOX_ON_GOAL, GOAL, PLAYER, PLAYER_ON_GOAL } BlocType;
typedef enum Movement { UP, DOWN, LEFT, RIGHT, ERROR } Movement;

typedef struct Position{
    int x;
    int y;
} Position;

Position* create_Position(int x, int y);
void destroy_Position(Position* p);

typedef struct Bloc{
    Position pos;
    bool canBeActive;
    BlocType baseValue;
    BlocType curValue;
} Bloc;

Bloc* create_Bloc(BlocType bbt, int x, int y);
void destroy_Bloc(Bloc* b);

typedef struct Level{
    const char* levelName;
    const int   matrixWidth;
    const int   matrixHeight;
    const int   nbBoxes;
    Bloc***     matrix;
    Position**   boxIndices;
    Bloc*       player;
} Level;

void init_Matrix();
void definePlayer(Bloc* player);
Level* create_Level(const char* levelName, const int matrixHeight, const int matrixWidth, const int nbBoxes);
void destroy_Level(Level* lvl);

/*
typedef struct Bloc{
    int id;
    Position pos;
    bool isMovable;
    bool isPlayer;
    char asciiTexture;
} Bloc;
Bloc* create_Bloc(int id, int x, int y);
void destroy_Bloc(Bloc* b);*/

#endif // LEVELENTITIES_H_INCLUDED
