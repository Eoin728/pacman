#include "Paccam.h"
#include "Game.h"
#include "Renderer.h"
#include "Actor.h"

Paccam::Paccam(class Actor* a):Component{a,10000},mpitch{0},mpitchspeed{0},mmaxpitch{ Math::Pi / 3.0f }
{

}

void Paccam::Update(float delta)
{
	Vector3 eye = mOwner->GetPos();

	mpitch += mpitchspeed * delta;
	if (mpitch > mmaxpitch)
		mpitch = mmaxpitch;
	else if (mpitch < -mmaxpitch)
		mpitch = -mmaxpitch;
	Quaternion q(mOwner->GetSide(), mpitch);

	Vector3 target = Vector3::Transform(mOwner->GetForward(), q);
	target = 100.0f * target + eye;

	Vector3 up = Vector3::Transform(Vector3::UnitZ, q);

	Matrix4 view = Matrix4::CreateView(eye, target, up);

	mOwner->GetGame()->GetRenderer()->SetView(view);
	
}

ThirdCam::ThirdCam(class Actor* a) :Paccam{ a }, mfordis{ 20 }, mbackdis{ 40 },mupdis{115}
{

}


void ThirdCam::Update(float delta)
{

	Vector3 eye = mOwner->GetPos() - mbackdis * mOwner->GetForward() + mupdis * Vector3::UnitZ;
	
	Vector3 target = mOwner->GetPos() + mfordis * mOwner->GetForward();

	Matrix4 view = Matrix4::CreateView(eye, target, Vector3::UnitZ);

	mOwner->GetGame()->GetRenderer()->SetView(view);


}