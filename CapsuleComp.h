#pragma once
#include "Component.h"
#include "CollisionTime.h"

class CapsuleComp :public Component
{
public:
	CapsuleComp(class Actor* a,float x,float);

	void OnWorldTransform() override;

	const Capsule& GetCapsule() const { return mcapsule; }
private:
	Capsule mcapsule;
	float mheight;

};