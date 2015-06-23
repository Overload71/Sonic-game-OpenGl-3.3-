#include "CollisionManager.h"


CollisionManager::CollisionManager(void)
{
}


CollisionManager::~CollisionManager(void)
{
}

void CollisionManager::UpdateCollisions()
{
	for (int i = 0; i < collidableModels.size(); i++)
	{
		for (int j = i+1; j < collidableModels.size(); j++)
		{
			if (collidableModels[i]->GetBoundingBox().IsIntersecting(collidableModels[j]->GetBoundingBox()))
			{
				collidableModels[i]->Collided(collidableModels[j]->objectType);
				collidableModels[j]->Collided(collidableModels[i]->objectType);
			}
		}
	}
}

void CollisionManager::SetCollidableModels(std::vector<CollidableModel*> fCollidableModels)
{
	collidableModels = fCollidableModels;
}

void CollisionManager::AddCollidableModel(CollidableModel* model)
{
	collidableModels.push_back(model);
}

void CollisionManager::RemoveCollidableModel(int modelIndex)
{
	collidableModels.erase(collidableModels.begin()+modelIndex);
}

void CollisionManager::RemoveCollidableModel(CollidableModel* model)
{
	for (int i = 0; i < collidableModels.size(); i++)
	{
		//comparing the addresses.
		if (model == collidableModels[i])
		{
			RemoveCollidableModel(i);
			return;
		}
	}
}
