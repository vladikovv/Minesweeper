#ifndef SQUARE_H
#define SQUARE_H

#include <SFML/Graphics.hpp>

class Square {
public:
	Square();
	Square(int x, int y);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	bool isOpened();
	bool hasMine();
	void setMine();
	int getValue();
	void setValue(int value);
	sf::Sprite getSprite();
	void setSprite(sf::Sprite& sprite);


private:
	int x_;
	int y_;
	int value_;
	bool isOpened_;
	bool hasMine_;
	sf::Sprite sprite_;
};

#endif