#pragma once
#include "Actor.h"

class Projectile:public Actor
{
public:
	Projectile(class Game* g);
	~Projectile();
	void ActorUpdate(float d) override;

private:
	//once again i propose adding this to actor
	class Movement* mmovie;

	float timer;

	//maybe add the meshcomp to actor??
	class MeshComp* mmeshcomp;

	class SphereComp* msphere;
};