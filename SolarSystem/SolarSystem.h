#pragma warning(disable : 26812)
#pragma warning(disable : 4244)
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sun.h"
#include "Planet.h"

using namespace std;

const float DEFAULT_SUN_RADIUS = 45.0f;
const int MAX_PLANETS = 8; //8
const int DISTANCE_FROM_SUN_K = 40;
const int RADIUS_K = 3;
const float OrbitalPeriodBySecond = 360.0f;

class SolarSystem {
private:
	Sun sun; //It must be textrued
	Planet* planets; //수금지화목토천해
	const sf::Color DEFAULT_SUN_COLOR = sf::Color(240, 255, 254);

	struct planetData {
		float radius;
		float revolutionRadius;
		float revoleCycleSpeed;
	};
	//Inital Values
	planetData planetDatas[8] = {
		//Radius, Revolution Radius, Revolution Speed
		{ 0.4f, 0.5f, },
		{ 0.9f, 0.82f,  },
		{ 1.0f, 1.0f, },
		{ 0.8f, 1.52f, },
		{ 6.2f, 2.5f,  },
		{ 5.4f, 7.18f,  },
		{ 2.5f, 9.4f,  },
		{ 1.9f, 13.2f, },
	};
	PlanetType planetList[8] = {
		PlanetType::Mercury,
		PlanetType::Venus,
		PlanetType::Earth,
		PlanetType::Mars,
		PlanetType::Jupiter,
		PlanetType::Saturn,
		PlanetType::Uranus,
		PlanetType::Neptune
	};
	sf::Color planetColors[8] = {
		sf::Color(219, 128, 0),
		sf::Color(227, 204, 0),
		sf::Color(41, 147, 217),
		sf::Color(204, 41, 0),
		sf::Color(135, 70, 0),
		sf::Color(150, 106, 57),
		sf::Color(45, 237, 224),
		sf::Color(0, 87, 168)
	};

	float cycleToRelativeSpeed(float relativeEarth) {
		return OrbitalPeriod / relativeEarth * OrbitalPeriod;
	}
	float getRevoleCycle(PlanetType t) {
		switch (t) {
		case PlanetType::Mercury:
			return 86.79f;
			break;
		case PlanetType::Venus:
			return 221.91f;
			break;
		case PlanetType::Earth:
			return 360.0f;
			break;
		case PlanetType::Mars:
			return 677.58f;
			break;
		case PlanetType::Jupiter:
			return 3960.0f;
			break;
		case PlanetType::Saturn:
			return 10440.0f;
			break;
		case PlanetType::Uranus:
			return 30240.0f;
			break;
		case PlanetType::Neptune:
			return 59400.0f;
			break;
		}
		return 0;
	}

	Planet createPlanet(PlanetType type, sf::Color color, planetData data) {
		sf::CircleShape mercuryShape(data.radius * RADIUS_K);
		mercuryShape.setFillColor(color);

		return Planet(type, mercuryShape, &sun, DEFAULT_SUN_RADIUS + data.revolutionRadius * DISTANCE_FROM_SUN_K, data.revoleCycleSpeed);
	}
public:

	float OrbitalPeriod = OrbitalPeriodBySecond / 3.0f; //3초에 1회 공전

	SolarSystem(float width, float height) {
		this->planets = new Planet[MAX_PLANETS];

		sf::CircleShape sunShape(DEFAULT_SUN_RADIUS);
		sunShape.setFillColor(DEFAULT_SUN_COLOR);
		sunShape.setPosition((width - DEFAULT_SUN_RADIUS) / 2, (height - DEFAULT_SUN_RADIUS) / 2 - 30);

		sun = Sun(sunShape);

		//Relative Values (화면에 맞게 디자인하기 위해서 오차 존재)
		for (int i = 0; i < MAX_PLANETS; i++) {
			planetDatas[i].revoleCycleSpeed = cycleToRelativeSpeed(getRevoleCycle(planetList[i]));
			planets[i] = createPlanet(planetList[i], planetColors[i], planetDatas[i]);
		}

	}

	void ResetPlanetSize() {
		sun.SetRadius(DEFAULT_SUN_RADIUS);
		for (int i = 0; i < MAX_PLANETS; i++) {
			planets[i].SetRadius(planetDatas[i].radius * RADIUS_K);
		}
	}
	void SizePlanetRadiusAlpha(float alpha) {
		for (int i = 0; i < MAX_PLANETS; i++) {
			planets[i].SizeAlphaRadius(alpha);
		}
	}
	void SizeSunRadiusAlpha(float alpha) {
		sun.SizeAlphaRadius(alpha);
	}

	void Operate(float mainDeltaTime) {

		for (int i = 0; i < MAX_PLANETS; i++) {
			planets[i].Revolution(mainDeltaTime);
			//planets rotating
		}
		sun.Rotate();

	}
	void Draw(sf::RenderWindow* window) {

		for (int i = 0; i < MAX_PLANETS; i++) {
			window->draw(planets[i].GetShape());
		}

		window->draw(sun.GetShape());
	}

	//void AddPlanet() {  } //케플러 운동법칙 + 미적분 + 삼각비 활용
};