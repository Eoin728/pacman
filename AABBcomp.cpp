#include "AABBcomp.h"
#include "Actor.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Wall.h"
#include "Game.h"
AABBcomp::AABBcomp(class Actor*a):Component{a}
{

}

void AABBcomp::OnWorldTransform()
{
	mworld = morig;
	mworld.mmax = mOwner->GetScale() * mworld.mmax;
	mworld.mmin = mOwner->GetScale() * mworld.mmin;



}

AABBcomp::AABBcomp(class Wall* p,const Quaternion& rot,const Vector3& pos)
{
	mworld = p->GetGame()->GetRenderer()->GetMesh("Assets/Wall.txt")->GetAABB();
	
	mworld.mmax = p->GetScale() * mworld.mmax;
	mworld.mmin = p->GetScale() * mworld.mmin;

	mworld.Rotate(rot);
	mworld.mmax = mworld.mmax + pos;

	mworld.mmin = mworld.mmin + pos;
	

}