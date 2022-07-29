# SudokuSolver

## What is this?

This is SudokuSolver, a quick algorithm I made over the course of about 8 hours or so total. It takes a sudoku puzzle as input from a text file, and solves it as best it can. While not reliable with high difficulty puzzles, it seems to work perfectly for average difficulty ones.

## How does it work?

This algorithm has a few different strategies it uses to solve cells, and it runs them in order from least to most difficult to compute. As soon as one of them works, it starts again from the first strategy, and if it runs through every one of them without changing anything, the algorithm ends. Here are the three basic strategies used by the algorithm in order:

1. If a row/column/square is missing only one number, add the last one. Since every row, column, and square add up to 45, this is very easy to compute.

2. If a cell has only one possible number that could be there (through process of elimination), that number belongs in that cell. This is the main way of solving sudokus and is used for most of the algorithm.

3. If a row/column/square has only one location where a number can belong, that number belongs in that cell. This is a slightly more advanced way of solving sudokus, and only comes in use when the first 2 strategies aren’t affective.

## How could it be improved?

Since this program was created in a very small time frame, there are a few notable weaknesses. First, it is not very fast in its current state. I originally intended it so that when the algorithm creates a list of every possible number in every empty cell, it could use that data to solve multiple cells. However, I haven’t yet been able to implement this feature, so for now it just makes a new list after every solved cell. While this is much slower, it does work, which is much better than a broken algorithm. The other weakness is that it can’t solve higher difficulty puzzles, and will just give up when it can’t solve any more. This is because the algorithm cannot make any 50/50 decisions, since then there might be a chance it is incorrect. This could be solved by implementing a strategy using recursion along with the current algorithm. This would make it able to backtrack if the decision was incorrect, and it would be able to solve much higher difficulty puzzles. While this program has these 2 flaws, it still works very well and these flaws could be pretty easily solved with more development time.
