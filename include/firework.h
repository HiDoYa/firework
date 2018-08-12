#include <vector>

#ifndef FIREWORK
#define FIREWORK

class Firework {
	private:
		sf::CircleShape circle;
		sf::VertexArray circleTail;
		std::vector<sf::Vector2f> velocityTail;

		sf::VertexArray particles;
		std::vector<sf::Vector2f> velocity;
		std::vector<sf::Vector2f> acceleration;


		// Vary between each firework
		sf::Vector2f circleVelocity;
		sf::Vector2f wind; // Not used (deprecated)
		int numParticles;
		int startXInput;
		int magnitudeThreshold;
		int colorType;
		sf::Color initialColor;

		// Flags
		bool explode; // Flag for explosion
		bool initExplode;
		bool done;
	public:
		Firework();
		void setInitVars();
		void setColorType();
		void initialColorChooser();

		void circleTailAnimate();
		bool execute();

		void goUp();

		void initializeExplode();
		void adjustAcc();
		bool checkForCompletion();
		void setColor();
		void explodeHandle();

		void draw(sf::RenderWindow&);
};

#endif
