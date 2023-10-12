#pragma once
#include <vector>

class Tile
{
public:
	Tile(int x, int y);
	friend class Maze;
	friend class Ghost;

	std::vector<Tile*> GetAdjacent() { return madjacent; }

	int GetX() { return x; }
	int GetY() { return y; }

	const bool Xoveradj() { return xoveradj; }
	const bool Xunderadj() { return xunderadj; }
	const bool Yoveradj() { return yoveradj; }
	const bool Yunderadj() { return yunderadj; }

	

	void SetCollectible(class Collectible* c) { mcollectible = c; }

	int GetPathCost() { return mpathlen; }
private:
	std::vector<Tile*> madjacent;

	bool xunderadj, xoveradj, yoveradj, yunderadj;

	bool visited;

	class Collectible* mcollectible;;

	int mpathlen;
	Tile* mprev;

	int x, y;
};