#pragma warning(disable : 26812)
#pragma warning(disable : 4244)
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sun.h"
#include "Planet.h"

using namespace std;

class SolarSystem {
private:
	Sun sun; //It must be textrued
	Planet* planets; //수금지화목토천
	const float DEFAULT_SUN_RADIUS = 20.0f;
	const sf::Color DEFAULT_SUN_COLOR = sf::Color(240, 255, 254);

	sf::CircleShape sunCenterPointer = sf::CircleShape(1);
	bool enableSunCenterPointer = false;
	
	//Temporary creator
	Planet CreatePlanet(PlanetType type, sf::Color color, float radius, float revolutionRadius) {
		sf::CircleShape mercuryShape(radius);
		mercuryShape.setFillColor(color);

		return Planet(type, mercuryShape, &sun, revolutionRadius);
	}
public:
	const int MAX_PLANETS = 5;
	SolarSystem(float width, float height) {
		this->planets = new Planet[MAX_PLANETS];

		sf::CircleShape sunShape(DEFAULT_SUN_RADIUS);
		sunShape.setFillColor(DEFAULT_SUN_COLOR);
		sunShape.setPosition((width - DEFAULT_SUN_RADIUS) / 2, (height - DEFAULT_SUN_RADIUS) / 2);


		sun = Sun(sunShape);
		for(int i = 0;i < MAX_PLANETS;i++)
			planets[i] = CreatePlanet(PlanetType::Mercury, sf::Color(255,255,255), 5+i*3, i*70+50);

		sunCenterPointer.setFillColor(sf::Color(0, 0, 0));
		sunCenterPointer.setPosition(sf::Vector2f(sun.GetShape().getPosition().x + sun.GetShape().getRadius(),
			sun.GetShape().getPosition().y + sun.GetShape().getRadius()));
		
	}
	void ToggleSunCenterPointer() {
		enableSunCenterPointer = !enableSunCenterPointer;
	}
	void Operate() {
		for (int i = 0; i < MAX_PLANETS; i++) {
			planets[i].Revolution();
		}

		sun.Rotate();
	}
	void Draw(sf::RenderWindow* window) {

		for (int i = 0; i < MAX_PLANETS; i++) {
			window->draw(planets[i].GetShape());
		}

		window->draw(sun.GetShape());
		
		if (enableSunCenterPointer)
			window->draw(sunCenterPointer);
	}

	void AddPlanet() {  } //케플러 운동법칙 + 미적분 + 삼각비 활용
};