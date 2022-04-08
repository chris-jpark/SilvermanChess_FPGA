#include "address_map_arm.h"
#include "images.h"
#include <stdbool.h>

#define PAWN = 0
#define ROOK = 1
#define QUEEN = 2
#define KING = 3


struct pair {
    int first;
    int second;
};

struct piece{
    int _id;
    struct pair *next_moves;
    bool isWhite; 
};

struct piece basemap[4][4];
 


