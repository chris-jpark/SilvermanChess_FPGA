/* This file is a tester - for using an online compiler when the hardware is inaccessible 
The online compiler cannot do multiple file compilation, and so all files are
cumbersomely merged in this file for quick testing.
### NOT NEEDED FOR PROJECT COMPILATION ###*/

/* Screen size. */
#define RESOLUTION_X 320
#define RESOLUTION_Y 240
#define BOARD_DIMENSION 4
#define OFFSET 40

#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <math.h> 

typedef struct pair {
    int first;
    int second;
}Pair;

typedef struct Coordinates{
    int x;
    int y;
} Coordinates;

typedef struct Piece{
    int _id;
    bool isWhite; 
    char name[2];
   // Coordinates coords; 
} Piece;

typedef struct mapSpot{
	Piece piece;
	int possMoves[16]; 
	bool isEmpty;
} mapSpot;

mapSpot basemap[4][4];
Pair startPos; 
Pair endPos; 
bool whiteTurn = true; 

void makeBoard() {
    for(int col = 0; col < BOARD_DIMENSION; col++) {
        for(int row = 0; row < BOARD_DIMENSION; row++) {
            if(row < 2) {
                basemap[col][row].piece.isWhite = false;
                //pawns
                if(row == 1) {
                    basemap[col][row].piece._id = 0; 
                    strcpy(basemap[col][row].piece.name, "bP"); //strcpy( a, "foo" );
                } else {
                    basemap[col][row].piece._id =  col + 1;
                    if(col == 0 || col == 3){
                        strcpy(basemap[col][row].piece.name ,"bR"); 
                    }
                    else if(col == 1){   
                        strcpy(basemap[col][row].piece.name ,"bQ"); 
                    }
                    else if(col == 2){ 
                        strcpy(basemap[col][row].piece.name ,"bK"); 
                    }
                }
            //if row >= 2
            } else {
                basemap[col][row].piece.isWhite = true;
                //pawns
                if(row == 2) {
                    basemap[col][row].piece._id = 0; 
                    strcpy(basemap[col][row].piece.name ,"wP"); 
                } else {
                    basemap[col][row].piece._id = col + 1;
                    if(col == 0 || col == 3)
                        strcpy(basemap[col][row].piece.name ,"wR"); 
                    else if(col == 1)
                        strcpy(basemap[col][row].piece.name ,"wQ"); 
                    else if(col == 2)
                        strcpy(basemap[col][row].piece.name ,"wK"); 
                }
            }
            Coordinates currCoords = {col, row};
            //basemap[col][row]. = currCoords;
            basemap[col][row].isEmpty = false; 
        }
    }
}

void appendMove(int col, int row, int pieceType){
	for(int i=0; i < 16; i++){
		if(basemap[col][row].possMoves[i] <= 0){
			basemap[col][row].possMoves[i] = pieceType;
			return;
		}
	}
}
void possibleMoves(){
    for(int col = 0; col < BOARD_DIMENSION; col++) {
        for(int row = 0; row < BOARD_DIMENSION; row++) {
			Piece currPiece = basemap[col][row].piece;
			int pieceType = (currPiece._id +1) * (currPiece.isWhite + 1);
			//if piece is a pawn
			if(pieceType % 4 == 1){
				//move up or down depending on the piece color
				int temprow = row + (2 * currPiece.isWhite - 1);
				if(temprow >= 0 && temprow < BOARD_DIMENSION){
					if(basemap[col][temprow].isEmpty){
						appendMove(col, temprow, pieceType);
					}
					//llook right
					int tempcol = col + 1; 
					if(!(basemap[tempcol][temprow].isEmpty) && 
					basemap[tempcol][temprow].piece.isWhite != currPiece.isWhite &&
					tempcol < BOARD_DIMENSION)
						appendMove(tempcol, temprow, pieceType);
					//lookleft
					tempcol = col - 1; 
					if(!(basemap[tempcol][temprow].isEmpty) && 
					basemap[tempcol][temprow].piece.isWhite != currPiece.isWhite && 
					tempcol >= 0)
						appendMove(tempcol, temprow, pieceType);	
				}
			}
			//IF PIECE IS A ROOK
			if(pieceType % 4 == 2){
				int temprow = row + 1; 
				while (temprow < BOARD_DIMENSION){
					if (basemap[col][temprow].isEmpty)
						appendMove(col, temprow, pieceType); 
					else if(basemap[col][temprow].piece.isWhite != currPiece.isWhite){
						appendMove(col, temprow, pieceType);
						break;
					}
					temprow += 1;
				}
				int temprow = row -1; 
				while (temprow >= 0){
					if (basemap[col][temprow].isEmpty)
						appendMove(col, temprow, pieceType); 
					else if(basemap[col][temprow].piece.isWhite != currPiece.isWhite){
						appendMove(col, temprow, pieceType);
						break;
					}
					temprow-=1;
				}
				
				int tempcol = col + 1; 
				while (tempcol < BOARD_DIMENSION){
					if (basemap[tempcol][row].isEmpty)
						appendMove(tempcol, row, pieceType); 
					else if(basemap[tempcol][row].piece.isWhite != currPiece.isWhite){
						appendMove(tempcol, row, pieceType);
						break;
					}
					tempcol += 1;
				}
				int tempcol = col -1; 
				while (tempcol >= 0){
					if (basemap[tempcol][row].isEmpty)
						appendMove(tempcol, row, pieceType); 
					else if(basemap[tempcol][row].piece.isWhite != currPiece.isWhite){
						appendMove(tempcol, row, pieceType);
						break;
					}
					tempcol-=1;
				}
			}
			//IF PIECE IS A QUEEN
			if(pieceType % 4 == 3){
				//look in all 8 directions
				for(int i = 0; i < 8; i++){
					int temprow = row + round(sin(i*3.14/4));
					int tempcol = col + round(cos(i*3.14/4)); 
					while(temprow >= 0 && tempcol >=0  && tempcol < BOARD_DIMENSION && temprow < BOARD_DIMENSION){
						if (basemap[tempcol][temprow].isEmpty)
							appendMove(tempcol, temprow, pieceType); 
						else if(basemap[tempcol][temprow].piece.isWhite != currPiece.isWhite){
							appendMove(tempcol, temprow, pieceType);
							break;

						}
						temprow += round(sin(i*3.14/4));
						tempcol += round(cos(i*3.14/4)); 
					}
				}
			}

			//IF PIECE IS A King
			if(pieceType % 4 == 0){
				//look in all 8 directions
				for(int i = 0; i < 8; i++){
					int temprow = row + round(sin(i*3.14/4));
					int tempcol = col + round(cos(i*3.14/4)); 
					if(temprow >= 0 && tempcol >=0  && tempcol < BOARD_DIMENSION && temprow < BOARD_DIMENSION){
						if (basemap[tempcol][temprow].isEmpty)
							appendMove(tempcol, temprow, pieceType); 
						else if(basemap[tempcol][temprow].piece.isWhite != currPiece.isWhite){
							appendMove(tempcol, temprow, pieceType);
						}
					}
				}
			}

		}
	}
}

bool moveMade(){
	mapSpot startSpot = basemap[startPos.first][startPos.second];
	if (startSpot.isEmpty == true) return; 

	Piece selectedPiece = startSpot.piece; 
	int pieceType = (selectedPiece._id +1) * (selectedPiece.isWhite + 1);

	bool legalMove; 
	mapSpot endSpot = basemap[endPos.first][endPos.second]; 
	for(int i = 0; i < 16; i++){
		if(endSpot.possMoves[i] == pieceType){
			legalMove == true; 
			startSpot.isEmpty = true; 
			endSpot.piece = selectedPiece; 
			endSpot.isEmpty = false; 

			return true; 
		}
	}
    return false; 
}


int main(){
	printf("the program has started\n");

	makeBoard(basemap);

    while(1){
        possibleMoves(); 
        int move; 
        scanf("\nInput the next move: %d", move);
        startPos.first = (move / 1000) % 10; 
        startPos.second = (move / 100) % 10;
        endPos.first = (move / 10) % 10; 
        endPos.second = move % 10; 
        bool validMove = moveMade(); 
        if(!validMove)
            printf("\n please enter a valid move");
        else
            whiteTurn = !whiteTurn; 

    } 
	return 0;
}

