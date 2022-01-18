/*
	Author: Michael Stepzinski
	Date: 10/3/21
	Purpose: Minimax code and helper functions for TicTacToe
*/

#include <tictac_support.h>
#include <stdio.h>
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

int make_move( int board[][3] )
{
	// inform the user that the program is working
	printf("Processing...\n");
	int winner = evaluate(board);
	// if evaluate is -1 or 1 then that's the winner
	if (winner != 0)
	{	
		printf("%d has already won!\n", winner);
		return 0;
	}
	// if there's no winner and no moves are available, then its a tie
	if (winner == 0)
	{
		if (moves_left(board) == 0)
		{
			printf("It's a tie!\n");
			return 0;
		}
	}
	
	// figure out what move it is
	int state = 0;
	for( int i = 0; i < 3; i++ )
		for( int j = 0; j < 3; j++ )
			state += board[i][j];

	state = -state;
	if( state == 0 )
		state = 1;

	// translate state to max and min
	bool isMax;
	if ( state == 1 )
		isMax = true;
	else
		isMax = false;

	int bestScore, currentScore;
	Move move;
	// if max, set minimum value to bestScore
	// if min, set maximum value to bestScore
	if ( isMax )
		bestScore = -1000;
	else
		bestScore = 1000;

	// iterate through all moves, run minimax on each, take best score
	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			// make move if spot is open
			if ( board[i][j] == 0 )
			{
				board[i][j] = state;

				//if this move can instantly win the game, make the move
				if (evaluate(board) == state)
				{
					move.row = i;
					move.col = j;
					board[move.row][move.col] = state;
					printf("%d move made at %d, %d\n", state, move.row, move.col);
					return 0;
				}
				// otherwise,
				// find minimax score of move
				//print_board(board);
				currentScore = minimax (board, !isMax);
				//print_board(board);

				//undo move
				board[i][j] = 0;

				//if currentScore is better, replace best with current and save move location
				// currentScore >  bestScore when max
				if (isMax)
				{
					if (currentScore > bestScore)
					{
						bestScore = currentScore;
						move.row = i;
						move.col = j;
					}
				}
				// currentScore < bestScore when min
				else
				{
					if (currentScore < bestScore)
					{
						bestScore = currentScore;
						move.row = i;
						move.col = j;
					}
				}
			}	
		}
	}

	// make move, announce move is made
	board[move.row][move.col] = state;
	printf("%d move made at %d, %d\n", state, move.row, move.col);

	return 0;
}

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
int minimax ( int board[][3], bool isMax )
{
	// terminate when no more moves left
	// or terminate when move causes a win
	print_board(board);
	if (!moves_left(board))
		return 0;
	else if (evaluate(board) == 1)
		return 1;
	else if (evaluate(board) == -1)
		return -1;

	// if no escape, check minimax score of opponent move
	int bestScore, currentScore, state;
	// if max, set bestScore to minimum value
	// if min, set bestScore to maximum value
	if ( isMax )
	{
		bestScore = -1000;
		state = 1;
	}
	else
	{
		bestScore = 1000;
		state = -1;
	}

	// iterate through all moves, run minimax on each, take best score
	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			// make move if spot is open
			if ( board[i][j] == 0 )
			{
				board[i][j] = state;
				//print_board(board);

				// find minimax score of move, use !isMax to find minimax of opponent move
				currentScore = minimax (board, !isMax);

				//undo move
				board[i][j] = 0;
				// find highest score possible for max
				if (isMax)
					if(currentScore > bestScore)
						bestScore = currentScore;
				// find lowest score possible for min
				if (isMax == false)
					if (currentScore < bestScore)
						bestScore = currentScore;
			}
		}
	}
	// return the best score from move
	return bestScore;
}

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
bool moves_left( int board[][3] )
{
	// iterate over all spots, check for empty spot
	// if empty spot, return true
	// if no empty spot, return false
	for ( int i = 0; i < 3; i++ )
		for ( int j = 0; j < 3; j++ )
			if ( board[i][j] == 0 )
				return true;
	return false;
}

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
int evaluate ( int board[][3] )
{
	// check to see if there is a winner
	// if there is a winner, return winner score
	for ( int i = 0; i < 3; i++)
	{
		// check rows, make sure number is not 0
		if ( (board[i][0] == board[i][1]) && (board[i][1] == board[i][2]) )
			if ( board[i][1] != 0 )
				return board[i][1];
		// check cols, make sure num is not 0
		if ( (board[0][i] == board[1][i]) && (board[1][i] == board[2][i]) )
			if ( board[1][i] != 0 )
				return board[1][i];
	}
	// check diagonals, make sure num is not 0
	if ( (board[0][0] == board[1][1]) && (board[1][1] == board[2][2]) )
		if ( board[1][1] != 0 )
			return board[1][1];
	if ( (board[0][2] == board[1][1]) && (board[1][1] == board[2][0]) )
		if ( board[1][1] != 0 )
			return board[1][1];
	// if none of the above conditions returned, no winner return 0
	return 0;
}

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
void print_board ( int board[][3] )
{
	printf("board:\n");
	for (int i = 0; i < 3; i++)
	{
		printf("%d %d %d\n", board[i][0], board[i][1], board[i][2]);
	}
}