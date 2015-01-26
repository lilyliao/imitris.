#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Tank.h"
#include "UserInterface.h"
#include <string>
// [Add other #include directives as necessary.]

class Game
{
  public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
    void iniGame();
    void newPiece();
    void drawPiece(int px, int py, int pp);
	void displayNextPiece();

  private:
    Tank    m_tank;
    Screen  m_screen;
    int     m_level;
    int     m_score;
    int     m_leftRows;
    // [Add other members as necessary.]

	void delay(int);
};

#endif // GAME_INCLUDED
