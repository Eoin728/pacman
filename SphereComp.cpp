#include "SphereComp.h"
#include "Actor.h"



#include "Fruit.h"
SphereComp::SphereComp(class Actor* a,float x):Component{a}
{
	msphere.mRadius = x;
	msphere.mCentre = Vector3::Zero;
}

void SphereComp::Update(float delta)
{
	
	msphere.mCentre = mOwner->GetPos();
	

}


