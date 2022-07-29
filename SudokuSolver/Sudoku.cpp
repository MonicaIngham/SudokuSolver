//Written by Monica Ingham

#include "Sudoku.h"



//This function gets a single number at a point
int Sudoku::getPoint(int x, int y) {

	return sdata.at(y).at(x);

}



//This function gets a single vertical line from the data
vector<int> Sudoku::getY(int x) {

	vector<int> v;
	
	//Loop through each row to get every number from the column
	for (int a = 0; a < 9; a++) {

		v.push_back(sdata.at(a).at(x));

	}

	return v;
}



//This function gets a single horizontal line from the data
vector<int> Sudoku::getX(int y) {

	return sdata.at(y);

}



//This function returns the sudoku data
vector<vector<int>> Sudoku::getData() {

	return sdata;

}



//this function sets the sudoku data
void Sudoku::setData(vector<vector<int>> s) {

	sdata = s;
	return;

}