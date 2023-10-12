#include "Component.h"
#include "Actor.h"
Component::Component(class Actor* c, int updateorder ):mOwner{c},mUpdateOrder{updateorder}
{
	mOwner->AddComponent(this);
}
 Component:: ~Component()
{
	 mOwner->RemoveComponent(this);
}

 Component::Component():mOwner{nullptr},mUpdateOrder{0}{}