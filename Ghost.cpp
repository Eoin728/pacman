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


	float wallsize = Math::Max(tmp.mmax.y - tmp.mmin.y, tmp.mmin.y - tmp.mmax.y);

	float w2 = Math::Max(tmp.mmax.x - tmp.mmin.x, tmp.mmin.x - tmp.mmax.x);
	wallsize = Math::Max(wallsize, w2);

	w2 = Math::Max(tmp.mmax.z - tmp.mmin.z, tmp.mmin.z - tmp.mmax.z);
	wallsize = Math::Max(wallsize, w2);
	a->AddGhost(this);
	
	mcapsule = new CapsuleComp(this,10 *  ((me->GetAABB().mmax.y - me->GetAABB().mmin.y) / 2),wallsize);
	mmovie->SetForward(40.0f);

	mprev = GetCurrTile();
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
		

		
		Tile* t = GetCurrTile();

		Tile* node = t->GetAdjacent()[Random::get(0, static_cast<int>(t->GetAdjacent().size() - 1))];
		if (t->GetAdjacent().size() > 1)
		{
			while (node == mlast)
			{
				node = t->GetAdjacent()[Random::get(0, static_cast<int>(t->GetAdjacent().size() - 1))];
			}

		}
	
		mprev->mghost = nullptr;
		GetCurrTile()->mghost = this;
		mprev = GetCurrTile();

		SetFacingDir(node, t);
	}
}



int Ghost::Range()
{

	const int maxpathlen = 5;
	struct info
	{
		int pathlen;
		int heuristic;
		Tile* prev;
	};

	std::unordered_map<Tile*, info> mp;
	auto cmp = [&mp](Tile* a, Tile* b)
	{
		return mp[a].pathlen > mp[b].pathlen;
	};
	std::priority_queue< Tile*, std::vector < Tile*>, decltype(cmp)> pq(cmp);

	Tile* start = GetGame()->GetPac()->GetCurrTile();
	Tile* end = GetCurrTile();
	Tile* curr;

	auto calculateheuristic = [end](Tile * other)
	{
		return (Math::Abs(other->GetX() - end->GetX()) + Math::Abs(other->GetY() - end->GetY()));
	};
	info x;
	x.pathlen = 0;
	x.heuristic = calculateheuristic(start);
	x.prev = end;
	mp.emplace(start, x);

	bool chkr[100][100] = { {false} };
	chkr[start->GetX()][start->GetY()] = true;
	pq.push(start);
	while (!pq.empty())
	{
		curr = pq.top();
		pq.pop();

		if (curr == end)
		{
			mhuntnext = mp[curr].prev;
			return 1;
		}
		if (mp[curr].pathlen > maxpathlen)
		{
		
			return -1;
		}

		for (auto adj : curr->GetAdjacent())
		{
			if (!chkr[adj->GetX()][adj->GetY()])
			{
				chkr[adj->GetX()][adj->GetY()] = true;
				info xx;
				xx.pathlen = mp[curr].pathlen + 1;
				x.heuristic = calculateheuristic(adj);
				xx.prev = curr;
				mp.emplace(adj, xx);
				pq.push(adj);
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

	
	
		SetRotation(Quaternion(Vector3::UnitZ, Math::HalfPi) * Quaternion(Vector3::UnitX, Math::HalfPi));
		mlast = t;

	}
	else if ((t->GetY() > node->GetY()))
	{
		

		SetRotation(Quaternion(Vector3::UnitZ, -Math::HalfPi) * Quaternion(Vector3::UnitX, Math::HalfPi));
		mlast = t;
	}
}