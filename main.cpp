#include "Game.h"
int main(int, char**)
{

	Game game;

	if (game.Initialize())
	{
		
		game.Runloop();

	}
	
	game.Shutdown();
}