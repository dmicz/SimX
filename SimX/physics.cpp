#include "physics.h"
#include <algorithm>
#include <cmath>
#include <numbers>

bool PhysicsScene::AddBlock(Block x)
{
	for (int i = 0; i < _blocks.size(); i++) {
		bool xCollide = false, yCollide = false;
		if ((x.x > _blocks[i].x && x.x < (_blocks[i].x + _blocks[i].size)) ||
			((x.x + x.size) > _blocks[i].x && (x.x + x.size) < (_blocks[i].x + _blocks[i].size))) {
			xCollide = true;
		}

		if ((x.y > _blocks[i].y && x.y < (_blocks[i].y + _blocks[i].size)) ||
			((x.y + x.size) > _blocks[i].x && (x.y + x.size) < (_blocks[i].y + _blocks[i].size))) {
			yCollide = true;
		}

		if (xCollide && yCollide) {
			return false;
		}
	}
	_blocks.push_back(x);
	return true;
}

int PhysicsScene::GetNumBlocks()
{
	return static_cast<int>(_blocks.size());
}

Block* PhysicsScene::GetBlock(int id)
{
	if (id < 0 || id > _blocks.size()) return nullptr;
	return &_blocks[id];
}

void PhysicsScene::RunForSeconds(int secondsToRun, int deltaTSeconds)
{

}


SDL_Rect* Block::GetSDLRect()
{
	SDL_Rect bounds = { static_cast<int>(x), static_cast<int>(y), size, size };
	return &bounds;
}

double Force::GetMagnitude()
{
	return std::sqrt(x * y);
}

double Force::GetAngleDeg()
{
	return std::atan(x/y) / 180 * std::numbers::pi;
}
