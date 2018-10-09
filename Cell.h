// a Cell is a square in the Minesweeper game

#pragma once

#ifndef Cell_H
#define Cell_h

class Cell {
public:
	int x;			// coordinate within the board
	int y;
	bool bomb;		// true if the Cell holds a bomb
	bool marked;	// true if the user right clicks the Cell
	int touching;	// number of bombs a Cell touches
	bool covered;	// true if Cell has never been clicked on
	bool mistake;	// true if user left clicks a bomb
	Cell();
	Cell(int, int, bool);	// include coordinate and bomb status
	void action(char);	// respond to left or right click
};

#endif // !Cell_H