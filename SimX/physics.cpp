#include "physics.h"
#include <algorithm>

void PhysicsScene::AddBlock(Block x)
{
	for (int i = 0; i < _blocks.size(); i++) {
		if(x.GetBounds())
	}
	_blocks.push_back(x);
}

int PhysicsScene::GetNumBlocks()
{
	return _blocks.size();
}

Block* PhysicsScene::GetBlock(int id)
{
	if (id < 0 || id > _blocks.size()) return nullptr;
	return &_blocks[id];
}

void Block::SetPosition(int x, int y)
{
	_xPosition = std::max(0, x);
	_xPosition = std::max(0, y);
}

SDL_Rect* Block::GetBounds()
{
	SDL_Rect bounds = { _xPosition, _yPosition, _size, _size };
	return &bounds;
}
