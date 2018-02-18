#include "Pipe.h"
#include "Constants.h"

const float UPDATE_SPEED = -15.f;

Pipe::Pipe(float width, float height, float xPos, bool upper): width(width), height(height), upper(upper)
{
	shape = sf::RectangleShape(sf::Vector2f(width, height));
	shape.setFillColor(sf::Color::Green);
	if (upper) {
		shape.setPosition(xPos, 0);
	} else {
		shape.setPosition(xPos, WINDOW_HEIGHT - height);
	}
}


Pipe::~Pipe()
{
}

bool Pipe::collidesWithBird(Bird & bird)
{
	float birdXPos = bird.getPosX() + BIRD_RADIUS / 2;
	float xPos = this->getXPos();
	if (xPos < birdXPos && birdXPos < (xPos + width)) {
		float birdYPos = bird.getYPos();
		if (upper) {
			return (birdYPos < height);
		} else {
			return ((WINDOW_HEIGHT - height) < birdYPos + BIRD_RADIUS);
		}
	} else {
		return false;
	}
}

void Pipe::update(sf::Time delta)
{
	shape.move(UPDATE_SPEED / delta.asMicroseconds(), 0);
}

bool Pipe::shouldUpdate()
{
	return (shape.getPosition().x + width) < 0;
}

void Pipe::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape);
}
