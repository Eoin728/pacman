#include "Ghost.h"
#include "Movement.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Random.h"
#include "Tile.h"
#include "Maze.h"
#include "Pacman.h"
#include <queue>
#include <functional>
#include "CapsuleComp.h"

Ghost::Ghost(class Game* a):Actor{a},timer{1},mlast{nullptr},maxlength{5},mishunting{false},mhuntnext{nullptr}
{
	mmovie = new Movement(this);
	SetScale(10);
	Mesh* me = a->GetRenderer()->GetMesh("Assets/Ghost.txt");
	MeshComp* m = new MeshComp(this);
	m->SetMesh(me);
	mlast = GetGame()->GetMaze()->GetTiles()[GetTileX()][GetTileY()];
	AABB tmp = me->GetAABB();

	***REMOVED***
	float wallsize = Math::Max(tmp.mmax.y - tmp.mmin.y, tmp.mmin.y - tmp.mmax.y);

	float w2 = Math::Max(tmp.mmax.x - tmp.mmin.x, tmp.mmin.x - tmp.mmax.x);
	wallsize = Math::Max(wallsize, w2);

	w2 = Math::Max(tmp.mmax.z - tmp.mmin.z, tmp.mmin.z - tmp.mmax.z);
	wallsize = Math::Max(wallsize, w2);
	a->AddGhost(this);
	
	mcapsule = new CapsuleComp(this,10 *  ((me->GetAABB().mmax.y - me->GetAABB().mmin.y) / 2),wallsize);
	mmovie->SetForward(40.0f);
}

Ghost::~Ghost()
{
	GetGame()->RemoveGhost(this);
}


void Ghost::ActorUpdate(float delta)
{
	
	timer += delta;
	if (Centered())
	{
		if (Range() == -1)
		{
			mishunting = false;
			
			Patrol(delta);
		}
		else
		{
			
			mishunting = true;
			Hunt(delta);
		}
	}
}

bool Ghost::Centered()
{
	return (fmodf(GetPos().x, (GetGame()->GetMaze()->GetTileSize())) < 2 && fmodf(GetPos().y , GetGame()->GetMaze()->GetTileSize()) < 2);
}




void Ghost::Patrol(float& delta)
{
	if (timer > 0.1)
	{
		mmovie->SetForward(40.0f);
		timer = 0;
		SetPosition(Vector3(GetTileX() * GetGame()->GetMaze()->GetTileSize(), GetTileY() * GetGame()->GetMaze()->GetTileSize(), 0.0f));
	

		//this perhaps could be revised
		Tile* t = GetCurrTile();
		Tile* node = t->GetAdjacent()[Random::get(0, static_cast<int>(t->GetAdjacent().size() - 1))];
		if (node == mlast)
			node = t->GetAdjacent()[Random::get(0, static_cast<int>(t->GetAdjacent().size() - 1))];
		if (node == mlast)
			node = t->GetAdjacent()[Random::get(0, static_cast<int>(t->GetAdjacent().size() - 1))];
		if (node == mlast)
			node = t->GetAdjacent()[Random::get(0, static_cast<int>(t->GetAdjacent().size() - 1))];


		SetFacingDir(node, t);
	}
}

bool cmp(Tile* a, Tile* b)
{
	return a->GetPathCost() > b->GetPathCost();
}

int Ghost::Range()
{


	int i{ 0 };
	Tile* start{ GetGame()->GetPac()->GetCurrTile()};

	Tile* end{ GetCurrTile() };
	struct scar
	{
		Tile* parent = nullptr;
		int num = 0;
	};
	scar x;
	std::unordered_map<Tile*, scar> mp;
	Tile* curr;
	mp.emplace(start, x);
	std::queue<Tile*> q;
	q.emplace(start);
	while (!q.empty())
	{
		curr = q.front();
		q.pop();
		if (curr == end)
		{

			mhuntnext = mp[curr].parent;
			
			return x.num;
		}
		for (auto child : curr->GetAdjacent())
		{

			if (mp.find(child) == mp.end())
			{


				x.parent = curr;
				x.num = mp.find(curr)->second.num + 1;
				if (x.num > maxlength)
				{
					return -1;
				}
				mp.emplace(child, x);
				q.emplace(child);
			}



		}



	}

	return -1;

}

void Ghost::Hunt(float delta)
{
	if (timer > 0.1)
	{
		mmovie->SetForward(100.0f);
		Tile* node = mhuntnext;
		timer = 0;
		SetPosition(Vector3(GetTileX() * GetGame()->GetMaze()->GetTileSize(), GetTileY() * GetGame()->GetMaze()->GetTileSize(), 0.0f));
		Tile* t = GetCurrTile();
		SetFacingDir(node, t);
	}

}

void Ghost::SetFacingDir( Tile * node,  Tile *t)
{
	Quaternion q;
	if ((t->GetX() < node->GetX()))
	{
		
		q = Quaternion(Vector3::UnitZ, Math::Pi);

		SetRotation(Quaternion(Vector3::UnitX, Math::HalfPi));
		mlast = t;
	}
	else if ((t->GetX() > node->GetX()))
	{
		SetRotation(Quaternion(Vector3::UnitZ, Math::Pi) * Quaternion(Vector3::UnitX, Math::HalfPi));
		mlast = t;
	}
	else if ((t->GetY() < node->GetY()))
	{

	
		q = Quaternion(Vector3::UnitZ, -Math::HalfPi);
		SetRotation(Quaternion(Vector3::UnitZ, Math::HalfPi) * Quaternion(Vector3::UnitX, Math::HalfPi));
		mlast = t;

	}
	else if ((t->GetY() > node->GetY()))
	{
		
		q = Quaternion(Vector3::UnitZ, Math::HalfPi);
		SetRotation(Quaternion(Vector3::UnitZ, -Math::HalfPi) * Quaternion(Vector3::UnitX, Math::HalfPi));
		mlast = t;
	}
}