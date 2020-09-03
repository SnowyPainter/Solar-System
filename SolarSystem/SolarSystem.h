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
	Planet* planets; //������ȭ����õ��
	sf::Vector2f sunCenterPosition;

	//���� �����Ͽ� ���
	float revolvePeriodSecond = DEFAULT_EARTH_REVOLVE_PERIOD;
	float orbitalPeriodSpeed = EARTH_OrbitalPeriod_Second / revolvePeriodSecond; //1�ʿ� 1ȸ ����

	struct planetData {
		wstring dscrp;
		float radius;
		float revolutionRadius;
		float revoleCycleSpeed;
	};
	//Inital Values
	planetData planetDatas[8] = {
		//Dscpr ,Radius, Revolution Radius, Revolution Speed
		{ L"����\n���� ���� �������� ������\n��� �µ��� 179���� ���մϴ�.\n�µ���ȭ�� �ſ� Ů�ϴ�.",0.4f, 0.5f, },
		{ L"�ݼ�\n���ϴÿ��� �ι�°�� ����ϴ�.\n���� CO2�� ��������\n�ſ� ū ȭ����� �����ϴ�.",0.9f, 0.82f,  },
		{ L"����\n�츮�� ��� �༺�Դϴ�.\nŸ���� ������̸�\n�ٴٰ� �ֽ��ϴ�.\n",1.0f, 1.0f, },
		{ L"ȭ��\n������ �����ϸ�, �������� ��ϴ�.\n�¾�迡�� ���� ū �ø�Ǫ�� ȭ���� �ֽ��ϴ�.",0.8f, 1.52f, },
		{ L"��\n���� ū �༺�̸� ��ü �༺�Դϴ�.\n���м� ��ǳ�� �������� �ֽ��ϴ�.",6.2f, 2.5f,  },
		{ L"�伺\n���� ��� ������ ���� ������\n�е��� ������ �����ϴ�.",5.4f, 7.18f,  },
		{ L"õ�ռ�\n��Ⱑ �������̸�\n�ٶ��� ���� �ʽ��ϴ�.\n�¾翡�� ���� 30��KM �������ֽ��ϴ�",2.5f, 9.4f,  },
		{ L"�ؿռ�\n�̾��� ���� �ֽ��ϴ�.\n�Ŵ� ���� �༺���ε� �Ҹ��ϴ�.",1.9f, 13.2f, },
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

		//Relative Values (ȭ�鿡 �°� �������ϱ� ���ؼ� ���� ����)
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

	// ���� ����
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