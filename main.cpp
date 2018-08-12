#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <memory>
#include <iostream>
#include "include/firework.h"

void addFireworks(std::vector<std::shared_ptr<Firework>>&, std::vector<bool>&);

int main() {
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Fireworks");

	// Fireworks
	std::vector<std::shared_ptr<Firework>> fr;
	std::vector<bool> done;

	// Text
	sf::Font font;
	font.loadFromFile("font/Opensans-Light.ttf");
	sf::Text instr;
	instr.setFont(font);
	instr.setString("Press space to launch fireworks!");
	instr.setCharacterSize(24);
	instr.setFillColor(sf::Color(224, 224, 224));
	instr.setPosition(sf::Vector2f(350, 30));

	sf::Event event;
	while (window.isOpen()) {
		while(window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					instr.setString("");
					break;
				case sf::Event::KeyPressed:
					addFireworks(fr, done);
					break;
				default:
					break;
			}
		}
		window.setFramerateLimit(60);

		window.clear(sf::Color(45, 45, 45));

		for (int i = 0; i < fr.size(); i++) {
			if (!done[i]) {

				// If done, delete and mark as done
				if (fr[i]->execute()) {
					// TODO: Error: Somehow this code is running even when firework isn't done
					// fr.erase(fr.begin() + i);
					done[i] = true;
				}

				fr[i]->draw(window);
			}
		}

		window.draw(instr);

		window.display();
	}

	return 0;
}

void addFireworks(std::vector<std::shared_ptr<Firework>>& fr, std::vector<bool>& done) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		for (int i = 0; i < done.size(); i++) {
			if (done[i]) {
				fr[i] = std::make_shared<Firework>();
				done[i] = false;
				return;
			}
		}

		fr.push_back(std::make_shared<Firework>());
		done.push_back(false);
	}
}
