#pragma once
#include "Math.h"
#include <vector>

class Actor
{
public:
	enum State
	{
		EAlive,
		EDead,
		EInactive

	};
	Actor(class Game*);
	virtual ~Actor();

	void Update(float delta);

	void ComputeWorldTransform();

	const Matrix4& GetWorldTrans() const{ return mWorldTransform; }
	State GetState() { return mstate; }
	class Game* GetGame() { return mGame; }

	void AddComponent(class Component*);
	void RemoveComponent(class Component*);

	//setters
	void SetPosition(const Vector3& a) { mpos = a;  mRecomputeWorldTrans = true; }
	void SetRotation(const Quaternion& q) { mrot = q; mRecomputeWorldTrans = true;}
	void SetScale(float s) { mscale = s; mRecomputeWorldTrans = true;}
	void SetState(State s) { mstate = s; }

	//getters
	const Vector3& GetPos()const { return mpos; }
	const Vector3& GetForward() const { return Vector3::Transform(Vector3::UnitX, mrot); }
	const Vector3& GetSide() const { return Vector3::Transform(Vector3::UnitY, mrot); }
	const Quaternion& GetRot() const { return mrot; }
	float GetScale() { return mscale; }

	virtual void ProcessInput(const class Input& state){}
	virtual void ActorUpdate(float delta) { }

	int GetTileX();
	int GetTileY();
	virtual class Tile* GetCurrTile();

private:
	
	void UpdateComponents(float delta);

 Vector3 mpos;
 Quaternion mrot;
 float mscale;

 State mstate;

 std::vector<class Component*> mComponents;

 bool mRecomputeWorldTrans;
 class Game* mGame;

 Matrix4 mWorldTransform;

};