#include "Maze.h"
#include "Tile.h"
#include "Renderer.h"
#include "Wall.h"
#include "Mesh.h"
#include <algorithm>
#include "Random.h"
#include "AABBcomp.h"
#include "CollisionTime.h"
#include "Fruit.h"
#include "Collectible.h"
#include "Game.h"
#include "Pellet.h"
#include "Ghost.h"
#include "Pacman.h"
void Maze::CreateAdjacent(int i,int j)
{
	if (i < mtilenum - 1)
				mtiles[i][j]->madjacent.emplace_back(mtiles[i + 1][j]);
			if (i > 0)
				mtiles[i][j]->madjacent.emplace_back(mtiles[i - 1][j]);
			if (j < mtilenum - 1)
				mtiles[i][j]->madjacent.emplace_back(mtiles[i][j + 1]);
			if (j > 0)
				mtiles[i][j]->madjacent.emplace_back(mtiles[i][j - 1]);
		
			std::shuffle(mtiles[i][j]->madjacent.begin(), mtiles[i][j]->madjacent.end(),Random::mt);
}




Maze::Maze(class Game* r) :mGame{ r }
{


	Quaternion q = Quaternion::Identity;
	mtiles[0][0] = new Tile(0,0);
	for (int i{ 0 }; i < mtilenum; i++)
	{
		if (i + 1 < mtilenum)
		{
			mtiles[0][i + 1] = new Tile(0, i + 1);

		}
		mtiles[1][i] = new Tile(1, i);

		CreateAdjacent(0, i);


	}
	

	for (int i{ 1 }; i < mtilenum; i++)
	{

		for (int j{ 0 }; j < mtilenum; j++)
		{

			if (i + 1 < mtilenum)
			{
				mtiles[i + 1][j] = new Tile(i + 1, j);

			}
			CreateAdjacent(i, j);
		}

	}

	Wall a(Vector3::Zero, Quaternion::Identity, mGame);
	AABB tmp = a.Getboox()->GetAABB();
	float wallsize = Math::Max(tmp.mmax.y - tmp.mmin.y, tmp.mmin.y - tmp.mmax.y);
	
	float w2 = Math::Max(tmp.mmax.x - tmp.mmin.x, tmp.mmin.x - tmp.mmax.x);
	wallsize = Math::Max(wallsize, w2);
	
	w2 = Math::Max(tmp.mmax.z - tmp.mmin.z, tmp.mmin.z - tmp.mmax.z);
	wallsize = Math::Max(wallsize, w2);

	
	mtilesize = wallsize;

	MakeMaze(mtiles[0][0]);
	MakeWalls();

	for (int i{ 0 }; i < mtilenum; i++)
	{
		for (int j{ 0 }; j < mtilenum; j++)
		{
			if (!mtiles[i][j]->xunderadj)
				mtiles[i][j]->madjacent.emplace_back(mtiles[i + 1][j]);
			if (!mtiles[i][j]->xoveradj)
				mtiles[i][j]->madjacent.emplace_back(mtiles[i - 1][j]);
			if (!mtiles[i][j]->yunderadj)
				mtiles[i][j]->madjacent.emplace_back(mtiles[i][j + 1]);
			if (!mtiles[i][j]->yoveradj)
				mtiles[i][j]->madjacent.emplace_back(mtiles[i][j - 1]);
		}
	}
	Pellet* p;
	for (int i{ 0 }; i < mtilenum; i++)
	{
		for (int j{ 0 }; j < mtilenum; j++)
		{
			p = new Pellet(mGame);
			mtiles[i][j]->mcollectible = p;
			p->SetPosition(Vector3(i * mtilesize,j * mtilesize,0.0f));
		}
	}

	
	
}


		Maze::~Maze()
		{
			for (auto& x : mtiles)
			{
				for (auto y : x)
				{
					delete y;
				}
			}
		}

		void Maze::MakeMaze(Tile* curr)
		{

			
			bool x{ false };
			Tile* node{ nullptr };
			while (!curr->madjacent.empty())
			{

				node = curr->madjacent.back();
				curr->madjacent.pop_back();

				if (node->visited == false)
				{
					x = true;
					node->visited = true;
					if (node->x > curr->x)
					{
						curr->xunderadj = false;
						node->xoveradj = false;
					}
					else if (node->x < curr->x)
					{
						curr->xoveradj = false;
						node->xunderadj = false;
					}
					else if (node->y < curr->y)
					{
						curr->yoveradj = false;
						node->yunderadj = false;
					}
					else if (node->y > curr->y)
					{
						curr->yunderadj = false;
						node->yoveradj = false;
					}
					MakeMaze(node);
				}


			}


		}

void Maze::MakeWalls()
{

	

	for (auto x:mtiles)
	{
		for (auto y: x)
		{
			
	Quaternion q(Vector3::UnitX, Math::Pi / 2);
	if (y->yunderadj)
	{
	
	 new Wall(Vector3(y->x * mtilesize, (y->y * mtilesize) + mtilesize / 2, 0.0f), q, mGame);
	}
	if (y->yoveradj)
	{

	
	 new Wall(Vector3(y->x * mtilesize, y->y * mtilesize - mtilesize / 2, 0.0f), q, mGame);
	}
	q = Quaternion(Vector3::UnitZ, Math::Pi / 2) * q;

	if (y->xunderadj)
	{
		
		 new Wall(Vector3((y->x * mtilesize) + mtilesize / 2, y->y * mtilesize, 0.0f), q, mGame);
	}
	if (y->xoveradj)
	{
		
	new Wall(Vector3((y->x * mtilesize) - mtilesize / 2, y->y * mtilesize, 0.0f), q, mGame);
	}
}}



}



void Maze::MakeNewMaze()
{
	
	for (int i{ 0 }; i < mtilenum; i++)
	{
		for (int j{ 0 }; j < mtilenum; j++)
		{
			delete mtiles[i][j];
			mtiles[i][j] = new Tile(i, j);
		}
	}
	for (int i{ 0 }; i < mtilenum; i++)
	{
		for (int j{ 0 }; j < mtilenum; j++)
		{
			CreateAdjacent(i,j);
		}
	}

	
	while( !mGame->GetRenderer()->GetWalls().empty())
	{
		delete  mGame->GetRenderer()->GetWalls().back();
	}


	MakeMaze(mtiles[0][0]);
	MakeWalls();
	for (int i{ 0 }; i < mtilenum; i++)
	{
		for (int j{ 0 }; j < mtilenum; j++)
		{

			if (!mtiles[i][j]->xunderadj)
				mtiles[i][j]->madjacent.emplace_back(mtiles[i + 1][j]);
			if (!mtiles[i][j]->xoveradj)
				mtiles[i][j]->madjacent.emplace_back(mtiles[i - 1][j]);
			if (!mtiles[i][j]->yunderadj)
				mtiles[i][j]->madjacent.emplace_back(mtiles[i][j + 1]);
			if (!mtiles[i][j]->yoveradj)
				mtiles[i][j]->madjacent.emplace_back(mtiles[i][j - 1]);


		}
	}

	
}


void Maze::MakeMazeItems()
{
	//make pellets where fruits were
	Pellet* p;
	while (!mfruits.empty())
	{
		Fruit* h = mfruits.back();
		p = new Pellet(mGame);
		p->SetPosition(h->GetPos());
	
		mtiles[p->GetTileX()][p->GetTileY()]->SetCollectible(p);
		delete h;
	}
	
	//replace deleted pellets
	for (auto& j : mdeletedpositions)
	{
		p = new Pellet(mGame);
		p->SetPosition(j);
		mtiles[p->GetTileX()][p->GetTileY()]->SetCollectible(p);
	}
	mdeletedpositions.clear();

	//make new fruits
	Fruit* f;
	bool fcheck[mtilenum][mtilenum] = { false };
	for (int i{ 0 }; i < mfruitnum; i++)
	{
		f = new Fruit(mGame);

		//this should be automated
		int x = Random::get(0, mtilenum - 1);
		int y = Random::get(0, mtilenum - 1);

		while (fcheck[x][y])
		{
			
			 x = Random::get(0, mtilenum - 1);
			 y = Random::get(0, mtilenum - 1);
		}
		fcheck[x][y] = true;
		f->SetPosition(Vector3(x * mtilesize,y * mtilesize, 0.0f));
		delete mtiles[x][y]->mcollectible;
		mtiles[x][y]->mcollectible = f;
		mfruits.emplace_back(f);
	}

	//reset pacman
	int px = Random::get(1, mtilenum - 1), py = Random::get(1, mtilenum - 1);
	mGame->GetPac()->SetPosition(Vector3(px * mtilesize, py * mtilesize, 0.0f));
	mGame->GetPac()->ResetPelletsAndRocks();


	//make ghosts

	while (!mGame->GetGhosts().empty())
	{
		delete mGame->GetGhosts().back();
	}

	Ghost* g;
	for (int i{ 0 }; i < mghostnum; i++)
	{
		g = new Ghost(mGame);
		int x = Random::get(0, mtilenum - 1);
		int y = Random::get(0, mtilenum - 1);

		while (Math::Abs(x - px) < 3 || Math::Abs(y - py) < 3)
		{
			x = Random::get(0, mtilenum - 1);
			 y = Random::get(0, mtilenum - 1);
		}

		g->SetPosition(Vector3(x * mtilesize, y * mtilesize, 0.0f));
	}


}

void Maze::RemoveFruit(class Fruit* f)
{
	auto iter = std::find(mfruits.begin(), mfruits.end(), f);
	if (iter != mfruits.end())
	{
		mfruits.erase(iter);
	}
}

