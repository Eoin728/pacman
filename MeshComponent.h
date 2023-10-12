#pragma once
#include "Component.h"
#include "Actor.h"
class MeshComp:public Component
{
public:
	MeshComp(class Actor *a);
	~MeshComp();

	void Draw(class Shader* s);
	void SetMesh(class Mesh* d) { mMesh = d; }
	const Matrix4 Getworld() { return mOwner->GetWorldTrans(); }

	void SetVisible(bool x) { misvisible = x; }
	bool IsVisible() { return misvisible; }
public:
	class Mesh * mMesh;
	bool misvisible;
};