#ifndef tools.h
#define tools.h 

#define PAWN = 0
#define ROOK = 1
#define QUEEN = 2
#define KING = 3

#define ABS(x) (((x) > 0) ? (x) : -(x))

/* Screen size. */
#define RESOLUTION_X 320
#define RESOLUTION_Y 240

volatile int pixel_buffer_start; // global variable

struct pair {
    int first;
    int second;
};

struct piece{
    int _id;
    bool isWhite; 
};

#endif