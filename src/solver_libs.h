#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

struct nineInt {
	int item[9];
};

struct sudokuBoard {
	int numbers[9][9];
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
				cout << board.numbers[j][i];
			}
			cout << '|' << endl;
		}

		cout << "+---+---+---+" << endl;
}

nineInt bigsquare_row_ids(int col, int row) {
	int bigsquare_row_start = row - (row % 3);
	nineInt rows;
	for (int i = 0; i < 9; i++) {
		rows.item[i] = bigsquare_row_start + (i / 3);
	}
	return rows;
}

nineInt bigsquare_col_ids(int col, int row) {
	int bigsquare_col_start = col - (col % 3);
	nineInt cols;
	//TODO: change this logic so it does 111222333
	for (int i = 0; i < 9; i++) {
		cols.item[i] = bigsquare_col_start + (i % 3);
	}
	return cols;
}

bool number_is_possibe(int col, int row, int check_number, sudokuBoard board) {
	bool row_possible_check, column_possible_check, bigsquare_possible_check;
	nineInt bigsquare_row_ref;
	nineInt bigsquare_col_ref;

	if(board.numbers[col][row] != 0) {
		return 0;
	}

	bigsquare_row_ref = bigsquare_row_ids(col, row);
	bigsquare_col_ref = bigsquare_col_ids(col, row);

	row_possible_check = true;
	for (int k = 0; k < 9; k++) {
		if (board.numbers[col][k] == check_number) {
			row_possible_check = false;
		}
	}
	column_possible_check = true;
	for (int k = 0; k < 9; k++) {
		if (board.numbers[k][row] == check_number) {
			column_possible_check = false;
		}
	}
	bigsquare_possible_check = true;

	for (int k = 0; k < 9; k++) {
		int bs_row = bigsquare_row_ref.item[k];
		int bs_col = bigsquare_col_ref.item[k];
		if (board.numbers[bs_col][bs_row] == check_number) {
			bigsquare_possible_check = false;
		}
	}

	if (!bigsquare_possible_check || !row_possible_check
			|| !column_possible_check) {
		return false;
	}
	return true;
}

bool number_can_only_go(int col, int row, int check_number, sudokuBoard board) {
	bool row_only_check, column_only_check, bigsquare_only_check;
	nineInt bigsquare_row_ref;
	nineInt bigsquare_col_ref;
	bigsquare_row_ref = bigsquare_row_ids(col, row);
	bigsquare_col_ref = bigsquare_col_ids(col, row);

	row_only_check = true;
	for (int k = 0; k < 9; k++) {
		if (k==row) {continue;}
		if(number_is_possibe(col,k,check_number,board)) {
			row_only_check = false;
		}
	}
	column_only_check = true;
	for (int k = 0; k < 9; k++) {
		if(k==col) {continue;}
		if(number_is_possibe(k,row,check_number,board)) {
					column_only_check = false;
				}
	}
	bigsquare_only_check = false;
	for (int k = 0; k < 9; k++) {
		int bs_row = bigsquare_row_ref.item[k];
		int bs_col = bigsquare_col_ref.item[k];
		if(bs_row == row && bs_col == col) { continue ;}
		if (number_is_possibe(bs_col,bs_row,check_number,board)) {
			bigsquare_only_check = false;
		}
		}
    // TODO: other cases??

	if (bigsquare_only_check || row_only_check
			|| column_only_check) {
		return true;
	}
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

		nineInt bigsquare_row = bigsquare_row_ids(col, row);
		nineInt bigsquare_col = bigsquare_col_ids(col, row);
		if (board.numbers[bigsquare_col.item[k]][bigsquare_row.item[k]] != 0) {
			bigsquare_possible[board.numbers[bigsquare_col.item[k]][bigsquare_row.item[k]]
					- 1] = false;
			}
	}

	int possible_count = 0;
	for (int k = 0; k < 9; k++) {
		if (row_possible[k] && column_possible[k] && bigsquare_possible[k]) {
			possible_count++;
		}
		if(col == 1 && row == 5)
	    	cout << col << k << row_possible[k] << column_possible[k] << bigsquare_possible[k] << endl;

	}
	return possible_count;
}


int solve_board(char instring[82]) {

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
	print_board(board);

	int check_number = 0;
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
							// TODO: put in compiler flags for showing debug.
							cout << i << "," << j << '=' << check_number << " has to go"<< endl;
							print_board(board);
							continue;
						}

						// Finally check if it is only possible for check_number to go in this square.
                       if(number_can_only_go(i,j,check_number,board)) {
                        	board.numbers[i][j] = check_number;
                            board_changed = true;
							// TODO: put in compiler flags for showing debug.
                            cout << i << "," << j << '=' << check_number << " only possible" << endl;
							print_board(board);
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

    // TODO: add validator to check results (very important for testing).

	// Output final board
	print_board(board);
	return 1;
}