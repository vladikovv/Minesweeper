#include "Square.h"
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
	sprite_.setPosition(x_ * 27, y_ * 27);
	sprite_.setScale(0.125f, 0.125f);
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
	sprite_.setPosition(x_ * 27, y_ * 27);
	sprite_.setScale(0.125f, 0.125f);
}



int Square::getX() {
	return x_;
}

int Square::getY() {
	return y_;
}

void Square::setX(int x) {
	x_ = x;
}

void Square::setY(int y) {
	y_ = y;
}

bool Square::isOpened() {
	return isOpened_;
}

bool Square::hasMine() {
	return hasMine_;
}

void Square::setMine() {
	hasMine_ = true;
}

int Square::getValue() {
	return value_;
}

void Square::setValue(int value) {
	value_ = value;
}

sf::Sprite Square::getSprite() {
	return sprite_;
}
void Square::setSprite(sf::Sprite& sprite) {
	sprite_ = sprite;
}

sf::Texture Square::getTexture() {
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
	if (hasMine_ ) {
		if (!texture.loadFromFile("textures/MINESWEEPER_M.png")) {
			std::cout << "Error loading texture!" << std::endl;
		}
	} else {
		std::string fileName = std::format("textures/MINESWEEPER_{}.png", getValue());
		if (!texture.loadFromFile(fileName)) {
			std::cout << "Error loading texture!" << std::endl;
		}
	}
	
	changeSprite(texture);
	isOpened_ = true;
}