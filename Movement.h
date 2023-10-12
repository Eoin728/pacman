#pragma once
#include "Component.h"

class Movement :public Component
{
public:
	Movement(class Actor*);

	void SetSide(float f) { mstrafe = f; }
	void SetRot(float f) { mangular = f; }
	void SetForward(float f) { mforward = f; }
	void Update(float delta) override;



private:
	float mforward;
	float mstrafe;
	float mangular;
};