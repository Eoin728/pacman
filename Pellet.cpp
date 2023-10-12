#include "Pellet.h"
#include "Mesh.h"
#include "SphereComp.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "Pacman.h"

Pellet::Pellet(class Game*g) :Collectible{ g }
{
	SetScale(5);
	Quaternion q = Quaternion(Vector3::UnitX, 3 * Math::HalfPi / 4);
	q = q * Quaternion(Vector3::UnitZ, 3 * Math::HalfPi / 4);
	SetRotation(q);
	Mesh* m = new Mesh();
	m->Load("Assets/DUBE.txt", GetGame()->GetRenderer());
	//	m->Load("Assets/Sphere.gpmesh", GetGame()->GetRenderer());
	float r = m->GetRadius() * GetScale();
	MeshComp* mc = new MeshComp(this);
	mc->SetMesh(m);

	msphere = new SphereComp(this, r);
}

void Pellet::SpecialMove()
{
	GetGame()->GetPac()->AddPellet();

}