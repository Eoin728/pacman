#include "CapsuleComp.h"
#include "Actor.h"
#include "Game.h"
CapsuleComp::CapsuleComp(class Actor* a, float radius,float height):Component{a}
{
	mcapsule.mradius = radius;
	mheight = height;
}

void CapsuleComp::OnWorldTransform()
{
	mcapsule.mline.mstart = Vector3(0.0, 0.0f, 0);
	mcapsule.mline.mend = mcapsule.mline.mstart;
	mcapsule.mline.mend.z =  mheight;


	mcapsule.mline.mstart = mcapsule.mline.mstart + mOwner->GetPos();
	mcapsule.mline.mend = mcapsule.mline.mend + mOwner->GetPos();


}