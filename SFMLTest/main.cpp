#include "Grid.h"

#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
	Grid grid(3, 3, 5);

	while (window.isOpen()) {
		std::cout << "open window\n";
		sf::Event event;
		int squaresCount = 0;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				std::cout << "closed window\n";
				window.close();
			}
		}

		window.display();
		window.clear();

	}


	
}