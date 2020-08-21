#pragma warning(disable : 26812)
#pragma warning(disable : 4244)
#include <iostream>
#include <SFML/Graphics.hpp>
#include "StarManagement.h"
#include "SolarSystem.h"

using namespace std;

const int WIDTH = 1400;
const int HEIGHT = 800;
const int INITMAXSTAR = 100;
const string TITLE = "Solar System";

//Variables
sf::RenderWindow app(sf::VideoMode(WIDTH, HEIGHT), TITLE, sf::Style::Titlebar | sf::Style::Close);
StarManagement starmanager(INITMAXSTAR, WIDTH, HEIGHT); //Background manager
SolarSystem solarSystem = SolarSystem(WIDTH, HEIGHT);

void eventCallback(sf::Event::EventType type, sf::Event::KeyEvent key) {
    switch (type) {
    case sf::Event::Closed:
        app.close();
        break;
    case sf::Event::KeyPressed:
        if (key.code == sf::Keyboard::B)
            starmanager.SetStarRatio(90, 6, 4);
        else if (key.code == sf::Keyboard::Up) {
            starmanager.ResizeStarNumber(starmanager.GetMaxStars() + 10);
        }
        else if (key.code == sf::Keyboard::Down) {
            if(starmanager.GetMaxStars() > 10)
                starmanager.ResizeStarNumber(starmanager.GetMaxStars() + -10 );
        }
        else if (key.code == sf::Keyboard::P) {
            solarSystem.ToggleSunCenterPointer();
        }
        break;

    }
}

void initApp() {
    app.setFramerateLimit(30);
}

int main()
{
    initApp();

    while (app.isOpen())
    {

        sf::Event event;
        while (app.pollEvent(event))
            eventCallback(event.type, event.key);

        solarSystem.Operate();

        app.clear(sf::Color(21, 21, 21));

        solarSystem.Draw(&app);
        starmanager.DrawAllStars(&app);

        app.display();
    }

    return 0;
}
