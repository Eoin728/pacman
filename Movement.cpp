#include "Movement.h"
#include "Math.h"
#include "Actor.h"


Movement::Movement(class Actor* a):Component{a,10},mforward{0},mstrafe{0},mangular{0.0f}
{

}


void Movement::Update(float delta)
{
	if (!Math::NearZero(mforward) || !Math::NearZero(mstrafe))
	{
		mOwner->SetPosition(mOwner->GetPos() + delta * mforward * mOwner->GetForward() +
			delta * mstrafe * mOwner->GetSide()
		);

	}

	if (!Math::NearZero(mangular))
	{
		
		Quaternion q = Quaternion(Vector3::UnitZ, mangular * delta);
		q = q * mOwner->GetRot();

		mOwner->SetRotation(q);
	}

}

