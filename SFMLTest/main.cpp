#include "Grid.h"

#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
	Grid grid(16, 16, 75);

	

	while (window.isOpen()) {
		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();
		window.draw(grid.getGrid()[0][0].getSprite());
		window.display();

	}


	
}