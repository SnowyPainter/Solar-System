#pragma once
#include <SFML/Graphics.hpp>

class SolarSystemElement {
protected:
	sf::CircleShape shape;

public:
	SolarSystemElement() {}
	SolarSystemElement(sf::CircleShape shape) {
		this->shape = shape;
	}
	void SizeAlphaRadius(float alpha) {
		float r = shape.getRadius();
		if (r + alpha > 0.0f) {
			shape.setRadius(r + alpha);
			shape.setPosition(shape.getPosition() - sf::Vector2f(alpha, alpha));
		}
	}
	void SetRadius(float r) {
		shape.setRadius(r);
	}
	sf::CircleShape GetShape() {
		return shape;
	}
};