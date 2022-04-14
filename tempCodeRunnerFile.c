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