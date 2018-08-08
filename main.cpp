#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "include/particle.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Fireworks");

	sf::Event event;
	while (window.isOpen()) {
		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();

		// window.draw(shape);

		window.display();
	}

	return 0;
}
