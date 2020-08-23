#pragma warning(disable : 26812)
#pragma warning(disable : 4244)
#include <iostream>
#include <SFML/Graphics.hpp>
#include "StarManagement.h"
#include "SolarSystem.h"

using namespace std;

const int WIDTH = 1920;
const int HEIGHT = 1024;
const int INITMAXSTAR = 200;
const string TITLE = "Solar System";

//Settings
int scalingNumber = 1;

//Variables
sf::RenderWindow app(sf::VideoMode(WIDTH, HEIGHT), TITLE);
StarManagement starmanager(INITMAXSTAR, WIDTH, HEIGHT); //Background manager
SolarSystem solarSystem = SolarSystem(WIDTH, HEIGHT);

sf::Clock c;
bool isStop = false;

void eventCallback(sf::Event::EventType type, sf::Event::KeyEvent key) {
    switch (type) {
    case sf::Event::Closed:
        app.close();
        break;
    case sf::Event::KeyPressed:
        if (key.code == sf::Keyboard::B)
            starmanager.SetStarRatio(90, 6, 4);
        else if (key.code == sf::Keyboard::PageUp) {
            starmanager.ResizeStarNumber(starmanager.GetMaxStars() + 10);
        }
        else if (key.code == sf::Keyboard::PageDown) {
            if(starmanager.GetMaxStars() > 10)
                starmanager.ResizeStarNumber(starmanager.GetMaxStars() + -10 );
        }
        else if (key.code == sf::Keyboard::Home) {
            cout << "KeyPress HOME" << endl;
            solarSystem.ResetPlanetSize();
        }
        break;
    case sf::Event::KeyReleased:
        if (key.code == sf::Keyboard::Up) {
            solarSystem.SizeSunRadiusAlpha(scalingNumber);
            solarSystem.SizePlanetRadiusAlpha(scalingNumber);
        }
        else if (key.code == sf::Keyboard::Down) {
            solarSystem.SizeSunRadiusAlpha(-scalingNumber);
            solarSystem.SizePlanetRadiusAlpha(-scalingNumber);
        }
        else if (key.code == sf::Keyboard::Space) {
            isStop = !isStop;
        }
    }
}

void initApp() {
    app.setFramerateLimit(60);
}

int main()
{
    initApp();

    while (app.isOpen())
    {
        
        sf::Event event;
        while (app.pollEvent(event))
            eventCallback(event.type, event.key);

        sf::Time t = c.getElapsedTime();

        if (!isStop) {
            solarSystem.Operate(t.asSeconds());
        }
        c.restart().asSeconds();

        // Resizing orbital size ..


        app.clear(sf::Color(21, 21, 21));

        solarSystem.Draw(&app);
        starmanager.DrawAllStars(&app);

        app.display();
    }

    return 0;
}
