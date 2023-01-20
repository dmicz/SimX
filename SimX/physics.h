#pragma once
#include <vector>
#include <SDL.h>

class Block;

class PhysicsScene {
public:
	void AddBlock(Block x);

	int GetNumBlocks();
	Block* GetBlock(int id);

	void simulationTick();
	void runForTicks();
private:
	std::vector<Block> _blocks;
};

class Block {
public:
	Block(int x, int y, int size) : _xPosition(x), _yPosition(y), _size(size) {};
	void SetPosition(int x, int y);
	SDL_Rect* GetBounds();
private:
	int _xPosition, _yPosition;
	int _size;
};