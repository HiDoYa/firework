#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
	private:
		sf::Vector2f velocity;
		sf::Vertex point;
		int mass; // For F=ma

		// Tick of movement (velocity worth)
		void move();

		// Change velocity (must account for fps)
		void accelerate(sf::Vector2f);
	public:
		void draw(sf::RenderWindow&);
};

#endif
