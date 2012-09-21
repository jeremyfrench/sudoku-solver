#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

struct gridref {
	unsigned char row;
	unsigned char col;
};

struct gridreflist {
	gridref positions[9];
};

struct nineInt {
	unsigned char item[9];
};

struct sudokuBoard {
	unsigned char	 numbers[9][9];
};

void print_board(sudokuBoard board) {
	for (int i = 0; i < 9; i++) {
			if (i % 3 == 0) {
				cout << "+---+---+---+" << endl;
			}
			for (int j = 0; j < 9; j++) {
				if (j % 3 == 0) {
					cout << '|';
				}
				cout << char(board.numbers[j][i]+48);
			}
			cout << '|' << endl;
		}

		cout << "+---+---+---+" << endl;
}

gridreflist bigsquare_refs(int col, int row) {
	unsigned char bigsquare_col_start = col - (col % 3);
	unsigned char bigsquare_row_start = row - (row % 3);
    gridreflist refs;
    for (int i = 0; i < 9; i++) {
    	refs.positions[i].row = bigsquare_row_start + (i / 3);
    	refs.positions[i].col = bigsquare_col_start + (i % 3);
    }
    return refs;
}


bool number_is_possibe(int col, int row, int check_number, sudokuBoard board) {
	if(board.numbers[col][row] != 0) {
		return false;
	}
	for (int k = 0; k < 9; k++) {
		if (board.numbers[col][k] == check_number) {
			return false;
		}
		if (board.numbers[k][row] == check_number) {
			return false;
		}
	}
	gridreflist refs = bigsquare_refs(col,row);
	for (int k = 0; k < 9; k++) {
		if (board.numbers[refs.positions[k].col][refs.positions[k].row] == check_number) {
			return false;
		}
	}
	return true;
}

bool number_can_only_go(int col, int row, int check_number, sudokuBoard board) {

	bool row_only_check = true;
	for (int k = 0; k < 9; k++) {
		if (k==row) {continue;}
		if(number_is_possibe(col,k,check_number,board)) {
			row_only_check = false;
		}
	}
	if(row_only_check) { return true; }

	bool column_only_check = true;
	for (int k = 0; k < 9; k++) {
		if(k==col) {continue;}
		if(number_is_possibe(k,row,check_number,board)) {
					column_only_check = false;
				}
	}
	if(column_only_check) { return true; }

	bool bigsquare_only_check = false;
    gridreflist refs = bigsquare_refs(col,row);
	for (int k = 0; k < 9; k++) {
		int bs_row = refs.positions[k].row;
		int bs_col = refs.positions[k].col;
		if(bs_row == row && bs_col == col) { continue ;}
		if (number_is_possibe(bs_col,bs_row,check_number,board)) {
			bigsquare_only_check = false;
		}
	}
    if(bigsquare_only_check) { return true; }
    return false;
}

int possibility_count(int col, int row, sudokuBoard board) {
	// Work out possible numbers
	if(board.numbers[row][col] != 0) {
		return 0;
	}

	bool row_possible[9] = { true, true, true, true, true, true, true, true,
			true };
	bool column_possible[9] = { true, true, true, true, true, true, true, true,
			true };
	bool bigsquare_possible[9] = { true, true, true, true, true, true, true,
			true, true };

	for (int k = 0; k < 9; k++) {
		if (board.numbers[k][row] != 0) {
			row_possible[board.numbers[k][row] - 1] = false;
		}
	}
	for (int k = 0; k < 9; k++) {
		if (board.numbers[col][k] != 0) {
			column_possible[board.numbers[col][k] - 1] = false;
		}
	}

	for (int k = 0; k < 9; k++) {

		gridreflist refs = bigsquare_refs(col,row);

		if (board.numbers[refs.positions[k].col][refs.positions[k].row] != 0) {
			bigsquare_possible[board.numbers[refs.positions[k].col][refs.positions[k].row]
					- 1] = false;
			}
	}

	int possible_count = 0;
	for (unsigned char k = 0; k < 9; k++) {
		if (row_possible[k] && column_possible[k] && bigsquare_possible[k]) {
			possible_count++;
		}

	}
	return possible_count;
}


int solve_board(const char instring[82]) {

	sudokuBoard board;

	// Put string into 9x9 array for easier refernce
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			// only put put in if it is a number.
			if (instring[(i * 9) + j] >= 48 && instring[(i * 9) + j] < 58) {
				board.numbers[j][i] = instring[(i * 9) + j] - 48;
			} else {
				board.numbers[j][i] = 0;
			}
		}
	}

	// Output board
    #ifdef DEBUG
	print_board(board);
    #endif
	unsigned char check_number = 0;
	bool board_changed;
	// Start with a slow but potentially easy to understand algrothim
	for (;;) {
		board_changed = false;
		// Iterate over the numbers 1-9 indefintly.
		for (check_number = 1; check_number < 10; check_number++) {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					//Only look blank squares.
					if (board.numbers[i][j] == 0) {
						// First check if it is possible to place check_number in this square
						if (!number_is_possibe(i,j,check_number,board)) {
							continue;
						}
						// Then check if check_number HAS to go in this square
						// Work out possible numbers
						// TODO: investigate sets.
						int possible_count = possibility_count(i, j, board);
						if (possible_count == 1) {
							board.numbers[i][j] = check_number;
							board_changed = true;
                            #ifdef DEBUG
							cout << i << "," << j << '=' << char(check_number+48) << " has to go"<< endl;
							print_board(board);
                            #endif
							continue;
						}

						// Finally check if it is only possible for check_number to go in this square.
                       if(number_can_only_go(i,j,check_number,board)) {
                        	board.numbers[i][j] = check_number;
                            board_changed = true;
                            #ifdef DEBUG
							cout << i << "," << j << '=' << char(check_number+48) << " only possible" << endl;
							print_board(board);
                            #endif
                       }
					}
				}
			}
		}

		// If after checking all numbers no changes have been made then exit.
		if (!board_changed) {
			break;
		}
	}

	// Check to see if solved.
    bool solved = true;
    for (int i = 0; i < 9; i++) {
    				for (int j = 0; j < 9; j++) {
    					if (board.numbers[i][j] == 0) solved = false;
    				}
    }
    // TODO: add validator to check results (very important for testing).

	// Output final board
    #ifdef DEBUG
	print_board(board);
    #endif
	return (int) solved;
}
