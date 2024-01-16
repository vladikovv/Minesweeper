#include "Game.h"

#include <SFML/Graphics.hpp>
#include <climits>
#include <iostream>
#include <cstdlib>

int main() {
	sf::RenderWindow window(sf::VideoMode(27 * 9, 27 * 9), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
	Game game(9, 9, 10);

	while (game.isGameOver() != true && window.isOpen()) {
		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || game.isGameOver()) {
				window.close();	
			}
			
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			int xCoord = event.mouseButton.x;
			int yCoord = event.mouseButton.y;
			Square* sq = game.getGrid().at(std::abs(xCoord / 27)).at(std::abs(yCoord / 27));
			if (event.mouseButton.button == sf::Mouse::Left) {
				if(sq->isOpenable()) {
					sq->openSquare();
				}
				if (sq->isOpened() && sq->hasMine()) {
					window.close();
					return 0;
				}
			}
			else if (event.mouseButton.button == sf::Mouse::Right) {
				if (sq->isOpenable()) {
					sq->flag();
				}
				
			}
		}

		window.clear(sf::Color(0,0,0,255));

		for (size_t i = 0; i < game.getM(); i++) {
			for (size_t j = 0; j < game.getN(); j++) {
				window.draw(game.getGrid()[i][j]->getSprite());
			}
		}
		window.display();
	}


	return 0;
}