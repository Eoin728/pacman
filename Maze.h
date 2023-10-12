#pragma once
#include <vector>
#include <array>
#include<random>
#include "Math.h"

#define TILENUM 20

class Maze
{
public:
	Maze(class Game*);
	~Maze();

	void MakeNewMaze();
	
	static	const int mtilenum{ 10 };
	std::array<std::array<class Tile*, mtilenum>, mtilenum> GetTiles() { return mtiles; }

	const int GetTileSize() const { return mtilesize; }
	const int GetTileNum() const { return mtilenum; }
	void MakeMazeItems();
	void RemoveFruit(class Fruit*);
	const int GetFruitNum() { return mfruitnum; }
	void KillACollectible( Vector3 m) { mdeletedpositions.push_back(m); }
private:
	void MakeWalls();
	void MakeMaze(class Tile* curr);
	void CreateAdjacent(int i,int j);
	***REMOVED***
	  int mtilesize;

	  //this maybe not needed
	  std::vector<class Fruit*> mfruits;

	std::array<std::array<class Tile*,mtilenum>,mtilenum> mtiles;
	const int mfruitnum{ 20 };
	
	class Game* mGame;
	const int mghostnum{ 6 };
	std::vector<  Vector3 > mdeletedpositions;

};