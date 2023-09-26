#pragma once
#include <vector>
#include <SDL.h>

struct Particle {
	Vector2D position, velocity; // m, m/s
	double mass; // kg
};

class ParticleSimulation {

	ParticleSimulation(int ticksPerSecond);

	void runTick();
	void runTicks(int ticks);

	void addParticle(Particle particle);

	std::vector<Vector2D> getParticlePositions();
private:
	int _ticksPerSecond;

	std::vector<Particle> _particles;
};

struct Vector2D {
	double x, y;
	double GetMagnitude();
	double GetAngleDeg();
	Vector2D operator+(Vector2D a);
	void operator+=(Vector2D a);
	Vector2D operator*(double a);
	int operator*(Vector2D a);
	Vector2D(double x, double y);
	bool operator==(const Vector2D& other) const;
};