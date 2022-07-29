//Written by Monica Ingham

#pragma once
#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
using namespace std;

//Class definition
class Sudoku {

public:

	vector<vector<int>> getData();
	void setData(vector<vector<int>>);
	int getPoint(int x, int y);
	vector<int> getX(int y);
	vector<int> getY(int x);

private:

	vector<vector<int>> sdata;

};

#endif