//Written by Monica Ingham

#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
using namespace std;

vector<vector<int>> solveSudoku(vector<vector<int>>);						//Main algorithm function
int countRow(vector<vector<int>>, int);										//Counts how many solved numbers are in a row
int countColumn(vector<vector<int>>, int);									//Counts how many solved numbers are in a column
int countSquare(vector<vector<int>>, int, int);								//Counts how many solved numbers are in a square
vector<vector<vector<int>>> getPossibilities(vector<vector<int>>);			//Creates a list of possible numbers for each position
bool searchRow(vector<vector<int>>, int, int);								//Searches if a number is in a row
bool searchColumn(vector<vector<int>>, int, int);							//Searches if a number is in a column
bool searchSquare(vector<vector<int>>, int, int, int);						//Searches if a number is in a square
bool searchRowPossibilities(vector<vector<vector<int>>>, int, int);			//Searches if a possibility is in a row
bool searchColumnPossibilities(vector<vector<vector<int>>>, int, int);		//Searches if a possibility is in a column
bool searchSquarePossibilities(vector<vector<vector<int>>>, int, int, int);	//Searches if a possibility is in a square

#endif