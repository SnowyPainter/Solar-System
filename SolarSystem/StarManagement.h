#pragma warning(disable : 26812)
#pragma warning(disable : 4244)
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Star.h"

using namespace std;

class StarManagement {
private:
	Star* stars;
	int redDwarfRatio, whiteDwarfRatio, blueGiantStarRatio;
	int maxStars;
	int width, height;
	float starSize = 0.5f;

	int getRealCountFromRatio(float ratio) {
		float frac = (ratio / 100.0f);
		return frac * maxStars;
	}
	void initStarByRatio() {

		random_device rd;
		mt19937 gen(rd());

		uniform_int_distribution<int> widthDistribute(0, width);
		uniform_int_distribution<int> heightDistribute(0, height);

		stars = new Star[maxStars];

		int blueGiantCount = getRealCountFromRatio(blueGiantStarRatio);
		int whiteDwarfCount = getRealCountFromRatio(whiteDwarfRatio);
		int redDwarfCount = getRealCountFromRatio(redDwarfRatio);

		for (int i = 0; i < maxStars; i++) {

			sf::CircleShape starshape(starSize);
			starshape.setPosition(widthDistribute(gen), heightDistribute(gen));

			if (i < blueGiantCount) {
				starshape.setFillColor(sf::Color(0, 247, 243));
				stars[i] = Star(StarType::BlueGiantStar, starshape);
			}
			else if (i < whiteDwarfCount + blueGiantCount) {

				starshape.setFillColor(sf::Color(254, 255, 237));
				stars[i] = Star(StarType::WhiteDwarf, starshape);
			}
			else if (i < redDwarfCount + whiteDwarfCount + blueGiantCount) {
				
				starshape.setFillColor(sf::Color(255, 255, 199));
				stars[i] = Star(StarType::RedDwarf, starshape);
			}

		}
	}
public:
	StarManagement(int maximumStars, int width, int height) {
		maxStars = maximumStars;
		redDwarfRatio = 90;
		whiteDwarfRatio = 6;
		blueGiantStarRatio = 4;

		this->width = width;
		this->height = height;

		initStarByRatio();
	}

	void SetStarRatio(int redDwarf, int whiteDwarf, int blueGiantStar) {
		redDwarfRatio = redDwarf;
		whiteDwarfRatio = whiteDwarf;
		blueGiantStarRatio = blueGiantStar;
		
		initStarByRatio();
	}
	int GetMaxStars() { return maxStars;  }
	void ResizeStarNumber(int num) {
		maxStars = num;

		initStarByRatio();
	}

	void DrawAllStars(sf::RenderWindow* app) {

		for (int i = 0; i < maxStars; i++) {
			app->draw(stars[i].GetShape());
		}

	}
};