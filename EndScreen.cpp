#include "EndScreen.h"
#include "Game.h"
#include "Texture.h"
#include "Renderer.h"
#include "Startscreen.h"
#include "Input.h"

#include "Text.h"
#include "Maze.h"
Endscreen::Endscreen(class Game* g,State condition):Ui{g}
{

	//this is so bloated
	g->SetState(Game::Paused);
	Texture* t;

	t = mtexty->GetText("play again", mmenucolour);

***REMOVED***
***REMOVED***
	new Interact(this,Vector3(-minteractwidth * 0.5, 0, 0), Vector3(minteractwidth, minteractheight, 0), t, [this]() {SetState(Ui::Dead); mgame->GetMaze()->MakeMazeItems(); new Startscreen(mgame); });
	
	
	
	t = mtexty->GetText("quit", mmenucolour);
	  new Interact(this,Vector3(minteractwidth * 0.5, 0, 0), Vector3(minteractwidth, minteractheight, 0), t, [this]() {mgame->SetState(Game::Dead); });
	

	 if (condition == State::Lost)
		 mmessage = mtexty->GetText("You Lose", Vector3(255, 255, 0.0f));
	 else if (condition == State::Won)
		mmessage = mtexty->GetText("You Win!!!", Vector3(255, 255, 0.0f));
	
}


void Endscreen::Draw(class Shader*s)
{
	Vector3 f = Vector3(0, 200, 0);
	Ui::Draw(s);
	Drawhelper(mmessage,f, s);

}