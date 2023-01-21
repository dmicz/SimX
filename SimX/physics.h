#pragma once
#include <vector>
#include <SDL.h>

struct Block;

class PhysicsScene {
public:
	bool AddBlock(Block x);

	int GetNumBlocks();
	Block* GetBlock(int id);

	void RunForSeconds(int secondsToRun, int deltaTSeconds);
private:
	std::vector<Block> _blocks;
};

struct Block {
	SDL_Rect* GetSDLRect();
	double x, y;
	int size;
};

struct Force {
	double x, y;
	double GetMagnitude();
	double GetAngleDeg();
};