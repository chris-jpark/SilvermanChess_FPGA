#include "tools.h"

Piece getPiece(Coordinates coords, const Piece **gameBoard) {
    float gridParam = RESOLUTION_Y/BOARD_DIMENSION;

    Piece invalidClick;

    if((coords.x - OFFSET)> RESOLUTION_X || coords.y > RESOLUTION_Y || (coords.x - OFFSET) < 0 || coords.y < 0) {
        invalidClick.isEmpty = true;
        return invalidClick;
    }

    int xIndex = coords.x/gridParam;
    int yIndex = coords.y/gridParam;

    return gameBoard[xIndex][yIndex];

}