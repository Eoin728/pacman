#pragma once
#include "Math.h"

class Wall
{
public:
	Wall(Vector3 pos,Quaternion rot,class Game*);
	~Wall();

	const Matrix4& GetWorld() const { return mworldtrans; }
	class Game* GetGame() { return mGame; }
	class AABBcomp* Getboox() {
		return maabb;
	}
	
	float GetScale() const { return mscale; }
private:
	class AABBcomp* maabb;
	Matrix4 mworldtrans;
	class Game* mGame;
	float mscale;

	Vector3 mpos;
};