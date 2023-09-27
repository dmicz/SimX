#include "physics.h"
#include <algorithm>
#include <cmath>
#include <numbers>

ParticleSimulation::ParticleSimulation(int ticksPerSecond) {
	_ticksPerSecond = ticksPerSecond;
}

void ParticleSimulation::runTick() {
	for (int i = 0; i < _particles.size(); i++) {
		_particles[i].position += _particles[i].velocity * (1.0 / _ticksPerSecond);
	}
}

void ParticleSimulation::runTicks(int ticks) {
	for (int i = 0; i < ticks; i++) {
		runTick();
	}
}

void ParticleSimulation::addParticle(Particle particle) {
	_particles.push_back(particle);
}

void ParticleSimulation::getParticlePositions() {
	std::vector<Vector2D> positions;
	for (int i = 0; i < _particles.size(); i++) {
		positions.push_back(_particles[i].position);
	}
}

double Vector2D::GetMagnitude()
{
	return std::sqrt(x * y);
}

double Vector2D::GetAngleDeg()
{
	return std::atan(x / y) / 180 * std::numbers::pi;
}

Vector2D Vector2D::operator+(Vector2D a)
{
	return Vector2D(x + a.x, y + a.y);
}

void Vector2D::operator+=(Vector2D a)
{
	x += a.x;
	y += a.y;
}

Vector2D Vector2D::operator*(double a)
{
	return Vector2D(x * a, y * a);
}

int Vector2D::operator*(Vector2D a)
{
	return (x * a.x + y * a.y);
}


Vector2D::Vector2D(double x, double y)
	: x(x), y(y)
{
}


bool Vector2D::operator==(const Vector2D& other) const
{
	return x == other.x && y == other.y;
}
