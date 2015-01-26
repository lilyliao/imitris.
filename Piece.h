// Piece.h

#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED


class Screen;

class Piece
{


public:
	int piece_num;
	int x,y;
    int orientation;
	int cells[4][4][4];

public:

	Piece(int num,int x, int y,int cells[4][4][4]);
	void draw(Screen& screen, bool all); 
	void erase(Screen& screen, bool all); 
    void draw(Screen& screen); 
	void erase(Screen& screen); 

	void clockWise();
	void moveDown();
    void moveLeft();
	void moveRight();

};

#endif
