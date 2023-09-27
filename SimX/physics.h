#pragma once
#include <vector>
#include <SDL.h>

struct Vector2D {
	double x, y;
	double GetMagnitude();
	double GetAngleDeg();
	Vector2D operator+(Vector2D a);
	void operator+=(Vector2D a);
	Vector2D operator-(Vector2D a);
	void operator-=(Vector2D a);
	Vector2D operator*(double a);
	double operator*(Vector2D a);
	Vector2D(double x, double y);
	bool operator==(const Vector2D& other) const;
};

struct Particle {
	Vector2D position, velocity; // m, m/s
	double mass; // kg
};

class ParticleSimulation {
public:
	ParticleSimulation(int ticksPerSecond);

	void runTick();
	void runTicks(int ticks);

	void addParticle(Particle particle);

	int numberOfParticles();
	void setParticleVelocity(int index, Vector2D velocity);

	std::vector<Vector2D> getParticlePositions();
private:
	int m_ticksPerSecond;

	std::vector<Particle> m_particles;
};
