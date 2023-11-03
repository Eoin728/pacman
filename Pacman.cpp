
#include "Pacman.h"
#include "Paccam.h"
#include "Movement.h"
#include "Game.h"
#include "SphereComp.h"
#include "Renderer.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "AABBcomp.h"
#include "Wall.h"
#include "Maze.h"
#include "Ghost.h"
#include "Input.h"
#include "CapsuleComp.h"
#include "Projectile.h"
#include "Hud.h"
#include "EndScreen.h"


Pacman::Pacman(class Game* g) :Actor{ g },mspeed{250},mrockcount{0}, mpelletcount{0}
{
	SetScale(25.0f);
	mcam = new Paccam(this);
	mmovie = new Movement(this);
	 mpacmodel = new MeshComp(this);
	 Mesh* m = g->GetRenderer()->GetMesh("Assets/pacman23.txt");
	mpacmodel->SetMesh(m);
	mpacmodel->SetVisible(false);
	mradius = m->GetRadius() * GetScale();
	msphere = new SphereComp(this,mradius);
	
	mhands = new Actor(g);
	mhands->SetScale(10);
	Quaternion q = Quaternion(Vector3::UnitX, Math::HalfPi);
	mhands->SetRotation(q);

	mhandmodel = new MeshComp(mhands);
	mhandmodel->SetMesh(g->GetRenderer()->GetMesh("Assets/cannon.txt"));

	mwinningpelletamount = g->GetMaze()->GetTileNum() * g->GetMaze()->GetTileNum() - g->GetMaze()->GetFruitNum();

}

void Pacman::ProcessInput(const Input& state)
{
	int sidespeed{ 0 };
	int forspeed{ 0 };
	
	if (state.GetKeyboardState(SDL_SCANCODE_W) == Input::held || state.GetKeyboardState(SDL_SCANCODE_W) == Input::pressed)
	{
		forspeed += mspeed;
	}
	if (state.GetKeyboardState(SDL_SCANCODE_S) == Input::held || state.GetKeyboardState(SDL_SCANCODE_S) == Input::pressed)
	{
		forspeed -= mspeed;
	}
	if (state.GetKeyboardState(SDL_SCANCODE_D) == Input::held || state.GetKeyboardState(SDL_SCANCODE_D) == Input::pressed)
	{
		sidespeed += mspeed;
	}
	if (state.GetKeyboardState(SDL_SCANCODE_A) == Input::held || state.GetKeyboardState(SDL_SCANCODE_A) == Input::pressed)
	{
		sidespeed -= mspeed;
	}

	
	
	mmovie->SetForward(forspeed);
	mmovie->SetSide(sidespeed);


	if (state.GetKeyboardState(SDL_SCANCODE_SPACE) == Input::pressed)
	{
		SwitchCam();
	}
	else if (state.GetKeyboardState(SDL_SCANCODE_SPACE) == Input::released)
	{
		SwitchCam();
	}
	
	if (state.GetMouseButtonState(SDL_BUTTON_LEFT) == Input::pressed)
	{
		if (!dynamic_cast<ThirdCam*>(mcam))
		{
			if (mrockcount > 0)
			{
				new Projectile(GetGame());
				mrockcount--;
			}
		}
	}

	//mouse time
	int x, y;
	SDL_GetRelativeMouseState(&x, &y);
	
	
	const int maxMouseSpeed = 500;

	const float maxAngularSpeed = Math::Pi * 8;
	float h{ 0.0f };
	if (x != 0)
	{
		h = static_cast<float>(x) / maxMouseSpeed;
	
		h *= maxAngularSpeed;

	}
	
	mmovie->SetRot(h);

	const float maxPitchSpeed = Math::Pi * 8;
	float pitchspeed = 0.0f;
	if (y != 0)
	{
		
		pitchspeed = static_cast<float>(y) / maxMouseSpeed;
		pitchspeed *= maxPitchSpeed;
	}

	
	mcam->SetPitch(pitchspeed);
}



void Pacman::ActorUpdate(float)
{
	
	wallhit();
	//DetectGhosts();
	//do collisions with ghosts
	CheckGhostColl();

	Quaternion q = Quaternion(Vector3::UnitY, Math::HalfPi);
	q = GetRot() * q;
	q = Quaternion(GetSide(), -Math::Pi / 6) * q;

	mhands->SetRotation(q);
	Vector3 pos = GetPos();
	pos = pos + 2 * GetForward();
	pos = pos + 10 * GetSide();
	pos.z -= 5;

	mhands->SetPosition(pos);
}





bool Pacman::wallhit()
{
	for (auto b : GetGame()->GetRenderer()->GetWalls())
	{
		if (Intersect(b->Getboox()->GetAABB(), msphere->GetSphere()))
		{
			Vector3 g = b->Getboox()->GetAABB().MinVec(msphere->GetSphere().mCentre);
			Vector3 h = Vector3::Normalize(g);
			h = msphere->GetSphere().mRadius * h;
			h = h - g;

			if (b->Getboox()->GetAABB().IsLeftOrDown(msphere->GetSphere().mCentre))
			{

				SetPosition(GetPos() - h);
				msphere->Update(0.1);
			}
			else
			{
				SetPosition(GetPos() + h);
				msphere->Update(0.1);
			}
		
		}
	}
	return false;
	}

void Pacman::SwitchCam()
{
	if (dynamic_cast<ThirdCam*>(mcam))
	{
		 delete mcam;
		 mcam = new Paccam(this);
		 mpacmodel->SetVisible(false);
		 mhandmodel->SetVisible(true);
	}
	else
	{
		delete mcam;
		mcam = new ThirdCam(this);
		mpacmodel->SetVisible(true);
		mhandmodel->SetVisible(false);
	}

	GetGame()->GetHud()->SwitchDrawCrosshair();
}

void Pacman::CheckGhostColl()
{

	for (auto ghost : GetGame()->GetGhosts())
	{
		
		if (Intersect(msphere->GetSphere(), ghost->GetCapsule()->GetCapsule()))
		{
			new Endscreen(GetGame(),Endscreen::Lost);
		}

	}
}

void Pacman::AddRock()
{ 
	mrockcount++;
}

void Pacman::AddPellet() 
{ 
	mpelletcount++;
	if (mpelletcount == mwinningpelletamount)
	{
		new Endscreen(GetGame(), Endscreen::Won);
	}
}

void Pacman::ResetPelletsAndRocks()
{
	mpelletcount = 0;
	mrockcount = 0;

}

class Tile* Pacman::GetCurrTile()
{
	Vector3 fff = GetPos();
	int xxx = static_cast<int>(fff.x + mradius);
	int yyy = static_cast<int>(fff.y + mradius);
	xxx /= GetGame()->GetMaze()->GetTileSize();
	yyy /= GetGame()->GetMaze()->GetTileSize();
	
	return GetGame()->GetMaze()->GetTiles()[xxx][yyy];

}
#include "Tile.h"
#include <queue>
#include <iostream>

void Pacman::DetectGhosts()
{
	Tile* start = GetCurrTile();
	std::queue<Tile*> q;
	std::unordered_map<Tile*, int> pq;
	pq.emplace(start, 0);
	q.push(start);
	
	bool closed[100][100] = { {false} };
	closed[start->GetX()][start->GetY()];
	while (!q.empty() && pq[q.front()] < 5)
	{
		start = q.front();
	
		q.pop();
		for (auto adj : start->GetAdjacent())
		{
			if (adj->GetGhost())
			{
				//adj->GetGhost()->SetHunting(true);
			}
			if (!closed[adj->GetX()][adj->GetY()])
			{
				pq.emplace(adj, pq[start] + 1);
				q.push(adj);
				closed[adj->GetX()][adj->GetY()] = true;
			}
		}


	}
	
	

}