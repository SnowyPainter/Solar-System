#pragma warning(disable : 26812)
#pragma warning(disable : 4244)
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "StarManagement.h"
#include "SolarSystem.h"

using namespace std;

const int WIDTH = 1920;
const int HEIGHT = 1024;
const int INITMAXSTAR = 200;
const string TITLE = "Solar System";

//Settings
int scalingNumber = 1;
bool isStop = false;
sf::CircleShape* selectedPlanet = nullptr;

StarManagement starmanager(INITMAXSTAR, WIDTH, HEIGHT); //Background manager
SolarSystem solarSystem = SolarSystem(WIDTH, HEIGHT);

sf::Font basicFont;
sf::Text selectedPlanetInformation; //Planet Information
sf::Text baseRevolvePeriod, selectedPlanetRevolvePeriod; //revolution period == Earth

void cleanSelectedPlanetUI() {
	selectedPlanetInformation.setString("");
	selectedPlanetRevolvePeriod.setString("");
}

void mouseWheelEventCallback(sf::Event::EventType type, sf::Event::MouseWheelEvent event) {
	if (event.delta == 1) {
		//solarSystem.SizeSunRadiusAlpha(scalingNumber);
		solarSystem.SizePlanetRadiusAlpha(scalingNumber);
	}
	else if (event.delta == -1) {
		//solarSystem.SizeSunRadiusAlpha(-scalingNumber);
		solarSystem.SizePlanetRadiusAlpha(-scalingNumber);
	}
}
void keyEventCallback(sf::Event::EventType type, sf::Event::KeyEvent key) {
	switch (type) {
	case sf::Event::KeyPressed:
		if (key.code == sf::Keyboard::B)
			starmanager.SetStarRatio(90, 6, 4);
		else if (key.code == sf::Keyboard::PageUp) {
			starmanager.ResizeStarNumber(starmanager.GetMaxStars() + 10);
		}
		else if (key.code == sf::Keyboard::PageDown) {
			if (starmanager.GetMaxStars() > 10)
				starmanager.ResizeStarNumber(starmanager.GetMaxStars() + -10);
		}
		else if (key.code == sf::Keyboard::Home) {
			solarSystem.SetRevolutionPeriodSecond(DEFAULT_EARTH_REVOLVE_PERIOD);
			solarSystem.ResetPlanetSize();
		}
		//Set Revolution Speed - 지구 기준, 상대 주기
		else if (key.code == sf::Keyboard::Up) {
			solarSystem.SetRevolutionPeriodSecond(solarSystem.GetOrbitalPeriodSecond() + 0.1f);
		}
		else if (key.code == sf::Keyboard::Down) {
			solarSystem.SetRevolutionPeriodSecond(solarSystem.GetOrbitalPeriodSecond() - 0.1f);
		}

		if (key.code == sf::Keyboard::Home || key.code == sf::Keyboard::Up || key.code == sf::Keyboard::Down) {
			baseRevolvePeriod.setString(L"지구의 공전 주기는" + to_wstring(solarSystem.GetOrbitalPeriodSecond()) + L"초 입니다.");
		}
		break;
	case sf::Event::KeyReleased:
		if (key.code == sf::Keyboard::Space) {
			isStop = !isStop;
		}
	}
}
void mouseButtonEventCallback(sf::Event::EventType type, sf::Event::MouseButtonEvent event) {
	switch (type) {
	case sf::Event::MouseButtonReleased:
		Planet* planets = solarSystem.GetAllPlanets();
		for (int i = 0; i < MAX_PLANETS; i++) {
			if (planets[i].GetShape().getGlobalBounds().contains(event.x, event.y)) {
				selectedPlanet = planets[i].GetReadableShape();

				selectedPlanetRevolvePeriod.setString(L"공전주기 : " + to_wstring(planets[i].GetRevolutionPeriod(EARTH_OrbitalPeriod_Second)) + L"초");
				selectedPlanetInformation.setString(planets[i].Description);
				return;
			}
		}
		
		selectedPlanet = nullptr;
		cleanSelectedPlanetUI();

		break;
	}
}

bool initVariables(string* errMsg) {
	if (!basicFont.loadFromFile("./IBMPlexSansKR-Regular.ttf")) {
		*errMsg = "폰트 NanumGothic-Regular.ttf 를 불러오는데 실패했습니다.";
		return false;
	}

	selectedPlanetInformation = sf::Text(L"", basicFont, 18);
	selectedPlanetRevolvePeriod = sf::Text(L"", basicFont, 16);

	baseRevolvePeriod = sf::Text(L"지구의 공전 주기는" + to_wstring(solarSystem.GetOrbitalPeriodSecond()) + L"초 입니다.", basicFont);
	baseRevolvePeriod.setPosition((WIDTH - baseRevolvePeriod.getLocalBounds().width) / 2, 40);
	return true;
}

int main()
{
	string errMsg;
	if (!initVariables(&errMsg)) {
		cout << errMsg << endl;
		cout << "엔터키를 누르시면 종료됩니다." << endl;
		getchar();
		return -1;
	}

	sf::RenderWindow app(sf::VideoMode(WIDTH, HEIGHT), TITLE);
	app.setFramerateLimit(60);

	cout << "프로그램 초기화 완료" << endl;
	
	sf::Clock c;

	while (app.isOpen())
	{

		sf::Event event;
		while (app.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				app.close();
			int type = static_cast<int>(event.type);
			if (type >= 5 && type <= 6) //Key event
				keyEventCallback(event.type, event.key);
			else if (type >= 7 && type <= 8) //Mouse Wheel Event
				mouseWheelEventCallback(event.type, event.mouseWheel);
			else if (type >= 9 && type <= 13) //Mouse Button Event
				mouseButtonEventCallback(event.type, event.mouseButton);
		}
		sf::Time t = c.getElapsedTime();

		if (!isStop) {
			solarSystem.Operate(t.asSeconds()); //Deltatime updating
		}
		if (selectedPlanet != nullptr) {
			sf::Vector2f planetPos = selectedPlanet->getPosition();
			sf::FloatRect periodTextBound = selectedPlanetRevolvePeriod.getLocalBounds();
			float planetR = selectedPlanet->getRadius();
			sf::Vector2f leftParaDistance(planetR * 2, -5);
			sf::Vector2f upParaDistance(periodTextBound.width / -2 + planetR, -periodTextBound.height - 10);

			selectedPlanetInformation.setPosition(planetPos + leftParaDistance);
			selectedPlanetRevolvePeriod.setPosition(planetPos + upParaDistance);
		}

		c.restart().asSeconds();

		app.clear(sf::Color(21, 21, 21));

		starmanager.DrawAllStars(&app);
		solarSystem.Draw(&app);

		app.draw(selectedPlanetInformation);
		app.draw(selectedPlanetRevolvePeriod);
		app.draw(baseRevolvePeriod);
			
		app.display();
	}

	return 0;
}
