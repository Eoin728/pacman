#pragma once
#include "Actor.h"


class Collectible :public Actor
{
public:
	Collectible(class Game* g);
	~Collectible();
	void ActorUpdate(float del) override;
	virtual void SpecialMove() {}
protected:
	class SphereComp* msphere;
};