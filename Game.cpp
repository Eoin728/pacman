#include "Game.h"
#include "Renderer.h"
#include "Actor.h"
#include "SDL/SDL.h"
#include "MeshComponent.h"
#include "Mesh.h"

#include "Wall.h"
#include "Maze.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Input.h"
#include "Collectible.h"
#include "Tile.h"
#include "PauseMenu.h"
#include <SDL/SDL_ttf.h>
#include "Hud.h"
#include "Startscreen.h"

const  float pacheight = 0;

void Game::LoadData()
{

	mMaze = new Maze(this);
	mpac = new Pacman(this);
	mpac->SetPosition(Vector3(0, 0, pacheight));

	mhud = new Hud(this);


	SDL_SetRelativeMouseMode(SDL_TRUE);

	SDL_GetRelativeMouseState(nullptr, nullptr);
	
	mMaze->MakeMazeItems();

    new Startscreen(this);

   
}


//do i need mhud

Game::Game():misrunning{true},misupdatingactors{false},mticks{0},mRenderer{nullptr},mstate{Game::NotPaused},mMaze{nullptr},mpac{nullptr},minput{nullptr},mhud{nullptr}
{
	
}
bool Game::Initialize()
{

***REMOVED***

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	
	mRenderer = new Renderer(this);
	if (!mRenderer->Initialize(1024.0f, 768.0f))
	{
		
		SDL_Log("Failed to initialize renderer");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	}
	mticks = SDL_GetTicks();
	minput = new Input();

	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}


	LoadData();
	

	return true;
}
void Game::Runloop()
{
	while (misrunning)
	{
		
		processinput();
		update();
		genoutput();
	}
}


void Game::processinput()
{
	minput->UpdatePrev();
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			misrunning = false;
			break;
		
		
		
		default:
			break;
		}
	}

	minput->Update();
	if (mstate == Game::NotPaused)
	{
	
		if (minput->GetKeyboardState(SDL_SCANCODE_ESCAPE) == Input::released)
		{
			
			 new Pause(this);
		}
		misupdatingactors = true;
		for (auto actor : mcurractors)
		{
			actor->ProcessInput(*minput);
		}
		misupdatingactors = false;

	}
	else if (mstate == Game::Paused)
	{
	
		if (!mui.empty())
		{
			mui.back()->ProcessInput(*minput);
		}

	}



}
void Game::update()
{
	
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mticks + 16));
	float deltatime =  (SDL_GetTicks() - mticks)/ 1000.0f;
	
	if (mticks > 0.05f)
	{
		mticks = 0.05f;
	}

	mticks = SDL_GetTicks();

	for (auto x : mui)
	{
		if (x->GetState() == Ui::Dead)
		{
			auto iter = std::find(mui.begin(), mui.end(), x);
			mui.erase(iter);

			delete x;
		}
	}
	if (mstate == Game::NotPaused)
	{
		misupdatingactors = true;
		for (auto actor : mcurractors)
		{
			actor->Update(deltatime);
		}
		misupdatingactors = false;
		for (auto actor : mpendactors)
		{
			actor->ComputeWorldTransform();
			mcurractors.emplace_back(actor);
		}
		mpendactors.clear();

		std::vector<class Actor*> deadies;

		for (auto actor : mcurractors)
		{

			if (actor->GetState() == Actor::EDead)
			{
				deadies.emplace_back(actor);
			}
		}

		for (auto actor : deadies)
		{
			delete actor;
		}
	}
	else if (mstate == Dead)
	{
		misrunning = false;
	}


}
void Game::genoutput()
{
	
	mRenderer->Draw();
}

void Game::AddActor(class Actor*a)
{
	if (misupdatingactors)
	{
		mpendactors.emplace_back(a);
	}
	else
		mcurractors.emplace_back(a);
}
void Game::RemoveActor(class Actor* a)
{
	auto iter = std::find(mcurractors.begin(), mcurractors.end(), a);

	if (iter != mcurractors.end())
	{
		std::iter_swap(mcurractors.end() - 1, iter);
		mcurractors.pop_back();
	}

	 iter = std::find(mpendactors.begin(), mpendactors.end(), a);

	if (iter != mpendactors.end())
	{
		std::iter_swap(mpendactors.end() - 1, iter);
		mpendactors.pop_back();
	}


}

void Game::Shutdown()
{
	UnloadData();
	if (mRenderer)
	{
		mRenderer->Shutdown();
	}

	SDL_Quit();

}

void Game::UnloadData()
{
	while (!mcurractors.empty())
	{
		
		delete mcurractors.back();
	}
	if (mRenderer)
	{
		mRenderer->Unload();
	}


	delete minput;

	
	for (Ui * x : mui)
	{
		delete x;
	}

}


void Game::AddGhost(class Ghost*g)
{
	mGhosts.emplace_back(g);
}

void Game::RemoveGhost(class Ghost*g)
{
	auto iter = std::find(mGhosts.begin(), mGhosts.end(), g);
	mGhosts.erase(iter);
}

void Game::AddUi(class Ui* u)
{

	mui.push_back(u);
}

void Game::SetState(State a)
{
	mstate = a; 
	if (mstate == State::NotPaused)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_GetRelativeMouseState(nullptr, nullptr);
		minput->SetMouseRelative(false);
	}

	else if (mstate == State::Paused)
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		minput->SetMouseRelative(false);
	}

}