#include "physics.h"

void PhysicsScene::AddEntity(Entity x)
{
	_entities.push_back(x);
}

int PhysicsScene::GetNumEntities()
{
	return _entities.size();
}

Entity* PhysicsScene::GetEntity(int id)
{
	if (id < 0 || id > _entities.size()) return nullptr;
	return &_entities[id];
}

void Entity::SetPosition(int x, int y)
{
	_xPosition = x;
	_yPosition = y;
}

SDL_Rect Entity::GetBounds()
{
	SDL_Rect bounds = { _xPosition, _yPosition, }
	return ;
}
