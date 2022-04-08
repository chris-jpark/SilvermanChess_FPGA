#include "address_map_arm.h"
#DEFINE PAWN = 0
#DEFINE ROOK = 1
#DEFINE QUEEN = 2
#DEFINE KING = 3
piece  basemap[4][4];
 
struct piece{
    int _id;
    pair *next_moves;
    bool isWhite; 
}

struct pair {
    int first;
    int second;
}

