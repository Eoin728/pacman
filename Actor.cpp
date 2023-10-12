#include "Actor.h"
#include "Component.h"
#include "Game.h"
#include "Maze.h"
Actor::Actor(class Game* c):mGame{c},mpos{Vector3::Zero},mrot{Quaternion::Identity},mscale{1.0f},
mRecomputeWorldTrans{true},mstate{EAlive}
{
	mGame->AddActor(this);
}
Actor::~Actor()
{
	mGame->RemoveActor(this);

	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float delta)
{
	if (mstate == EAlive)
	{
		ComputeWorldTransform();

		UpdateComponents(delta);
		ActorUpdate(delta);

		ComputeWorldTransform();
	}
}

void Actor::ComputeWorldTransform()
{
	if (mRecomputeWorldTrans)
	{
		mWorldTransform = Matrix4::CreateScale(mscale);
		mWorldTransform *= Matrix4::CreateRotation(mrot);
		mWorldTransform *= Matrix4::CreateTranslation(mpos);

		for (auto comp : mComponents)
		{
			comp->OnWorldTransform();
		}
	
	}
}


void Actor::AddComponent(class Component* c)
{
	int myorder = c->GetUpdateOrder();
	auto iter = mComponents.begin();

	while (iter != mComponents.end() && myorder > (*iter)->GetUpdateOrder())
	{
		++iter;
	}

	
	mComponents.emplace(iter, c);
}
void Actor::RemoveComponent(class Component*c )
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), c);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}



void Actor::UpdateComponents(float delta)
{
	for (auto comp : mComponents)
	{
		comp->Update(delta);
	}
}

int Actor::GetTileX() { return static_cast<int>(GetPos().x / GetGame()->GetMaze()->GetTileSize()); }
int Actor::GetTileY() { return static_cast<int>(GetPos().y / GetGame()->GetMaze()->GetTileSize()); }

class Tile* Actor::GetCurrTile()
{
	return mGame->GetMaze()->GetTiles()[GetTileX()][GetTileY()];
}