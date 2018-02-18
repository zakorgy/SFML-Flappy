#pragma once
#include <SFML/Graphics.hpp>

class Bird: public sf::Drawable
{
public:
	Bird(float windowWidth, float windowHeight);
	~Bird();
	float getPosX() { return shape.getPosition().x; }
	float getYPos() { return shape.getPosition().y; }

	void update(sf::Time delta);
	void moveUp();

private:
	sf::Clock clock;
	sf::Time lastTimeJumped;
	sf::CircleShape shape;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};

