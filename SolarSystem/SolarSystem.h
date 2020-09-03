#pragma warning(disable : 26812)
#pragma warning(disable : 4244)
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Sun.h"
#include "Planet.h"

using namespace std;

const float DEFAULT_SUN_RADIUS = 45.0f;
const float DEFAULT_EARTH_REVOLVE_PERIOD = 1.0f;
const int MAX_PLANETS = 8; //8
const int DISTANCE_FROM_SUN_K = 40;
const int RADIUS_K = 3;
const float EARTH_OrbitalPeriod_Second = 360.0f;
const sf::Color DEFAULT_SUN_COLOR = sf::Color(255, 115, 0);

class SolarSystem {
private:
	Sun sun; //It must be textrued
	Planet* planets; //수금지화목토천해
	sf::Vector2f sunCenterPosition;

	//지구 기준하에 비례
	float revolvePeriodSecond = DEFAULT_EARTH_REVOLVE_PERIOD;
	float orbitalPeriodSpeed = EARTH_OrbitalPeriod_Second / revolvePeriodSecond; //1초에 1회 공전

	struct planetData {
		wstring dscrp;
		float radius;
		float revolutionRadius;
		float revoleCycleSpeed;
	};
	//Inital Values
	planetData planetDatas[8] = {
		//Dscpr ,Radius, Revolution Radius, Revolution Speed
		{ L"수성\n대기는 거의 존재하지 않으며\n평균 온도는 179도에 달합니다.\n온도변화가 매우 큽니다.",0.4f, 0.5f, },
		{ L"금성\n밤하늘에서 두번째로 밝습니다.\n대기는 CO2로 차있으며\n매우 큰 화산들이 많습니다.",0.9f, 0.82f,  },
		{ L"지구\n우리가 사는 행성입니다.\n타원형 생김새이며\n바다가 있습니다.\n",1.0f, 1.0f, },
		{ L"화성\n얼음이 존재하며, 붉은색을 띕니다.\n태양계에서 가장 큰 올림푸스 화산이 있습니다.",0.8f, 1.52f, },
		{ L"목성\n가장 큰 행성이며 기체 행성입니다.\n고기압성 폭풍인 대적점이 있습니다.",6.2f, 2.5f,  },
		{ L"토성\n눈에 띄는 선명한 고리가 있으며\n밀도가 물보다 낮습니다.",5.4f, 7.18f,  },
		{ L"천왕성\n대기가 안정적이며\n바람이 불지 않습니다.\n태양에서 부터 30억KM 떨어져있습니다",2.5f, 9.4f,  },
		{ L"해왕성\n미약한 고리가 있습니다.\n거대 얼음 행성으로도 불립니다.",1.9f, 13.2f, },
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
		return orbitalPeriodSpeed / relativeEarth * EARTH_OrbitalPeriod_Second; 
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
		Planet p(type, mercuryShape, &sun, DEFAULT_SUN_RADIUS + data.revolutionRadius * DISTANCE_FROM_SUN_K, data.revoleCycleSpeed);
		p.Description = data.dscrp;
		return p;
	}
public:

	SolarSystem(float width, float height) {
		this->planets = new Planet[MAX_PLANETS];

		sunCenterPosition = sf::Vector2f((width - DEFAULT_SUN_RADIUS) / 2, (height - DEFAULT_SUN_RADIUS) / 2);

		sf::CircleShape sunShape(DEFAULT_SUN_RADIUS);
		sunShape.setFillColor(DEFAULT_SUN_COLOR);
		sunShape.setPosition(sunCenterPosition);

		sun = Sun(sunShape);

		//Relative Values (화면에 맞게 디자인하기 위해서 오차 존재)
		for (int i = 0; i < MAX_PLANETS; i++) {
			planetDatas[i].revoleCycleSpeed = cycleToRelativeSpeed(getRevoleCycle(planetList[i]));
			planets[i] = createPlanet(planetList[i], planetColors[i], planetDatas[i]);
		}

	}
	float GetOrbitalPeriodSecond() {
		return revolvePeriodSecond;
	}
	Planet GetPlanet(int index) {
		return planets[index];
	}
	Planet* GetAllPlanets() {
		return planets;
	}
	void ResetPlanetSize() {
		sun.SetRadius(DEFAULT_SUN_RADIUS);
		sun.SetPosition(sunCenterPosition);
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

	// 지구 기준
	void SetRevolutionPeriodSecond(float second) {
		if (second <= 0.0f)
			return;

		revolvePeriodSecond = second;
		orbitalPeriodSpeed = EARTH_OrbitalPeriod_Second / revolvePeriodSecond;

		for (int i = 0; i < MAX_PLANETS; i++) {
			planets[i].RevolutionSpeed = cycleToRelativeSpeed(getRevoleCycle(planets[i].GetType()));;
		}
	}

	void Operate(float mainDeltaTime) {

		for (int i = 0; i < MAX_PLANETS; i++) {
			planets[i].Revolution(mainDeltaTime);
			//planets rotating
		}
		sun.Rotate();

	}
	void Draw(sf::RenderWindow* window) {
		window->draw(sun.GetShape());
		for (int i = 0; i < MAX_PLANETS; i++) {
			window->draw(planets[i].GetShape());
		}
	}

};