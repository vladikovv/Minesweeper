#include "Grid.h"

#include <SFML/Graphics.hpp>
#include <climits>
#include <iostream>
#include <cstdlib>

int main() {
	sf::RenderWindow window(sf::VideoMode(27 * 16, 27 * 16), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
	Game grid(16, 16, 75);

	while (window.isOpen()) {
		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();	
			}
			
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				int xCoord = event.mouseButton.x;
				int yCoord = event.mouseButton.y;

				Square* sq = grid.getGrid().at(std::abs(xCoord / 27)).at(std::abs(yCoord / 27));
				sq->openSquare();
			}
		}

		window.clear(sf::Color(0,0,0,255));

		
		for (size_t i = 0; i < grid.getM(); i++) {
			for (size_t j = 0; j < grid.getN(); j++) {
				window.draw(grid.getGrid()[i][j]->getSprite());
			}
			
		}
		window.display();
	}


	
}