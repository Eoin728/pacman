#include "Wall.h"
#include "Renderer.h"
#include "Game.h"
#include "AABBcomp.h"

Wall::Wall(Vector3 pos, Quaternion rot, class Game* d):mGame{d},mpos{pos},mscale{1.0f}
{
	mworldtrans = Matrix4::CreateScale(mscale);
	mworldtrans *= Matrix4::CreateRotation(rot);
	mworldtrans *= Matrix4::CreateTranslation(pos);


	maabb = new AABBcomp(this, rot, pos);

	mGame->GetRenderer()->AddWall(this);
}
Wall::~Wall()
{
	mGame->GetRenderer()->RemoveWall(this);
}