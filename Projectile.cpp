#include "Projectile.h"
#include "Movement.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "SphereComp.h"
#include "Ghost.h"
#include "CapsuleComp.h"
#include "Wall.h"
#include "AABBcomp.h"

#define GRAVITY 30

Projectile::Projectile(class Game* g):Actor{g},timer{0.0f}
{

	mmeshcomp = new MeshComp(this);
	Mesh* m = GetGame()->GetRenderer()->GetMesh("Assets/rock.txt");
	mmeshcomp->SetMesh(m);
	SetScale(2);
	mmovie = new Movement(this);
	Vector3 start = GetGame()->GetRenderer()->GetTrueCentreScreenPos();
	SetPosition(start);
	mmovie->SetForward(100.0f);
	msphere = new SphereComp(this, m->GetRadius() * GetScale());


	Vector3 end =  GetGame()->GetRenderer()->GetTrueCentreScreenPos(Vector3(0, 0, 0.9));
	Vector3 dir = Vector3::Normalize(end - start);
	float angle = Math::ACos(Vector3::Dot(dir, Vector3::UnitX));
	Vector3 axis = Vector3::Normalize(Vector3::Cross(Vector3::UnitX,dir));
	SetRotation(Quaternion(axis, angle));
	
}

void Projectile::ActorUpdate(float d)
{

	timer += d;
	if (timer > 2.0f)
	{
		SetState(Actor::EDead);
	}

	//if it collides with a ghost destroy the ghost and itself
	for (auto ghost : GetGame()->GetGhosts())
	{
		if (Intersect(msphere->GetSphere(), ghost->GetCapsule()->GetCapsule()))
		{
			ghost->SetState(Actor::EDead);
			SetState(Actor::EDead);
		}
	}

	//if it collides with a wall destroy it
	for (auto wall : GetGame()->GetRenderer()->GetWalls())
	{
		if (Intersect(wall->Getboox()->GetAABB(), msphere->GetSphere()))
		{
			SetState(Actor::EDead);
		}
	}


	Vector3 y = GetPos();
	y.z -= d * GRAVITY;
	SetPosition(y);
}


Projectile::~Projectile()
{
}