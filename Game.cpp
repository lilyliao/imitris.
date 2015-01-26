#include "Game.h"
#include "Tank.h"
#include "UserInterface.h"
#include "randPieceType.h"
#include <string>
#include <cstdio>
#include <cstdlib>

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int TANK_X = 0;
const int TANK_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

const int PIECE_X = 3;
const int PIECE_Y = 0;

Game::Game(int width, int height)
 : m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_score(0), m_leftRows(0)
{
}

void Game::play()
{
    m_tank.display(m_screen, TANK_X, TANK_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Imitris!");
    waitForEnter();  // [in UserInterface.h]

	// just 3 levels
    for(m_level=1;m_level<=3;m_level++)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
       
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}


void Game::displayNextPiece()
{

       m_screen.gotoXY(NEXT_PIECE_TITLE_X,NEXT_PIECE_TITLE_Y);
	   m_screen.printStringClearLine("Next piece:");

}


// print score, rows left, level, 
void Game::displayStatus()
{
	char buffer[80];

	
    m_screen.gotoXY(SCORE_X,SCORE_Y);
	sprintf(buffer,"Score:         %2d",m_score);
	m_screen.printString(buffer);
	m_screen.gotoXY(ROWS_LEFT_X,ROWS_LEFT_Y);
    sprintf(buffer,"Rows Left:     %2d",m_leftRows);
	m_screen.printString(buffer);
	m_screen.gotoXY(LEVEL_X,LEVEL_Y);
    sprintf(buffer,"Level:         %2d",m_level);
	m_screen.printString(buffer);
}

bool Game::playOneLevel()
{
	char ch;
	int start=0;
	bool hasKey = false;
	int speed = 0;
	int px, py;
	int pOrientation;
	Piece* p = NULL; // curent piece
	Piece* pNext = NULL;
	m_score=0;
	m_leftRows = 0;

	if(m_level == 1) speed = 3000;
	if(m_level == 2) speed = 2000;
	else speed = 1000;
	m_tank.clear();

	// start pieces
	PieceType pt = randPieceType();
    p = new Piece(pt,PIECE_X,PIECE_Y,pieces[pt]);
	pt = randPieceType();
	pNext = new Piece(pt,NEXT_PIECE_X,NEXT_PIECE_Y,pieces[pt]);


	while(true)
	{
    // redraw tank		
	m_tank.display(m_screen, TANK_X, TANK_Y);

	// display next piece
	displayNextPiece();
	pNext->draw(m_screen,true);
    
	
	// display piece
	p->draw(m_screen);
	
    displayStatus();  //  score, rows left, level

	// piece loop
	while(true)
	{
		

		// time dealay
		  start = getMsecSinceStart();

         while(getMsecSinceStart()-start < speed )
	     {
			 hasKey = false;

				 if(getCharIfAny(ch))
				 {
					 hasKey = true;
					 break;
				 }
		  }

       px = p->x;
	   py = p->y;
	   pOrientation = p->orientation;
     
       if(hasKey || getCharIfAny(ch))
	   {
		    
		      if(ch == 'q')
			  {
				  exit(1);
			  }

              else if(ch ==  ARROW_UP )
			  {
				  if(m_tank.PossibleMovement( px, py, p, (pOrientation+1)%4))
				  {
				  p->erase(m_screen);
                  p->clockWise();
				  }
			  }

              else if(ch ==  ARROW_DOWN)
			  {
				      
				 if(m_tank.PossibleMovement( px, py+1, p,pOrientation))
				  {
				  p->erase(m_screen);
                  p->moveDown();
				 }
			  }

              else if(ch ==  ARROW_LEFT)
			  {
				  if(m_tank.PossibleMovement( px-1, py, p,pOrientation))
				  {
				  p->erase(m_screen);
                  p->moveLeft();
				  }
			  }

			  else if (ch == ARROW_RIGHT)
			  {
				 if(m_tank.PossibleMovement( px+1, py, p,pOrientation))
				  {
				  p->erase(m_screen);
                  p->moveRight();
				 }
			  }

			  	p->draw(m_screen);




	   }


	   px = p->x;
	   py = p->y;
	   pOrientation = p->orientation;

	   if(m_tank.PossibleMovement( px, py+1, p, pOrientation))
	   {
	    p->erase(m_screen);
	    if(!hasKey)  p->moveDown();
		hasKey=false;
	   	p->draw(m_screen);
	   }

	   else
	   {
		    m_tank.StorePiece(px, py, p);

			// check for vapor bomb
			if(p->piece_num==PIECE_VAPOR)
			{
				m_tank.vapor(p);
			}

			if(p->piece_num==PIECE_FOAM)
			{
			    m_tank.foam(p);
			}

			// check for foam bomb


			// check for filled row
			if(m_tank.vaporize())
				m_score++;

			m_leftRows= m_tank.countRowsLeft();
			break;
	   }
	} // end while

	if(m_score >= 5) break;
	if(m_leftRows<2) return false;

    p = pNext;
	p->x = PIECE_X;
	p->y = PIECE_Y;
	pt = randPieceType();
	pNext = new Piece(pt,NEXT_PIECE_X,NEXT_PIECE_Y,pieces[pt]);


	} // end while
	
    return true;  // [Replace this with the code to play a level.]
}


void Game::delay(int x)
	{
		  char ch;
          int s = getMsecSinceStart();

          while(getMsecSinceStart()-s < x);
       
	}