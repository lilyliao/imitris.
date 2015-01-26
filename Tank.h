#ifndef _TANK_
#define _TANK_

#include "Piece.h"

const int TANK_WIDTH  = 10;
const int TANK_HEIGHT = 18;

class Screen;

class Tank
{
  public:

	Tank();
    void display(Screen& screen, int x, int y);
    
    bool FreeBlock(int fx, int fy);
    bool PossibleMovement(int px, int py, Piece* pPiece, int pRotation);
    void StorePiece(int sx, int sy, Piece* pPiece);
    void DeleteLines();
    bool GameOver();
	void clear();
	bool vaporize();
	int countRowsLeft();
	void vapor(Piece* pPiece);
	void foam(Piece* pPiece);
    
private:
    enum{ FreePos, FilledPos};
    int mtank[TANK_HEIGHT][TANK_WIDTH];
    Piece *mPieces;
    
    void iniTank();
    void deleteLine(int pY);
};

#endif // TANK_INCLUDED
