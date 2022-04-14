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
#include <stdlib.h>

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
    char name[3];
    int uniqueID; 
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
            printf("col: %d row: %d\n", col, row);
           // Piece *currPiece = &basemap[col][row].piece; 
            if(row < 2) {
                
                basemap[col][row].piece.isWhite = false;
               // printf("here!");
                //pawns
                if(row == 1) {
                    basemap[col][row].piece._id = 0; 
                    strcpy(basemap[col][row].piece.name, "bP");
                } else {

                    if(col == 0 || col == 3){
                        strcpy(basemap[col][row].piece.name ,"bR"); 
                        basemap[col][row].piece._id = 1; 
                    }
                    else if(col == 1){   
                        strcpy(basemap[col][row].piece.name ,"bQ"); 
                        basemap[col][row].piece._id = 2; 
                    }
                    else if(col == 2){ 
                        strcpy(basemap[col][row].piece.name ,"bK"); 
                        basemap[col][row].piece._id = 3; 
                    }
                }
            
            //if row >= 2
            } else {
              //  printf("ch1\n");
                basemap[col][row].piece.isWhite = true;
                //pawns
                if(row == 2) {
                    basemap[col][row].piece._id = 0; 
                    strcpy(basemap[col][row].piece.name ,"wP"); 
                } else {
                    if(col == 0 || col == 3){
                        strcpy(basemap[col][row].piece.name ,"wR"); 
                        basemap[col][row].piece._id = 1; 
                    }
                    else if(col == 1){
                        strcpy(basemap[col][row].piece.name ,"wQ"); 
                        basemap[col][row].piece._id = 2; 
                    }
                    else if(col == 2){
                        strcpy(basemap[col][row].piece.name ,"wK");
                        basemap[col][row].piece._id = 3; 
                    }
                }
            }
           // Coordinates currCoords = {col, row};
            //basemap[co1l][row]. = currCoords;
            
            basemap[col][row].isEmpty = false; 
            basemap[col][row].piece.uniqueID = col * 10 + row+1; 
            printf("%d",basemap[col][row].piece.uniqueID);
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
void clearMoves(){
    for(int col = 0; col <4; col++){
        for(int row = 0; row<4; row++){
            for(int i =0; i < 16; i++) basemap[col][row].possMoves[i] = 0;
        }
    }
}
void printMoves(){
    for(int col=0; col <4; col++){
        for(int row=0; row<4; row++){
            printf("\ncol: %d, row: %d\n", col, row);
            for(int i=0; i < 16; i++)
                printf("%d ", basemap[col][row].possMoves[i]);
        }
    }
}

void possibleMoves(){
    for(int col = 0; col < BOARD_DIMENSION; col++) {
        for(int row = 0; row < BOARD_DIMENSION; row++) {
			Piece currPiece = basemap[col][row].piece;
			//int pieceType = (currPiece._id  + 1) + (currPiece.isWhite * 4);
			//if piece is a pawn
			if(currPiece._id  == 0){
				//move up or down depending on the piece color
				int temprow = row + (2 * !currPiece.isWhite - 1);
				if(temprow >= 0 && temprow < BOARD_DIMENSION){
					if(basemap[col][temprow].isEmpty){
						appendMove(col, temprow, currPiece.uniqueID);
					}
					//llook right
					int tempcol = col + 1; 
					if(!(basemap[tempcol][temprow].isEmpty) && 
					(basemap[tempcol][temprow].piece.isWhite != currPiece.isWhite) &&
					tempcol < BOARD_DIMENSION)
						appendMove(tempcol, temprow, currPiece.uniqueID);
					//lookleft
					tempcol = col - 1; 
					if(!(basemap[tempcol][temprow].isEmpty) && 
					(basemap[tempcol][temprow].piece.isWhite != currPiece.isWhite) && 
					tempcol >= 0)
						appendMove(tempcol, temprow, currPiece.uniqueID);	
				}
			}
			//IF PIECE IS A ROOK
			if(currPiece._id == 1){
				int temprow = row + 1; 
				while (temprow < BOARD_DIMENSION){
					if (basemap[col][temprow].isEmpty)
						appendMove(col, temprow, currPiece.uniqueID); 
					else if(basemap[col][temprow].piece.isWhite != currPiece.isWhite){
						appendMove(col, temprow, currPiece.uniqueID);
						break;
					}
                    else break; 
					temprow += 1;
				}
				temprow = row - 1; 
				while (temprow >= 0){
					if (basemap[col][temprow].isEmpty)
						appendMove(col, temprow, currPiece.uniqueID); 
					else if(basemap[col][temprow].piece.isWhite != currPiece.isWhite){
						appendMove(col, temprow, currPiece.uniqueID);
						break;
					}
                    else break; 
					temprow-=1;
				}
				
				int tempcol = col + 1; 
				while (tempcol < BOARD_DIMENSION){
					if (basemap[tempcol][row].isEmpty)
						appendMove(tempcol, row, currPiece.uniqueID); 
					else if(basemap[tempcol][row].piece.isWhite != currPiece.isWhite){
						appendMove(tempcol, row, currPiece.uniqueID);
                        printf("moving %d, dest %d\n", currPiece.isWhite, basemap[tempcol][row].piece.isWhite);
						break;
					}
                    else break; 
					tempcol += 1;
				}
				tempcol = col -1; 
				while (tempcol >= 0){
					if (basemap[tempcol][row].isEmpty)
						appendMove(tempcol, row, currPiece.uniqueID); 
					else if(basemap[tempcol][row].piece.isWhite != currPiece.isWhite){
						appendMove(tempcol, row, currPiece.uniqueID);
						break;
					}
                    else break; 
					tempcol-=1;
				}
			}
			//IF PIECE IS A QUEEN
			if(currPiece._id == 2){
				//look in all 8 directions
				for(int i = 0; i < 8; i++){
					int temprow = row + round(sin(i*3.14/4));
					int tempcol = col + round(cos(i*3.14/4)); 
					while(temprow >= 0 && tempcol >=0  && tempcol < BOARD_DIMENSION && temprow < BOARD_DIMENSION){
						if (basemap[tempcol][temprow].isEmpty)
							appendMove(tempcol, temprow, currPiece.uniqueID); 
						else if(basemap[tempcol][temprow].piece.isWhite != currPiece.isWhite){
						    appendMove(tempcol, temprow, currPiece.uniqueID);
							break;

						}
						temprow += round(sin(i*3.14/4));
						tempcol += round(cos(i*3.14/4)); 
					}
				}
			}

			//IF PIECE IS A King
			if(currPiece._id == 3){
				//look in all 8 directions
				for(int i = 0; i < 8; i++){
					int temprow = row + round(sin(i*3.14/4));
					int tempcol = col + round(cos(i*3.14/4)); 
					if(temprow >= 0 && tempcol >=0  && tempcol < BOARD_DIMENSION && temprow < BOARD_DIMENSION){
						if (basemap[tempcol][temprow].isEmpty)
							appendMove(tempcol, temprow, currPiece.uniqueID); 
						else if(basemap[tempcol][temprow].piece.isWhite != currPiece.isWhite){
							appendMove(tempcol, temprow, currPiece.uniqueID);
						}
					}
				}
			}

		}
	}
}

bool moveMade(){
	//mapSpot startSpot = basemap[startPos.first][startPos.second];
	if (basemap[startPos.first][startPos.second].isEmpty == true) return false; 
    if (basemap[startPos.first][startPos.second].piece.isWhite != whiteTurn) return false; 

	Piece selectedPiece = basemap[startPos.first][startPos.second].piece; 
    printf("Selected Piece: %s\n", selectedPiece.name);
	//int pieceType = (selectedPiece._id +1) * (selectedPiece.isWhite + 1);

	bool legalMove; 
	//mapSpot endSpot = basemap[endPos.first][endPos.second]; 
	for(int i = 0; i < 16; i++){
       // printf("Start Piece Num %d, End Piece Num %d\n", pieceType, endSpot.possMoves[i]);
		if( basemap[endPos.first][endPos.second].possMoves[i] == selectedPiece.uniqueID){
			legalMove = true; 

			basemap[startPos.first][startPos.second].isEmpty = true; 
            Piece endPiece = basemap[endPos.first][endPos.second].piece; 
            if(endPiece._id == 3){
                printf("GAME OVER!\n");
                if(endPiece.isWhite) printf("BLACK WINS!\n");
                else printf("WHITE WINS!\n");
                exit(0);
            }

			basemap[endPos.first][endPos.second].piece = selectedPiece; 
			basemap[endPos.first][endPos.second].isEmpty = false; 



            printf("Valid Move\n");
            break;
		}
	}
    if(legalMove)return true; 
    else return false;
}

void drawMap(){
    printf("--------------\n");
    for(int i = 0; i < BOARD_DIMENSION; i++){
        for(int j = 0; j < BOARD_DIMENSION; j++){
            printf("|"); 
            if(basemap[j][i].isEmpty == false)
                printf("%s", basemap[j][i].piece.name); 
            else 
                printf("--");
            
        }
        printf("|\n");
    }
    printf("--------------\n");
}

int main(){
	printf("the program has started\n");

	makeBoard();

    while(1){
        clearMoves();
        drawMap(); 
        possibleMoves(); 
       // printMoves();
        int move; 
        printf("Please input next move:\n");
        scanf("%d", &move);
        printf("%d", move); 
        startPos.first = (move / 1000) % 10; 
        startPos.second = (move / 100) % 10;
        endPos.first = (move / 10) % 10;
        endPos.second = move % 10; 
        bool validMove = moveMade(); 
        if(validMove == false)
            printf("\nInvalid Move\n");
        else{
            whiteTurn = !whiteTurn; 
            printf("\nValid Move\n");
        }
        

    } 
	return 0;
}

