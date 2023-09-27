#include "physics.h"
#include <algorithm>
#include <cmath>
#include <numbers>

ParticleSimulation::ParticleSimulation(int ticksPerSecond) {
	m_ticksPerSecond = ticksPerSecond;
}

void ParticleSimulation::runTick() {
	for (int i = 0; i < m_particles.size(); i++) {
		m_particles[i].position += m_particles[i].velocity * (1.0 / m_ticksPerSecond);
	}
}

void ParticleSimulation::runTicks(int ticks) {
	for (int i = 0; i < ticks; i++) {
		runTick();
	}
}

void ParticleSimulation::addParticle(Particle particle) {
	m_particles.push_back(particle);
}

int ParticleSimulation::numberOfParticles()
{
	return m_particles.size();
}

void ParticleSimulation::setParticleVelocity(int index, Vector2D velocity)
{
	m_particles[index].velocity = velocity;
}

std::vector<Vector2D> ParticleSimulation::getParticlePositions() {
	std::vector<Vector2D> positions;
	for (int i = 0; i < m_particles.size(); i++) {
		positions.push_back(m_particles[i].position);
	}
	return positions;
}

double Vector2D::GetMagnitude()
{
	return std::sqrt(x * x + y * y);
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

Vector2D Vector2D::operator-(Vector2D a)
{
	return Vector2D(x - a.x, y - a.y);
}

void Vector2D::operator-=(Vector2D a)
{
	x -= a.x;
	y -= a.y;
}

Vector2D Vector2D::operator*(double a)
{
	return Vector2D(x * a, y * a);
}

double Vector2D::operator*(Vector2D a)
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
