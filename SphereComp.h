#pragma once
#include "Component.h"
#include "CollisionTime.h"
class SphereComp :public Component
{
public:
	SphereComp(class Actor*,float x);
	void Update(float delta) override;

	const Sphere& GetSphere() const { return msphere; }

private:
	Sphere msphere;
};