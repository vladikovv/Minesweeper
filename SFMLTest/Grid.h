#ifndef GRID_H
#define GRID_H

#include<vector>
#include "Square.h"

class Grid {
public:
	Grid(int m, int n, int minesCount);
	int getM();
	int getN();
	int getMinesCount();
	void setM(int m);
	void setN(int n);
	void setMinesCount(int minesCount);
	


private:
	int m_;
	int n_;
	int minesCount_;
	std::vector<std::vector<Square>> grid_;

	void addMines();
	
};

#endif