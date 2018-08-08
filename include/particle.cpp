#include "particle.h"

Particle::Particle() {
	mass = 1;
}

void Particle::move() {
	point.position.x += velocity.x;
	point.position.y += velocity.y;
}

void Particle::acelerate(sf::Vector2f acc) {
	velocity.x += acc.x;
	velocity.x += acc.y;
}

void Particle::draw(sf::RenderWindow& win) {
	win.draw(point);
}
