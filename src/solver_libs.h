#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;
const unsigned char bigsquare_refs[81] = {
		 0, 0, 0, 1, 1, 1, 2, 2, 2,
		 0, 0, 0, 1, 1, 1, 2, 2, 2,
		 0, 0, 0, 1, 1, 1, 2, 2, 2,
		 3, 3, 3, 4, 4, 4, 5, 5, 5,
		 3, 3, 3, 4, 4, 4, 5, 5, 5,
		 3, 3, 3, 4, 4, 4, 5, 5, 5,
		 6, 6, 6, 7, 7, 7, 8, 8, 8,
		 6, 6, 6, 7, 7, 7, 8, 8, 8,
		 6, 6, 6, 7, 7, 7, 8, 8, 8,

};

/**
 * For refrence layout is as follows.
 *  0, 1, 2 |  3, 4, 5 |  6, 7, 8
 *  9,10,11 | 12,13,14 | 15,16,17
 * 18,19,20 | 21,22,23 | 24,25,26
 * ---------+----------+----------
 * 27,28,29 | 30,31,32 | 33,34,35
 * 36,37,38 | 39,40,41 | 42,43,44
 * 45,46,47 | 48,49,50 | 51,52,53
 * ---------+----------+---------
 * 54,55,56 | 57,58,59 | 60,61,62
 * 63,64,65 | 66,67,68 | 69,70,71
 * 72,73,74 | 75,76,77 | 78,79,80
 */
const unsigned char bigsquare_refs_pos[9][9] = {
		{ 0,  1,  2,  9, 10, 11, 18, 19, 20},
		{ 3,  4,  5, 12, 13, 14, 21, 22, 23},
		{ 6,  7,  8, 15, 16, 17, 24, 25, 26},
		{27, 28, 29, 36, 37, 38, 45, 46, 47},
		{30, 31, 32, 39, 40, 41, 48, 49, 50},
		{33, 34, 35, 42, 43, 44, 51, 52, 53},
		{54, 55, 56, 63, 64, 65, 72, 73, 74},
		{57 ,58 ,59, 66, 67, 68, 75, 76, 77},
		{60, 61, 62, 69, 70, 71, 78, 79, 80}
};

struct sudokuBoard {
	unsigned char	 numbers[81];
	unsigned char    possible_count[81];
	int              possible_updated[81];
	int update_counter;
};

sudokuBoard board;

void print_board() {
	for (int i = 0; i < 81; i++) {
			if (i % 27 == 0) {
				if (i != 0) {
					cout << '|';
				}
				 cout << endl << "+---+---+---+" << endl << '|';
			}
			else if(i % 9 == 0) {
				cout << '|' << endl << '|';
			}
			else if (i % 3 == 0) {
				cout << '|';
			}
			cout << char(board.numbers[i]+48);
		}
		cout << '|' << endl << "+---+---+---+" << endl;
}


bool number_is_possibe(unsigned char pos, unsigned char check_number) {
	if(board.numbers[pos] != 0) {
		return false;
	}
    bool check = true;
    unsigned char start = pos - (pos % 9);
    check = check && (board.numbers[start] != check_number);
    check = check && (board.numbers[start+1] != check_number);
    check = check && (board.numbers[start+2] != check_number);
    check = check && (board.numbers[start+3] != check_number);
    check = check && (board.numbers[start+4] != check_number);
    check = check && (board.numbers[start+5] != check_number);
    check = check && (board.numbers[start+6] != check_number);
    check = check && (board.numbers[start+7] != check_number);
    check = check && (board.numbers[start+8] != check_number);

    start = pos%9;
    check = check && (board.numbers[start] != check_number);
    check = check && (board.numbers[start+9] != check_number);
    check = check && (board.numbers[start+18] != check_number);
    check = check && (board.numbers[start+27] != check_number);
    check = check && (board.numbers[start+36] != check_number);
    check = check && (board.numbers[start+45] != check_number);
    check = check && (board.numbers[start+54] != check_number);
    check = check && (board.numbers[start+63] != check_number);
    check = check && (board.numbers[start+72] != check_number);

    start = bigsquare_refs[pos];
    check = check && (board.numbers[bigsquare_refs_pos[start][0]] != check_number);
    check = check && (board.numbers[bigsquare_refs_pos[start][1]] != check_number);
    check = check && (board.numbers[bigsquare_refs_pos[start][2]] != check_number);
    check = check && (board.numbers[bigsquare_refs_pos[start][3]] != check_number);
    check = check && (board.numbers[bigsquare_refs_pos[start][4]] != check_number);
    check = check && (board.numbers[bigsquare_refs_pos[start][5]] != check_number);
    check = check && (board.numbers[bigsquare_refs_pos[start][6]] != check_number);
    check = check && (board.numbers[bigsquare_refs_pos[start][7]] != check_number);
    check = check && (board.numbers[bigsquare_refs_pos[start][8]] != check_number);
	return check;
}

bool number_can_only_go(unsigned char pos, unsigned char check_number) {
	bool row_only_check, column_only_check, bigsquare_only_check;

	row_only_check = true;
	for (int k = (pos - (pos % 9)); k < (pos - (pos % 9) +9); k++) {
		if (k==pos) {continue;}
		if(number_is_possibe(k,check_number)) {
			row_only_check = false;
		}
	}


	column_only_check = true;
	for (int k = (pos%9); k < 81; k+=9) {
	    if(k==pos) {continue;}
		if(number_is_possibe(k,check_number)) {
					column_only_check = false;
				}
	}
	bigsquare_only_check = true;
	unsigned char bigsquare = bigsquare_refs[pos];

	for (int k = 0; k < 9; k++) {
		if(bigsquare_refs_pos[bigsquare][k] == pos) { continue ;}
		if (number_is_possibe(bigsquare_refs_pos[bigsquare][k],check_number)) {
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

int possibility_count(unsigned char pos) {
	// Work out possible numbers
	if(board.numbers[pos] != 0) {
		return 0;
	}
	if(board.possible_updated[pos] == board.update_counter) {
		return board.possible_count[pos];
	}

	bool possible[10] = { true, true, true, true, true, true, true, true,
			true, true };

	// Check the numbers in the row and remove them from possible numbers.
	unsigned char start = pos - (pos % 9);
	possible[board.numbers[start]] = false;
	possible[board.numbers[start+1]] = false;
	possible[board.numbers[start+2]] = false;
	possible[board.numbers[start+3]] = false;
	possible[board.numbers[start+4]] = false;
	possible[board.numbers[start+5]] = false;
	possible[board.numbers[start+6]] = false;
	possible[board.numbers[start+7]] = false;
	possible[board.numbers[start+8]] = false;

	start = pos%9;
    // Check the numbers in the col and remove them from possible numbers.
	possible[board.numbers[start]] = false;
	possible[board.numbers[start+9]] = false;
	possible[board.numbers[start+18]] = false;
	possible[board.numbers[start+27]] = false;
	possible[board.numbers[start+36]] = false;
	possible[board.numbers[start+45]] = false;
	possible[board.numbers[start+54]] = false;
	possible[board.numbers[start+63]] = false;
	possible[board.numbers[start+72]] = false;

	start = bigsquare_refs[pos];

	possible[board.numbers[bigsquare_refs_pos[start][0]]] = false;
	possible[board.numbers[bigsquare_refs_pos[start][1]]] = false;
	possible[board.numbers[bigsquare_refs_pos[start][2]]] = false;
	possible[board.numbers[bigsquare_refs_pos[start][3]]] = false;
	possible[board.numbers[bigsquare_refs_pos[start][4]]] = false;
	possible[board.numbers[bigsquare_refs_pos[start][5]]] = false;
	possible[board.numbers[bigsquare_refs_pos[start][6]]] = false;
	possible[board.numbers[bigsquare_refs_pos[start][7]]] = false;
	possible[board.numbers[bigsquare_refs_pos[start][8]]] = false;



	int possible_count = 0;
	for (int k = 1; k < 10; k++) {
		if (possible[k]) {
			possible_count++;
		}


	}
	board.possible_count[pos] = possible_count;
	board.possible_updated[pos] = board.update_counter;
	return possible_count;
}


int solve_board(const char instring[82]) {



	// Put string into 9x9 array for easier refernce
	for (int i = 0; i < 81; i++) {
		if (instring[i] >= 48 && instring[i] < 58) {
			board.numbers[i] = instring[i] - 48;
			board.possible_count[i]=0;
		} else {
			board.numbers[i] = 0;
			board.possible_count[i]=9;
		}
		board.possible_updated[i] = -1;
	}
    board.update_counter=0;

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
			for (unsigned char i = 0; i < 81; i++) {
					//Only look blank squares.
					if (board.numbers[i] == 0) {
						// First check if it is possible to place check_number in this square
						if (!number_is_possibe(i,check_number)) {
							continue;
						}
						// Then check if check_number HAS to go in this square
						// Work out possible numbers
						// TODO: investigate sets.
						int possible_count = possibility_count(i);
						if (possible_count == 1) {
							board.numbers[i] = check_number;
							board_changed = true;
							board.update_counter++;
                            #ifdef DEBUG
							cout << char(i%9+48) << ',' << char(i/9+48) << '=' << char(check_number+48) << " has to go"<< endl;
							print_board(board);
                            #endif
							continue;
						}

						// Finally check if it is only possible for check_number to go in this square.
                       if(number_can_only_go(i,check_number)) {
                        	board.numbers[i] = check_number;
                            board_changed = true;
                            board.update_counter++;
                            #ifdef DEBUG
							cout << char(i%9+48) << ',' << char(i/9+48)  << '=' << char(check_number+48) << " only possible" << endl;
							print_board(board);
                            #endif
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
    for (int i = 0; i < 81; i++) {
    	if (board.numbers[i] == 0) solved = false;
    }
    // TODO: add validator to check results (very important for testing).

	// Output final board
    #ifdef DEBUG
	print_board(board);
    #endif
	return (int) solved;
}
