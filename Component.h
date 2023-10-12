#pragma once

class Component
{
public:
	Component(class Actor*, int updateorder = 100);
	virtual ~Component();
	int GetUpdateOrder() { return mUpdateOrder; }
	virtual void Update(float delta){}
	Component();

	virtual void OnWorldTransform(){}
protected:
	int mUpdateOrder;
	class Actor* mOwner;
};