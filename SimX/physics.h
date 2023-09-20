#pragma once
#include <vector>
#include <SDL.h>


struct Vector {
	double x, y;
	double GetMagnitude();
	double GetAngleDeg();
	Vector operator+(Vector a);
	void operator+=(Vector a);
	Vector operator*(double a);
};