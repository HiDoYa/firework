#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main() {
	sf::Window window(sf::VideoMode(800, 600), "Fireworks");

	sf::Event event;
	while (window.isOpen()) {

		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}

	return 0;
}
