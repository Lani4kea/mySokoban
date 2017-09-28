/************************************************
 * @author : Maret Kilian
 * @date : 28/09/2017
 * @
 ***********************************************/
#ifndef LEVELENTITIES_H_INCLUDED
#define LEVELENTITIES_H_INCLUDED

typedef enum { false, true } bool;

struct Bloc{
    const int id = 0;
    int xPos = 0;
    int yPos = 0;
    bool isMovable = false;
    bool isPlayer = false;
    const char asciiTexture = ' ';
};

struct Level{
    const char* levelName;
    const int matrixWidth = 0;
    const int matrixHeight = 0;
    Bloc** matrix;
};

#endif // LEVELENTITIES_H_INCLUDED
