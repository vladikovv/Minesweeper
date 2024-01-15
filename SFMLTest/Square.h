#ifndef SQUARE_H
#define SQUARE_H

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


private:
	int x_;
	int y_;
	bool isOpened_;
	bool hasMine_;
};

#endif