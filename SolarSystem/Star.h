#pragma warning(disable : 26812)
#pragma warning(disable : 4244)
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

enum class StarType {
	RedDwarf, //90%
	WhiteDwarf, //6%
	BlueGiantStar //4%
};

class Star {
private:
	StarType type;
	sf::CircleShape star;
public:
	Star() { }
	Star(StarType t, sf::CircleShape s) {
		type = t;
		star = s;
	}
	sf::CircleShape GetShape() {
		return star;
	}
};