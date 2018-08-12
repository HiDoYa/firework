#include <SFML/Graphics.hpp>
#include "firework.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>

const float PI = 3.14;
const int FPS = 60;
const int SCREEN_HEIGHT = 768;
const int SCREEN_WIDTH = 1024;
const float GRAV = 9.8 / FPS;

enum colorTypes {SOLID_COLOR, RANDOM_COLOR, FADE_OPACITY};

Firework::Firework() {
	setInitVars();

	// Flags
	initExplode = false;
	explode = false;
	done = false;

	// Set circle
	circle.setRadius(5);
	circle.setPosition(startXInput, SCREEN_HEIGHT);
	circle.setFillColor(initialColor);
	circleTail.setPrimitiveType(sf::PrimitiveType::Points);

	// Set particles
	particles.resize(numParticles);
	acceleration.resize(numParticles);
	velocity.resize(numParticles);
	particles.setPrimitiveType(sf::PrimitiveType::Points);
}

void Firework::setInitVars() {
	circleVelocity = sf::Vector2f(rand() % (2 + 2 + 1) - 2, -(rand() % (15 - 8 + 1) + 8)); // -2 to 2 for x, -8 to -15 for y
	wind = sf::Vector2f(0, 0); // -0.02 to 0.02 for x
	numParticles = 360 * (rand() % (20 - 10 + 1) + 10); // lower bound 5, upper bound 10
	startXInput = rand() % (SCREEN_WIDTH - 100 - 100) + 100; // 100 margin on left and right side
	magnitudeThreshold = rand() % (9 - 2 + 1) + 2; // lower bound 2, upper bound 9
	initialColorChooser();
	setColorType();
}

void Firework::setColorType() {
	int randColorType = rand() % 3;
	switch (randColorType) {
		case 0:
			colorType = SOLID_COLOR;
			break;
		case 1:
			colorType = RANDOM_COLOR;
			break;
		case 2:
			colorType = FADE_OPACITY;
			break;
	}
}

void Firework::initialColorChooser() {
	int colorChoose = rand() % 6;
	switch (colorChoose) {
		case 0:
			initialColor = sf::Color::Red;
			break;
		case 1:
			initialColor = sf::Color::Blue;
			break;
		case 2:
			initialColor = sf::Color::Green;
			break;
		case 3:
			initialColor = sf::Color::Yellow;
			break;
		case 4:
			initialColor = sf::Color::Magenta;
			break;
		case 5:
			initialColor = sf::Color::Cyan;
			break;
	}
}

bool Firework::execute() {
	if (!explode) {
		goUp();
		circleTailAnimate();
	} else {
		explodeHandle();
	}
	return done;
}

void Firework::circleTailAnimate() {
	int last = circleTail.getVertexCount();
	circleTail.resize(last + 2);
	velocityTail.resize(last + 2);
	for (int i = last; i < circleTail.getVertexCount(); i++) {
		circleTail[i].position = circle.getPosition();
		circleTail[i].color = initialColor;
		velocityTail[i] = -circleVelocity;
		velocityTail[i].x += rand() % 6 - 3;
		velocityTail[i].y += rand() % 6 - 3;
	}


	for (int i = 0; i < circleTail.getVertexCount(); i++) {
		velocityTail[i].y += GRAV;
		circleTail[i].position += velocityTail[i];
	}
}

void Firework::goUp() {
	// Doesn't use particles yet (just a circle)

	circleVelocity.x += wind.x;
	circleVelocity.y += wind.y + GRAV;

	circle.move(circleVelocity.x, circleVelocity.y);

	if (circleVelocity.y >= 0) {
		explode = true;
	}
}

void Firework::initializeExplode() {
	for (int i = 0; i < numParticles; i++) {
		particles[i].color = initialColor;
		particles[i].position = circle.getPosition();

		float magnitude = rand() % magnitudeThreshold;
		magnitude += ((float)rand() / (float)(RAND_MAX)); // To add decimals

		// Must convert i to radians
		float accX = magnitude * cos(i * PI / 180.0) + wind.x;
		float accY = magnitude * sin(i * PI / 180.0) + GRAV + wind.y;
		acceleration[i] = sf::Vector2f(accX, accY);

		initExplode = true;
	}
}

void Firework::adjustAcc() {
	for (int i = 0; i < numParticles; i++) {
		acceleration[i].x = (acceleration[i].x + 0 + wind.x) / 2.0;
		acceleration[i].y = (acceleration[i].y + GRAV + wind.y) / 2.0;
	}
}

bool Firework::checkForCompletion() {
	done = true;
	for (int i = 0; i < numParticles; i++) {
		if (particles[i].position.y < SCREEN_HEIGHT) {
			done = false;
			break;
		}
	}
}

void Firework::setColor() {
	for (int i = 0; i < numParticles; i++) {

		int rnNum[4];
		switch (colorType) {
			case SOLID_COLOR:
				rnNum[0] = 0;
				rnNum[1] = 0;
				rnNum[2] = 0;
				rnNum[3] = 0;
				break;
			case RANDOM_COLOR:
				rnNum[0] = rand() % 3 - 1;
				rnNum[1] = rand() % 3 - 1;
				rnNum[2] = rand() % 3 - 1;
				rnNum[3] = 0;
				break;
			case FADE_OPACITY:
				rnNum[0] = 0;
				rnNum[1] = 0;
				rnNum[2] = 0;
				rnNum[3] = -5;
				break;
		}

		particles[i].color.r += rnNum[0];
		particles[i].color.g += rnNum[1];
		particles[i].color.b += rnNum[2];

		if (particles[i].color.a + rnNum[3] <= 0) {
			particles[i].color.a = 0;
		} else {
			particles[i].color.a += rnNum[3];
		}

	}
}

void Firework::explodeHandle() {
	if (!initExplode) {
		initializeExplode();
	} else {
		adjustAcc();
	}

	for (int i = 0; i < numParticles; i++) {
		velocity[i].x += acceleration[i].x;
		velocity[i].y += acceleration[i].y;

		particles[i].position.x += velocity[i].x;
		particles[i].position.y += velocity[i].y;
	}

	setColor();

	checkForCompletion();
}

void Firework::draw(sf::RenderWindow& win) {
	if (done) {
		// Do nothing
	} else if (explode) {
		// Only draw particles
		win.draw(particles);
	} else {
		// Only draw circle
		win.draw(circle);
		win.draw(circleTail);
	}
}
