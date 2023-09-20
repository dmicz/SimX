#include "physics.h"
#include <algorithm>
#include <cmath>
#include <numbers>



double Vector::GetMagnitude()
{
	return std::sqrt(x * y);
}

double Vector::GetAngleDeg()
{
	return std::atan(x / y) / 180 * std::numbers::pi;
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