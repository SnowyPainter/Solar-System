#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class SolarSystemElement {
protected:
	sf::CircleShape shape;
public:
	wstring Description = L"";

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
	void SetPosition(sf::Vector2f pos) {
		shape.setPosition(pos);
	}
	sf::Vector2f GetPosition() {
		return shape.getPosition();
	}
	void SetRadius(float r) {
		shape.setRadius(r);
	}
	float GetRadius() {
		return shape.getRadius();
	}
	sf::CircleShape GetShape() {
		return shape;
	}
	sf::CircleShape* GetReadableShape() {
		return &shape;
	}
};