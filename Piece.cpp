// Piece.cpp



#include "piece.h"
#include "UserInterface.h"

Piece::Piece(int num, int xpos, int ypos, int c[4][4][4])
{
     piece_num = num;
	 x = xpos;
	 y = ypos;
	 orientation=0;
	
	 for(int i=0;i<4;i++)
	 {
		 for(int j=0;j<4;j++)
		 {
			 for(int k=0;k<4;k++)
			 {
				 cells[i][j][k] = c[i][j][k];
			 }
		 }
	 }


}

void Piece::erase(Screen& screen)
{
	erase(screen,false);
}

// erase piece
void Piece::erase(Screen& screen, bool all)
{

	for(int r=0;r<4;r++)
	{
		for(int c=0;c<4;c++)
		{

            screen.gotoXY(c+x,r+y);

		    if(cells[orientation][r][c] == 1)
			{
			   screen.printChar(' ');
			}

			else if (all)
			{
				screen.printChar(' ');
			}
		}
	}
  
}

void Piece::draw(Screen& screen)
{
	draw(screen,false);
}

// draw piece
void Piece::draw(Screen& screen, bool all)
{

	for(int r=0;r<4;r++)
	{
		for(int c=0;c<4;c++)
		{
			screen.gotoXY(c+x,r+y);

		 	if(cells[orientation][r][c] == 1)
		 	{
		 		
		 		screen.printChar('#');
             }			

			else if(all)
			{

				screen.printChar(' ');
                
			}
		}
	}
  
}

void Piece::clockWise()
{
    orientation = (orientation+1) % 4;

}

void Piece::moveDown()
{
	 
     y = y + 1;
}
   
void Piece::moveLeft()
{
	 
     x = x - 1;
}

void Piece::moveRight()
{
	 
	x = x + 1;
}



