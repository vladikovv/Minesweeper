#include "Square.h"
#include "Constants.h"

#include <iostream>
#include <format>


Square::Square() {
	x_ = 0;
	y_ = 0;
	hasMine_ = false;
	isOpened_ = false;
	value_ = 0;
	if (!texture_.loadFromFile("textures/MINESWEEPER_X.png")) {
		std::cout << "Error loading texture!" << std::endl;
	}
	sprite_.setTexture(texture_);
	sprite_.setPosition(x_ * SPRITE_LENGTH, y_ * SPRITE_LENGTH);
	sprite_.setScale(SPRITE_SCALE, SPRITE_SCALE);
}

Square::Square(int x, int y) {
	x_ = x;
	y_ = y;
	hasMine_ = false;
	isOpened_ = false;
	value_ = 0;
	
	if (!texture_.loadFromFile("textures/MINESWEEPER_X.png")) {
		std::cout << "Error loading texture!" << std::endl;
	}
	sprite_.setTexture(texture_);
	sprite_.setPosition(x_ * SPRITE_LENGTH, y_ * SPRITE_LENGTH);
	sprite_.setScale(SPRITE_SCALE, SPRITE_SCALE);
}

int Square::getX() const {
	return x_;
}

int Square::getY() const {
	return y_;
}

void Square::setX(int x)  {
	x_ = x;
}

void Square::setY(int y) {
	y_ = y;
}

bool Square::isOpened() const {
	return isOpened_;
}

bool Square::hasMine() const {
	return hasMine_;
}

void Square::setMine() {
	hasMine_ = true;
}

int Square::getValue() const {
	return value_;
}

void Square::setValue(int value) {
	value_ = value;
}

sf::Sprite Square::getSprite() const {
	return sprite_;
}
void Square::setSprite(sf::Sprite& sprite) {
	sprite_ = sprite;
}

sf::Texture Square::getTexture() const {
	return texture_;
}

void Square::setTexture(sf::Texture& texture) {
	texture_ = texture;
}

void Square::changeSprite(sf::Texture& texture) {
	texture_ = texture;
	sprite_.setTexture(texture_);
}

void Square::openSquare() {
	sf::Texture texture;
	if (isFlagged_) {
		return;
	}
	if (hasMine_ ) {
		if (!isOpened_) {
			if (!texture.loadFromFile("textures/MINESWEEPER_M.png")) {
				std::cout << "Error loading texture!" << std::endl;
			}
		}
		else {
			if (!texture.loadFromFile("textures/MINESWEEPER_F.png")) {
				std::cout << "Error loading texture!" << std::endl;
			}
		}
		
	} else {
		if (value_ > 0) {
			std::string fileName = std::format("textures/MINESWEEPER_{}.png", getValue());
			if (!texture.loadFromFile(fileName)) {
				std::cout << "Error loading texture!" << std::endl;
			}
		} 
		else {
			if (!texture.loadFromFile("textures/MINESWEEPER_0.png")) {
				std::cout << "Error loading texture!" << std::endl;
			}
		}
	}
	changeSprite(texture);
	isOpened_ = true;
	isOpenable_ = false;
}

void Square::setIsOpened(bool value) {
	isOpened_ = value;
}

void Square::flag() {
	isFlagged_ = true;
	isOpenable_ = false;
	sf::Texture texture;
	if (!texture.loadFromFile("textures/MINESWEEPER_F.png")) {
		std::cout << "Error loading texture!" << std::endl;
	}
	changeSprite(texture);

}

bool Square::isOpenable() const {
	return isOpenable_ && !isOpened_;
}

bool Square::isFlagged() const {
	return isFlagged_;
}

void Square::removeFlag() {
	isFlagged_ = false;
	isOpenable_ = true;
	sf::Texture texture;
	if (!texture.loadFromFile("textures/MINESWEEPER_X.png")) {
		std::cout << "Error loading texture!" << std::endl;
	}
	changeSprite(texture);
}
