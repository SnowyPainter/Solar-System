#pragma warning(disable : 26812)
#pragma warning(disable : 4244)
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Sun {
private:
	sf::CircleShape sun; //It must be textrued
public:
	Sun() { }
	Sun(sf::CircleShape sun) {
		this->sun = sun;
	}
	void Rotate() {
		
	}
	sf::CircleShape GetShape() {
		return sun;
	}
};