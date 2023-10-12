#pragma once
#include "Component.h"
#include "CollisionTime.h"
class AABBcomp:public Component
{
public:
	AABBcomp(class Actor*);
	AABBcomp(class Wall* p,const Quaternion& rot,const Vector3& pos);
	void SetAABB(const AABB& f) { morig = f; }
	const AABB& GetAABB()const { return mworld; }

	void OnWorldTransform() override;

private:
	AABB mworld;
	AABB morig;

};