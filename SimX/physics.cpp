#include "physics.h"
#include <algorithm>
#include <cmath>
#include <numbers>

bool PhysicsScene::AddBlock(Block x)
{
	for (int i = 0; i < _blocks.size(); i++) {
		bool xCollide = false, yCollide = false;
		if ((x.x > _blocks[i].x && x.x < (_blocks[i].x + _blocks[i].size)) ||
			((x.x + x.size) > _blocks[i].x && (x.x + x.size) < (_blocks[i].x + _blocks[i].size)) ||
			(x.size == _blocks[i].size && x.x == _blocks[i].x)) {
			xCollide = true;
		}

		if ((x.y > _blocks[i].y && x.y < (_blocks[i].y + _blocks[i].size)) ||
			((x.y + x.size) > _blocks[i].y && (x.y + x.size) < (_blocks[i].y + _blocks[i].size)) || 
				(x.size == _blocks[i].size && x.y == _blocks[i].y)) {
			yCollide = true;
		}

		if (xCollide && yCollide) {
			return false;
		}
	}
	x.velocity = Vector(0.0, 0.0);
	x.force = Vector(0.0, GRAVITY_FORCE);
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

int PhysicsScene::GetFloorHeight()
{
	return _floorY;
}

void PhysicsScene::RunForSeconds(int secondsToRun, double deltaTSeconds)
{
	for (int i = 0; i < _blocks.size(); i++) {
		_blocks[i].velocity += _blocks[i].force * deltaTSeconds;
		_blocks[i].x -= _blocks[i].velocity.x;
		_blocks[i].y -= _blocks[i].velocity.y;
	}
}


SDL_Rect* Block::GetSDLRect()
{
	SDL_Rect bounds = { static_cast<int>(x), static_cast<int>(y), size, size };
	return &bounds;
}

double Vector::GetMagnitude()
{
	return std::sqrt(x * y);
}

double Vector::GetAngleDeg()
{
	return std::atan(x/y) / 180 * std::numbers::pi;
}

Vector Vector::operator+(Vector a)
{
	return Vector(x + a.x, y + a.y);
}

void Vector::operator+=(Vector a)
{
	x += a.x;
	y += a.y;
}

Vector Vector::operator*(double a)
{
	return Vector(x * a, y * a);
}