//Written by Monica Ingham

#include "Functions.h";



/*
This is the main algorithm controller the algorithm, and has a main loop that
completes either when the puzzle is completed or when the algorithm fails.
This is the two step process it goes through:

1. check for any obvious numbers in a square, row, or column
2. check for any cells where the answer is solvable through process of elimination

*/
vector<vector<int>> solveSudoku(vector<vector<int>> sdata) {

	//Start a while loop that exits when the algorithm is done
	bool done = false;

	while (done == false) {

		//So that when the algorithm does something, it goes back to checking the easiest step first
		bool doneLoop = false;



		//First check all rows for a row where only one number is missing
		for (int a = 0; a < 9; a++) {

			//If a row has 8 entered numbers in a row
			if (countRow(sdata, a) == 8) {

				//Add the missing number to complete the row
				int counter = 0;
				int posX;
				int posY;

				for (int b = 0; b < 9; b++) {

					//Add to the counter
					counter += sdata.at(a).at(b);

					//find the missing number position
					if (sdata.at(a).at(b) == 0) {

						posX = a;
						posY = b;

					}

				}

				//Change the number
				sdata.at(posX).at(posY) = (45 - counter);
				doneLoop = true;

			}

		}



		//Then check the columns
		if (doneLoop == false) {

			//First check all columns for a column where only one number is missing
			for (int a = 0; a < 9; a++) {

				//If a column has one number missing
				if (countColumn(sdata, a) == 8) {

					//Add the missing number
					int counter = 0;
					int posX;
					int posY;

					for (int b = 0; b < 9; b++) {

						//Add to the counter
						counter += sdata.at(b).at(a);

						//find the missing number position
						if (sdata.at(b).at(a) == 0) {

							posX = b;
							posY = a;

						}

					}

					//Change the number
					sdata.at(posX).at(posY) = (45 - counter);
					doneLoop = true;

				}

			}

		}



		//Finally, check the squares
		if (doneLoop == false) {

			//First check all the squares to find one with a single missing number
			for (int a = 0; a < 9; a += 3) {

				for (int b = 0; b < 9; b += 3) {

					//If a square has one number missing
					if (countSquare(sdata, b, a) == 8) {

						//Add the missing number
						int counter = 0;
						int posX;
						int posY;

						for (int c = a; c < (a + 3); c++) {

							for (int d = b; d < (b + 3); d++) {

								//Add to the counter
								counter += sdata.at(c).at(d);

								//Find the missing number position
								if (sdata.at(c).at(d) == 0) {

									posX = c;
									posY = d;

								}

							}

						}

						//Change the number
						sdata.at(posX).at(posY) = (45 - counter);
						doneLoop = true;

					}

				}

			}

		}




		//Next move on to the harder steps
		if (doneLoop == false) {

			//Make list of every possible number for every position
			vector<vector<vector<int>>> possibilities = getPossibilities(sdata);

			/*
			With this data made, we can do a lot of solving through process of elimination.
			After using this data to solve a position, the data has to be remade at the current point.
			With more development time, it would be possible to use the data for multiple solutions, which would make the algorithm much faster.
			So we will loop through every position and solve a number with one of 2 different kinds of proofs:
			
			1. this position only has one possible number as a possibility, therefore it is that number.
			2. in this square/row/column, there is only one time this number appears. Therefore, that is
			   the only place in the square/row/column that number could be, therefore that number is in that space.

			*/

			//Don't allow the algorithm to make 2 changes with the same data, this results in some weird numbers sometimes
			bool didOperation = false;

			//Loop through every position
			for (int a = 0; a < 9; a++) {

				for (int b = 0; b < 9; b++) {

					//a = sdata y position
					//b = sdata x position

					//If the only possibility is listed as 0, ignore this space
					if (possibilities.at(a).at(b).size() == 1 && possibilities.at(a).at(b).at(0) == 0) {

						//Do nothing (could inverse the logic on the if statement, but this is easier right now and it works)

					}
					//If there is only one possibility
					else if (possibilities.at(a).at(b).size() == 1 && didOperation == false) {

						//position is solved
						sdata.at(a).at(b) = possibilities.at(a).at(b).at(0);
						didOperation = true;
						doneLoop = true;

					}
					//If there are multiple possibilities
					else if (didOperation == false) {

						//Loop through each possibility
						for (int c = 0; c < possibilities.at(a).at(b).size(); c++) {

							//Search Row
							if (searchRowPossibilities(possibilities, possibilities.at(a).at(b).at(c), a) == false && didOperation == false) {
								
								//Position is solved
								sdata.at(a).at(b) = possibilities.at(a).at(b).at(c);
								didOperation = true;
								doneLoop = true;

							}

							//Search Column
							else if (searchColumnPossibilities(possibilities, possibilities.at(a).at(b).at(c), b) == false && didOperation == false) {
								
								//Position is solved
								sdata.at(a).at(b) = possibilities.at(a).at(b).at(c);
								didOperation = true;
								doneLoop = true;

							}

							//Search Square
							else if (searchSquarePossibilities(possibilities, possibilities.at(a).at(b).at(c), ((b / 3) * 3), ((a / 3) * 3)) == false && didOperation == false) {
								
								//Position is solved
								sdata.at(a).at(b) = possibilities.at(a).at(b).at(c);
								didOperation = true;
								doneLoop = true;

							}

						}
						
					}

				}

			}

		}



		//If nothing was done, exit the loop
		if (doneLoop == false) {

			done = true;

		}

	}

	return sdata;

}



//This function searches through all the possibilities in a square, and returns true if the number is found among them
bool searchSquarePossibilities(vector<vector<vector<int>>> possibilities, int num, int x, int y) {

	//Loop through every position in the square
	int found = 0;

	for (int a = y; a < (y + 3); a++) {

		for (int b = x; b < (x + 3); b++) {

			//Loop through every possibility in this position
			for (int c = 0; c < possibilities.at(a).at(b).size(); c++) {

				if (possibilities.at(a).at(b).at(c) == num) {

					//Found one
					found++;

				}

			}

		}

	}

	//Only return true if found more than one, since it will always find at least 1
	if (found > 1) {
		return true;
	}
	else {
		return false;
	}

}



//This function searches through all the possibilities in a column, and returns true if the number is found among them
bool searchColumnPossibilities(vector<vector<vector<int>>> possibilities, int num, int x) {

	//Loop through every position in the column
	int found = 0;

	for (int a = 0; a < 9; a++) {

		//Loop through every possibility in this position
		for (int b = 0; b < possibilities.at(a).at(x).size(); b++) {

			if (possibilities.at(a).at(x).at(b) == num) {

				//Found one
				found++;

			}

		}

	}

	//Only return true if found more than one, since it will always find at least 1
	if (found > 1) {
		return true;
	}
	else {
		return false;
	}

}



//This function searches through all the possibilities in a row, and returns true if the number is found among them
bool searchRowPossibilities(vector<vector<vector<int>>> possibilities, int num, int y) {

	//Loop through every position in the row
	int found = 0;

	for (int a = 0; a < 9; a++) {

		//Loop through every possibility in this position
		for (int b = 0; b < possibilities.at(y).at(a).size(); b++) {

			if (possibilities.at(y).at(a).at(b) == num) {

				//Found one
				found++;

			}

		}

	}

	//Only return true if found more than one, since it will always find at least 1
	if (found > 1) {
		return true;
	}
	else {
		return false;
	}

}



//This function makes a list of every possible number for every empty position
vector<vector<vector<int>>> getPossibilities(vector<vector<int>> sdata) {

	vector<vector<vector<int>>> possibilities;

	//Loop through every position in the puzzle
	for (int a = 0; a < 9; a++) {

		//Stores a line of possiblities
		vector<vector<int>> line;

		for (int b = 0; b < 9; b++) {

			//Stores a list of possibilities for a single point
			vector<int> list;

			//If the position is already filled in, just enter a 0
			if (sdata.at(a).at(b) != 0) {
				list.push_back(0);
			}
			//If not, check for possibilities
			else {

				//Loop through every possible number
				for (int c = 1; c < 10; c++) {

					/*
					a = sdata y position
					b = sdata x position
					c = current number being considered as a possibility
					*/

					bool found = false;

					//Search the line for the same number
					if (searchRow(sdata, c, a) == true) {
						found = true;
					}

					//Search the column for the same number
					else if (searchColumn(sdata, c, b) == true) {
						found = true;
					}

					//Search the square for the same number
					else if (searchSquare(sdata, c, ((b / 3) * 3), ((a / 3) * 3)) == true) {
						found = true;
					}

					//If these all pass, add the number as a possibility
					if (found == false) {
						list.push_back(c);
					}

				}
			}

			//Add the list to the current line
			line.push_back(list);

		}

		//Add the line to the full data set
		possibilities.push_back(line);

	}

	//Return the goods
	return possibilities;

}



//This function searches a square for a number, and returns true if the number is found
bool searchSquare(vector<vector<int>> sdata, int num, int x, int y) {

	//Loop through the square and search it
	bool found = false;
	for (int a = y; a < (y + 3); a++) {

		for (int b = x; b < (x + 3); b++) {

			if (sdata.at(a).at(b) == num) {

				//Found it
				found = true;

			}

		}

	}

	return found;

}



//This function searches a column for a number, and returns true if the number is found
bool searchColumn(vector<vector<int>> sdata, int num, int x) {

	//Loop through the column and search it
	bool found = false;
	for (int a = 0; a < 9; a++) {

		if (sdata.at(a).at(x) == num) {

			//Found it
			found = true;

		}

	}

	return found;

}



//This function searches a line for a number, and returns true if the number is found
bool searchRow(vector<vector<int>> sdata, int num, int y) {

	//Loop through the row and search it
	bool found = false;
	for (int a = 0; a < 9; a++) {

		if (sdata.at(y).at(a) == num) {

			//Found it
			found = true;
			
		}

	}

	return found;

}



//This function counts how many solved numbers are in a column
int countColumn(vector<vector<int>> sdata, int x) {

	//Loop through the column and count all the non zero numbers
	int counter = 0;

	for (int a = 0; a < 9; a++) {

		if (sdata.at(a).at(x) != 0) {

			counter++;

		}

	}

	return counter;

}



//This function counts how many solved numbers are in a square
int countSquare(vector<vector<int>> sdata, int x, int y) {

	//Loop through the square and count all the non zero numbers
	int counter = 0;

	for (int a = x; a < (x + 3); a++) {

		for (int b = y; b < (y + 3); b++) {

			if (sdata.at(b).at(a) != 0) {

				counter++;

			}

		}

	}

	return counter;

}



//This function counts how many solved numbers are in a row
int countRow(vector<vector<int>> sdata, int y) {

	//Loop through the row and count all the non zero numbers
	int counter = 0;

	for (int a = 0; a < 9; a++) {

		if (sdata.at(y).at(a) != 0) {

			counter++;

		}

	}

	return counter;

}