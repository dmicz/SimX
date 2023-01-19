#pragma once
#include <vector>
#include <SDL.h>

class Entity;
class Block;

class PhysicsScene {
public:
	void AddEntity(Entity x);

	int GetNumEntities();
	Entity* GetEntity(int id);
private:
	std::vector<Entity> _entities;
};

class Entity {
public:
	void SetPosition(int x, int y);
	SDL_Rect GetBounds();
private:
	int _xPosition, _yPosition;
};

class Block : public Entity {
public:
	Block(int size) : _size(size) {};
private:
	int _size;
};