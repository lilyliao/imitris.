#include "Tank.h"
#include "UserInterface.h"


// clear tank
Tank::Tank()
{
      for(int r=0;r<TANK_HEIGHT;r++)
	  {
		  for(int c=0;c<TANK_WIDTH;c++)
		  {
			
				  mtank[r][c] = ' ';
			
		  }
	  }
}

// clear tank
void Tank::clear()
{

     for(int r=0;r<TANK_HEIGHT;r++)
	  {
		  for(int c=0;c<TANK_WIDTH;c++)
		  {
			
				  mtank[r][c] = ' ';
			
		  }
	  }
}

// display screen
void Tank::display(Screen& screen, int x, int y)
{
      int r,c;
	  screen.gotoXY(x, y);

	 for(r=0;r<TANK_HEIGHT;r++)
	  {
		  screen.gotoXY(0+x, r+y);

		  screen.printChar('@');
		  for(c=0;c<TANK_WIDTH;c++)
		  {
                screen.printChar((char)mtank[r][c]);
			 
		  }
		 
		  screen.printChar('@');
	 }

	   screen.gotoXY(0+x, r+y);

	  for(int c=0;c<TANK_WIDTH+2;c++)
		    screen.printChar('@');
    
}

bool Tank::FreeBlock(int fx, int fy)
{
    if(mtank[fy][fx]==FreePos)
        return true;
    else
        return false;
}

bool Tank::PossibleMovement( int px, int py, Piece* pPiece, int pRotation)
{
    for(int i1=py, i2=0;i1<py+4;i1++,i2++)
    {
        for(int j1=px,j2=0;j1<px+4;j1++,j2++)
        {
            if(pPiece->cells[pRotation][i2][j2] == 1)
				{
				 if(j1 <= 0) return false;
				 if(j1 > TANK_WIDTH) return false;
				 if(i1 > TANK_HEIGHT) return false;
				 if(mtank[i1][j1-1] != ' ')return false;
			   }
				
        }
    }

	return true;
}

// store piece in tank
   void Tank::StorePiece(int sx, int sy, Piece* pPiece)
   {
	   for(int r=0;r<4;r++)
	   {
		   for(int c=0;c<4;c++)
		   {
			   if(pPiece->cells[pPiece->orientation][r][c]==1)
				   mtank[r+sy][c+sx-1] = '$';
		   }
	   }


   }

// vaporize
  bool Tank::vaporize()
   {
	   int count = 0;

	   // check bottom line
	   for(int j=0;j<TANK_WIDTH;j++)
	   {
		   if(mtank[TANK_HEIGHT-1][j]!=' ')count++;
	   }

	   // vaporize bottom row
	   if(count == TANK_WIDTH)
	   {
		   // shift lines down
		   for(int i=TANK_HEIGHT-1;i>=0;i--)
		   {
		   for(int j=0;j<TANK_WIDTH;j++)
	       {
		       mtank[i][j]=mtank[i-1][j];
		   }
		   }

		   for(int j=0;j<TANK_WIDTH;j++)
		   {
			   mtank[0][j]=' ';
		   }

		   return true;
	   }

	   return false;
  }



	   // count rows left
	   int Tank::countRowsLeft()
	   {
	   int count = 0;
	   int rowsleft = 0;

	   for(int i=0;i<TANK_HEIGHT-2;i++)
	   {
		   count = 0;
		   for(int j=0;j<TANK_WIDTH;j++)
		   {
			   if(mtank[i][j]!=' ') count++;
		   }

		   if(count > 0) break;

		   rowsleft++;
	   }

	   return rowsleft;
	   
   }

	   
	// remove all blocks that are up to
    // two rows directly above or below the VaporBomb, plus the blocks
    // of the VaporBomb itself. 
	void Tank::vapor(Piece* pPiece)
	{
		int px = pPiece->x;
		int py = pPiece->y;

		for(int i=py-2;i<TANK_HEIGHT && i < py+2;i++)
		{
			mtank[i][px] = ' ';
			mtank[i][px+1] = ' ';

		}
	}


	/*
	Once a FoamBomb has come to rest (on top of other blocks or at
    the bottom of the tank), its special action must be executed.
    Assuming the FoamBomb comes to rest at position (X,Y), its
    special action is to fill with foam (indicated by *) all empty slots
    that are in the 5x5 block bounding box (X-2,Y-2) to (X+2,Y+2),
    subject to the constraint that they are reachable from the FoamBomb:
    a All empty slots within the 5x5 bounding box that are directly
    adjacent, either vertically or horizontally (but not diagonally),
    to the FoamBomb should be filled with a * block.
    b All empty slots within the 5x5 bounding box that are directly
    adjacent, either vertically or horizontally, to slots defined in
   (a) should also be filled with a * block.
   c Step (b) should be recursively repeated for all blocks that are
   directly adjacent, either vertically or horizontally, to empty
   slots within the 5x5 bounding box as defined in (b) or in (a)
   — they should also be filled with a * block
   */
	void Tank::foam(Piece* pPiece)
	{
		   
		int px = pPiece->x;
		int py = pPiece->y;

		for(int i=py-2;i <= py+2;i++)
		{
			for(int j=px-2;j <= px+2;j++)
		    {
				if(i>=0 && i<TANK_HEIGHT && j >= 0 && j < TANK_WIDTH && mtank[i][j] == ' ') 
			       mtank[i][j] = '*';
		

		    }
		}
	}