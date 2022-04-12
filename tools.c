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

void makeBoard(Piece **gameBoard) {
    for(int row = 0; row < BOARD_DIMENSION; row++) {
        for(int col = 0; col < BOARD_DIMENSION; col++) {
            if(row < 2) {
                gameBoard[row][col].isWhite = false;
                //pawns
                if(row == 1) {
                    gameBoard[row][col]._id = 0; 
                    strcpy(gameBoard[row][col].name, "bP"); //strcpy( a, "foo" );
                } else {
                    gameBoard[row][col]._id = col + 1;
                    if(col == 0 || col == 3){
                        strcpy(gameBoard[row][col].name ,"bR"); 
                    }
                    else if(col == 1){   
                        strcpy(gameBoard[row][col].name ,"bQ"); 
                    }
                    else if(col == 2){ 
                        strcpy(gameBoard[row][col].name ,"bK"); 
                    }
                }
            //if row >= 2
            } else {
                gameBoard[row][col].isWhite = true;
                //pawns
                if(row == 2) {
                    gameBoard[row][col]._id = 0; 
                    strcpy(gameBoard[row][col].name ,"wP"); 
                } else {
                    gameBoard[row][col]._id = col + 1;
                    if(col == 0 || col == 3)
                        strcpy(gameBoard[row][col].name ,"wR"); 
                    else if(col == 1)
                        strcpy(gameBoard[row][col].name ,"wQ"); 
                    else if(col == 2)
                        strcpy(gameBoard[row][col].name ,"wK"); 
                }
            }
            Coordinates currCoords = {row, col};
            gameBoard[row][col].coords = currCoords;
            gameBoard[row][col].isEmpty = false; 
        }
    }
}