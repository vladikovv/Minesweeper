#include "Square.h"

Square::Square(int x, int y) {
	x_ = x;
	y_ = y;
	hasMine_ = false;
	isOpened_ = false;
	value_ = 0;
}

Square::Square() {
	x_ = 0;
	y_ = 0;
	hasMine_ = false;
	isOpened_ = false;
	value_ = 0;
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