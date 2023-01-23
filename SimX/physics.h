#pragma once
#include <vector>
#include <SDL.h>

const double GRAVITY_FORCE = -500;

struct Block;
struct Force;

class PhysicsScene {
public:
	PhysicsScene(int xMax, int yMax, int floorHeight) :
		_xMax(xMax), _yMax(yMax), _floorY(yMax - floorHeight) {};
	bool AddBlock(Block x);

	int GetNumBlocks();
	Block* GetBlock(int id);

	int GetFloorHeight();

	void RunForSeconds(double secondsToRun, double deltaTSeconds);
private:
	std::vector<Block> _blocks;
	int _floorY;
	int _xMax, _yMax;
};

struct Vector {
	double x, y;
	double GetMagnitude();
	double GetAngleDeg();
	Vector operator+(Vector a);
	void operator+=(Vector a);
	Vector operator*(double a);
};

struct Block {
	SDL_Rect* GetSDLRect();
	double x, y;
	int size;
	Vector velocity;
	Vector force;
};
