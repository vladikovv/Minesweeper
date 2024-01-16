#ifndef SQUARE_H
#define SQUARE_H

#include <SFML/Graphics.hpp>

class Square {
public:
	Square();
	Square(int x, int y);
	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);
	bool isOpened() const;
	bool hasMine() const;
	void setMine();
	int getValue() const;
	void setValue(int value);
	sf::Sprite getSprite() const;
	void setSprite(sf::Sprite& sprite);
	sf::Texture getTexture() const;
	void setTexture(sf::Texture& texture);
	void changeSprite(sf::Texture& texture);
	void openSquare();
	void setIsOpened(bool value);
	void flag();
	bool isFlagged() const;
	bool isOpenable() const;
	void removeFlag();

private:
	int x_;
	int y_;
	int value_;
	bool isOpened_;
	bool hasMine_;
	bool isFlagged_ = false;
	bool isOpenable_ = !isFlagged_;
	sf::Texture texture_;
	sf::Sprite sprite_;
};

#endif