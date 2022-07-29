//Written by Monica Ingham

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Sudoku.h"
#include "Functions.h"
using namespace std;



//Function definitions
vector<vector<int>> readData(string filename);
void writeData(vector<vector<int>>);
void outputSudoku(Sudoku);




/*
This is the main program for the algorithm that solves sudoku puzzles.
This file basically only does I/O stuff, all the actual
work of the algorithm is in Functions.cpp.
*/
int main()
{
    
	//Variable definitions
	Sudoku sudoku;
	string input;



	//Welcome the user and tell them to load the puzzle
	cout << "Welcome to the Sudoku Solver!\n" <<
			"Please enter a file name to load a puzzle: ";

	//Get filename and load data
	cin >> input;
	sudoku.setData(readData(input));



	//Output the puzzle that was just loaded
	outputSudoku(sudoku);



	//Solve the puzzle
	sudoku.setData(solveSudoku(sudoku.getData()));



	//Output the solved puzzle
	cout << "\n\nAlgorithm complete, here are the results:\n";
	outputSudoku(sudoku);
	


	//Save data
	cout << "Saving data...\n";
	writeData(sudoku.getData());
	cout << "Done!\n";




	//Exit program
	system("Pause");
	return 0;
}



//This outputs the Sudoku with a bunch of fancy formatting
void outputSudoku(Sudoku sudoku) {

	cout << "-------------------------------------\n|           |           |           |\n";

	//Loop through each line
	for (int a = 0; a < 9; a++) {

		//Get the line
		vector<int> line = sudoku.getX(a);

		cout << "|  ";

		//Loop through the line
		for (int b = 0; b < 9; b++) {

			//Get number
			int n = line.at(b);

			//Output and formatting
			if (n == 0) {
				cout << "_  ";
			}
			else {
				cout << n << "  ";
			}

			if ((b == 2) || (b == 5)) {
				cout << "|  ";
			}

		}

		cout << "|\n|           |           |           |\n";

		if ((a == 2) || (a == 5) || (a == 8)) {
			cout << "-------------------------------------\n";
			if (a != 8) {
				cout << "|           |           |           |\n";
			}
		}

	}

}



//This function writes the sudoku data to a text file
void writeData(vector<vector<int>> sdata) {

	fstream file;

	//Open the file
	file.open("Output.txt", ios::out);

	//Write to the file
	for (int a = 0; a < 9; a++) {

		//Make string and put line of puzzle onto it
		string output = "";
		for (int b = 0; b < 9; b++) {
			
			output.append(to_string(sdata.at(a).at(b)));

		}

		//Output string
		file << output;

		//Format
		if (a != 8) {
			file << endl;
		}

	}

	//Close the file
	file.close();

	//Return
	return;

}



//This function loads data from a file and turns it into puzzle data
vector<vector<int>> readData(string filename) {

	//Variable definitions
	vector<vector<int>> sdata;
	fstream file;

	//Open the file
	file.open(filename, ios::in);

	//While the file is open
	if (file.is_open()) {

		//Read each line of the file
		string input;
		int iterator = 0;
		while (getline(file, input)) {

			//Don't go over 9 lines
			if (iterator >= 9) {
				break;
			}

			//Make line data
			vector<int> line;

			//Loop through each digit of the input
			for (int a = 0; a < input.length(); a++) {

				//Turn the character into a digit and add it to the data
				line.push_back(input.at(a) - '0');

			}

			//Add line to data
			sdata.push_back(line);

			//Go to next line of sudoku
			iterator++;

		}

		//Close the file
		file.close();

	}

	//return the data
	return sdata;

}