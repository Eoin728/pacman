#include "Fruit.h"
#include "Collectible.h"
#include "SphereComp.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Pacman.h"
#include "Maze.h"


Fruit::Fruit(class Game*g):Collectible{g}
{

	SetScale(10);
	Mesh* m = new Mesh();
	m->Load("Assets/rock.txt", GetGame()->GetRenderer());
	
	float r = m->GetRadius() * GetScale();
	MeshComp* mc = new MeshComp(this);
	mc->SetMesh(m);

	msphere = new SphereComp(this, r);
	

}

void Fruit::SpecialMove()
{
	
	GetGame()->GetPac()->AddRock();
}

Fruit::~Fruit()
{
	GetGame()->GetMaze()->RemoveFruit(this);
}
