#pragma once
#include <SFML/Graphics.hpp>
#include "Bird.h"

class Pipe: public sf::Drawable
{
public:
	Pipe(float width, float height, float xPos, bool upper);
	~Pipe();

	bool collidesWithBird(Bird& bird);
	float getXPos() { return shape.getPosition().x; }
	void update(sf::Time delta);
	bool shouldUpdate();

private:
	sf::RectangleShape shape;
	float height;
	float width;
	bool upper;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};

