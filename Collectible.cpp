#include "Collectible.h"
#include "SphereComp.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Pacman.h"

#include "Maze.h"

Collectible::Collectible(class Game* g) :Actor{ g },msphere{nullptr}
{
}

void Collectible::ActorUpdate(float del)
{
	

	msphere->GetSphere();

	if (Intersect(msphere->GetSphere()
		, GetGame()->GetPac()->GetSphere()->GetSphere()
	))
	{
		SetState(Actor::EDead);
		SpecialMove();
		GetGame()->GetMaze()->KillACollectible(GetPos());
		
	}
	
}

Collectible::~Collectible()
{
}
