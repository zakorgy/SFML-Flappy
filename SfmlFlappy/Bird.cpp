#include "Bird.h"
#include "Constants.h"

const float FALLING_SPEED = 15.f;
const float JUMP_SIZE = 80.f;
const float CEIL_TRESHOLD = 50.f;
const float SECONDS_BETWEEN_PRESSES = 0.1f;

Bird::Bird(float windowWidth, float windowHeight)
{
	sf::CircleShape circle(BIRD_RADIUS);
	circle.setFillColor(sf::Color::Yellow);
	circle.setPosition(windowWidth / 2 - (BIRD_RADIUS / 2), windowHeight / 2 - (BIRD_RADIUS / 2));
	shape = circle;
	clock = sf::Clock();
	lastTimeJumped = clock.getElapsedTime();
}

Bird::~Bird()
{
}

void Bird::update(sf::Time delta) {
	shape.move(0.0, FALLING_SPEED / delta.asMicroseconds());
}

void Bird::moveUp()
{
	if (getYPos() - CEIL_TRESHOLD > 0) {
		sf::Time time = clock.getElapsedTime();
		float elapsed = (time - lastTimeJumped).asSeconds();
		if (elapsed > SECONDS_BETWEEN_PRESSES) {
			shape.move(0.f, -JUMP_SIZE);
			lastTimeJumped = clock.getElapsedTime();
		}
	}
}

void Bird::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}
