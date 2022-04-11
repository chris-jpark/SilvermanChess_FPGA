#ifndef TOOLS_H
#define TOOLS_H 

#define PAWN = 0
#define ROOK = 1
#define QUEEN = 2
#define KING = 3

#define ABS(x) (((x) > 0) ? (x) : -(x))

/* Screen size. */
#define RESOLUTION_X 320
#define RESOLUTION_Y 240

#include <stdbool.h>

volatile int pixel_buffer_start; // global variable

struct pair {
    int first;
    int second;
};

struct piece{
    int _id;
    bool isWhite; 
    uint16_t image[60][60];
};

#endif