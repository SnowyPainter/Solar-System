#pragma warning(disable : 26812)
#pragma warning(disable : 4244)
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace std;

enum class PlanetType {
	Mercury
};

class Planet {
private:
	Sun* sun;
	PlanetType type;
	sf::CircleShape planet; //It must be textrued

	float angle = 0;
	sf::Vector2f getSunPos() {
		return sun->GetShape().getPosition();
	}
	float getSunRadius() {
		return sun->GetShape().getRadius();
	}
	float getDegrees(float radian) {
		return radian * (180.0 / 3.141592653589793238463);
	}
public:
	float RevolutionRadius = 0;
	float RevolutionSpeed = 0;

	Planet() { }
	Planet(PlanetType t, sf::CircleShape p, Sun* sun, float revolutionRadius = 0, float revolutionSpeed = 0) {
		type = t;
		planet = p;
		this->sun = sun;
		RevolutionRadius = revolutionRadius;
		RevolutionSpeed = revolutionSpeed;
	}
	void SetSun(Sun* sun) {
		this->sun = sun;
	}
	float DistanceFromSun() {
		sf::Vector2f sunPos = getSunPos();
		sf::Vector2f p = planet.getPosition();
		float sunRadius = getSunRadius();

		return sqrt(pow(sunPos.x + sunRadius - planet.getRadius() - p.x, 2) + pow(sunPos.y + sunRadius - planet.getRadius() - p.y, 2));
	}
	void Revolution() {

		sf::Vector2f sunPos = getSunPos();
		float sunRadius = getSunRadius();

		float x = RevolutionRadius * cos(getDegrees(angle)) + sunPos.x + sunRadius - planet.getRadius();
		float y = RevolutionRadius * sin(getDegrees(angle)) + sunPos.y + sunRadius - planet.getRadius();
		
		planet.setPosition(sf::Vector2f(x,y));
		angle+=RevolutionSpeed; //360 1

	}
	void Rotation() {

	}
	sf::CircleShape GetShape() {
		return planet;
	}
};