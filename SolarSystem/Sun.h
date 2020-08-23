#pragma warning(disable : 26812)
#pragma warning(disable : 4244)
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SolarSystemElement.h"

using namespace std;

class Sun: public SolarSystemElement {
private:
	
public:
	Sun() :SolarSystemElement() {}
	Sun(sf::CircleShape sun):SolarSystemElement(sun) {
		
	}
	void Rotate() {
		
	}

};