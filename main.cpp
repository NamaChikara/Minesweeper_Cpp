// This file uses Probability.h, Cell.h, and Board.h to generate a
//  Minesweeper game and keep track of user progress.  It requires
//  the SFML graphics library to run.

#include <SFML/Graphics.hpp>
#include "Probability.h"
#include "Board.h"

int main()
{
	// test the Board constructor
	Board board1{ 6,10 };
	board1.print_board();
	std::cin.get();
}
