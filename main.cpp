#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <memory>
#include <iostream>
#include "include/firework.h"

void addFireworks(std::vector<std::shared_ptr<Firework>>&, std::vector<bool>&, bool&, sf::Text&);
void fire(std::vector<std::shared_ptr<Firework>>&, std::vector<bool>&);

int main() {
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Fireworks");

	// Fireworks
	std::vector<std::shared_ptr<Firework>> fr;
	std::vector<bool> done;
	bool autoFire = false;

	// Text
	sf::Font font;
	font.loadFromFile("font/Opensans-Light.ttf");
	sf::Text instr;
	instr.setFont(font);
	instr.setString("Press space to launch fireworks!");
	instr.setCharacterSize(24);
	instr.setFillColor(sf::Color(224, 224, 224));
	instr.setPosition(sf::Vector2f(350, 30));

	sf::Text toggle;
	toggle.setFont(font);
	toggle.setString("Press a to turn on autofire");
	toggle.setCharacterSize(16);
	toggle.setFillColor(sf::Color(170, 203, 255));
	toggle.setPosition(sf::Vector2f(430, 70));


	sf::Event event;
	while (window.isOpen()) {
		while(window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					instr.setString("");
					toggle.setString("");
					break;
				case sf::Event::KeyPressed:
					addFireworks(fr, done, autoFire, toggle);
					break;
				default:
					break;
			}
		}
		window.setFramerateLimit(60);

		// Comment this out for trippy effect
		window.clear(sf::Color(45, 45, 45));

		// 1 in 60 chance of firing every frame
		if (autoFire && rand() % 60 == 0) {
			fire(fr, done);
		}

		for (int i = 0; i < fr.size(); i++) {
			if (!done[i]) {

				// If done, delete and mark as done
				if (fr[i]->execute()) {
					// Error: this code is running even when firework isn't done
					// fr.erase(fr.begin() + i);
					done[i] = true;
				}

				fr[i]->draw(window);
			}
		}

		window.draw(instr);
		window.draw(toggle);

		window.display();
	}

	return 0;
}

void addFireworks(std::vector<std::shared_ptr<Firework>>& fr, std::vector<bool>& done, bool& autoFire, sf::Text& toggle) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		fire(fr, done);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		autoFire = !autoFire;
		if (autoFire) {
			toggle.setString("Press a to turn off autofire");
			toggle.setFillColor(sf::Color(255, 170, 170));
		} else {
			toggle.setString("Press a to turn on autofire");
			toggle.setFillColor(sf::Color(170, 203, 255));
		}
	}
}

void fire(std::vector<std::shared_ptr<Firework>>& fr, std::vector<bool>& done) {
	// Release 1-3 fireworks at once
	for (int i = 0; i < rand() % 3 + 1; i++) {
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
