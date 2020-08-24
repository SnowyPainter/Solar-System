#pragma warning(disable : 26812)
#pragma warning(disable : 4244)
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "SolarSystemElement.h"

using namespace std;

enum class PlanetType {
	None,
	Mercury,
	Venus,
	Earth,
	Mars,
	Jupiter,
	Saturn,
	Uranus,
	Neptune,
};

class Planet: public SolarSystemElement {
private:
	Sun* sun;
	PlanetType type;

	sf::Clock c;

	float angle = 0;
	sf::Vector2f getSunPos() {
		return sun->GetShape().getPosition();
	}
	float getSunRadius() {
		return sun->GetShape().getRadius();
	}
	float getRadian(float degree) {
		return degree * 3.141592653589793238463/180;
	}
public:

	float RevolutionRadius = 0;
	float RevolutionSpeed = 0;
	float ScaleAlpha = 0;

	Planet() : SolarSystemElement(){ 
		type = PlanetType::None;	
		sun = nullptr;
	}
	Planet(PlanetType t, sf::CircleShape p, Sun* sun, float revolutionRadius = 0, float revolutionSpeed = 360) 
		:SolarSystemElement(p){
		type = t;
		this->sun = sun;
		RevolutionRadius = revolutionRadius;
		RevolutionSpeed = revolutionSpeed;
	}
	void SetSun(Sun* sun) {
		this->sun = sun;
	}
	float GetRevolutionPeriod(float relativePeriodSpeedOneSecond) {
		return relativePeriodSpeedOneSecond / RevolutionSpeed;
	}
	PlanetType GetType() {
		return type;
	}

	//Unused
	float DistanceFromSun() {
		sf::Vector2f sunPos = getSunPos();
		sf::Vector2f p = shape.getPosition();
		float sunRadius = getSunRadius();

		return sqrt( pow(sunPos.x + sunRadius - shape.getRadius() - p.x, 2) 
			+ pow(sunPos.y + sunRadius - shape.getRadius() - p.y, 2) );
	}

	void Revolution(float deltaTime) {
		sf::Time t = c.getElapsedTime();

		sf::Vector2f sunPos = getSunPos();
		float sunRadius = getSunRadius();

		float x = (RevolutionRadius + ScaleAlpha) * cos(getRadian(angle)) + sunPos.x + sunRadius - shape.getRadius();
		float y = (RevolutionRadius + ScaleAlpha) * sin(getRadian(angle)) + sunPos.y + sunRadius - shape.getRadius();
		
		shape.setPosition(sf::Vector2f(x,y));
		
		angle += RevolutionSpeed * deltaTime;

	}
	void Rotation() {

	}
};