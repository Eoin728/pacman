#pragma once
#include "Actor.h"


class Ghost :public Actor
{
public:
	Ghost(class Game*);
	~Ghost();
	void ActorUpdate(float delta) override;
	
	
	bool IsHunting() { return mishunting; }

	class CapsuleComp* GetCapsule() { return mcapsule; }
protected:
	
	class Movement* mmovie;


	void Patrol(float& delta);
	void Hunt(float delta);
	void SetFacingDir(Tile* node, Tile* t);

	class Tile* mhuntnext;

	int maxlength;
	bool Centered();
	int Range();

	class Tile* mlast;
	bool mishunting;
	float timer;

	class CapsuleComp* mcapsule;

	class Tile* mprev;
};