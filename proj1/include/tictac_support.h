#ifndef _TICTAC_SUPPORT_H_
#define _TICTAC_SUPPORT_H_

#include <string>

/**
	load_board: loads a tic-tac-toe board state from a file

	args:
		std::string filename: file to read the board from
		int [][3] board: 3x3 array of ints representing the board state
			0: empty
			1: x
		 -1: o

	returns (int):
		0: if file loaded OK
		-1: if file doesn't exist

**/

int load_board( std::string filename, int board[][3] );


/**
	save_board: saves a tic-tac-toe board state to a file

	args:
		std::string filename: file to write the board to
		int [][3] board: 3x3 array of ints representing the board state
			0: empty
			1: x
		 -1: o

	returns (int):
		0: if file opened OK
		-1: if file can't be opened

**/

int save_board( std::string filename, int board[][3] );

/**
	make_move: takes a board state and makes a legal 
	(hopefully optimal) move

	args:
		int [][3] board: 3x3 array of ints representing the 
		board state. The values of board are altered based
		on the move
			0: empty
			1: x
		   -1: o
		
	returns (int):
		0 : exit function or move made (program always returns 0)
**/

int make_move( int board[][3] );

/**
	minimax: takes a board state and a player and gives a move score

	args:
		int [][3] board: 3x3 array of ints representing the 
		board state. The values of board are altered based
		on the move
			0: empty
			1: x
		   -1: o

		bool isMax: bool value representing player turn
			false or 0: min
			true or  1: max
		
	returns (int):
		-1: move gives -1 points
		 0: move gives 0 points
		 1: move gives 1 points
**/

int minimax ( int board[][3], bool isMax );

/**
	moves_left: checks if there are empty spaces on the board

	args:
		int [][3] board: 3x3 array of ints representing the 
		board state. The values of board are altered based
		on the move
			0: empty
			1: x
		   -1: o
		
	returns (bool):
		true: there are moves left
		false: there are no moves left
**/
bool moves_left( int board[][3] );

/**
	evaluate: gives a score value for a board state

	args:
		int [][3] board: 3x3 array of ints representing the 
		board state. The values of board are altered based
		on the move
			0: empty
			1: x
		   -1: o
		
	returns (int):
		-1: -1 wins
		 0: tie
		 1: 1 wins
**/
int evaluate ( int board[][3] );

/**
	print board: prints the current board state

	args:
		int [][3] board: 3x3 array of ints representing the 
		board state. The values of board are altered based
		on the move
			0: empty
			1: x
		   -1: o
		
	returns (void):
		none
		but the functions prints the current board state
**/
void print_board ( int board[][3] );

/**
	Move: struct to store a move

	members:
		int row : stores an integer representing the row
		int col : stores an integer representing the column
**/
struct Move
{
	int row, col;
};

#endif