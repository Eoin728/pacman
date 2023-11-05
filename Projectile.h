#pragma once
#include "Actor.h"

class Projectile:public Actor
{
public:
	Projectile(class Game* g);
	~Projectile();
	void ActorUpdate(float d) override;

private:
	
	class Movement* mmovie;

	float timer;


	class MeshComp* mmeshcomp;

	class SphereComp* msphere;
};