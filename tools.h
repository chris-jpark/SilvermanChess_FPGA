#ifndef TOOLS_H
#define TOOLS_H 

#include <stdbool.h>

#define PAWN = 0
#define ROOK = 1
#define QUEEN = 2
#define KING = 3

#define ABS(x) (((x) > 0) ? (x) : -(x))

/* Screen size. */
#define RESOLUTION_X 320
#define RESOLUTION_Y 240
#define BOARD_DIMENSION 4
#define OFFSET 40


volatile int pixel_buffer_start; // global variable

typedef struct Coordinates{
    int x;
    int y;
} Coordinates;


typedef struct Piece{
    int _id;
    bool isWhite; 
    uint16_t image[60][60];
    bool isEmpty;
    Coordinates coords; 
} Piece;

Piece getPiece(Coordinates coords, const Piece **gameBoard);

#endif