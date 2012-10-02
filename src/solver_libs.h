#include <iostream>
#include <stdint.h>
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

/*
 * Use 4 bytes to store a square and it's state
 *
 * 01|02|03|04|05|06|07|08||09|10|11|12|13|14|15|16||17|18|19|20|21|22|23|24||25|26|27|28|29|30|31|32
 * F1|S1|03|04|05|06|07|V1||V2|V3|V4|V5|V6|V7|V8|V9||P1|P2|P3|P4|P5|P6|P7|N1||N2|N3|N4|N5|N6|N7|N8|N9
 *
 * PP the squares position 0-81 (shift right one and use as unsigned byte)
 * V1-V9 The value in the square if F1 is set.
 * N1-N9 The possible values that the square could be.
 * NN possiblity set 24 = 1 possible -- 32 9 possible
 * VV the squares value
 * F1 solved flag
 * S1 Stale flag
 */

const uint32_t number_masks[9] = {
	0x00000001, // 1
	0x00000002, // 2
	0x00000004, // 3
	0x00000008, // 4
	0x00000010, // 5
	0x00000020, // 6
	0x00000040, // 7
	0x00000080, // 8
	0x00000100, // 9
};

struct sudokuBoard {
	uint32_t numbers[81];
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
			//TODO: work out the number and if it is set.
			char number;
			if (board.numbers[i] & 0x80000000) {
			    uint32_t working;
                working = board.numbers[i] >> 16;
                // lowest bit set hack from bit twiddling how to.
                working = (working ^ (working - 1)) >> 1;
                for (number = 49; working; number++)
                  {
                	//cout << working << endl;
                	working >>= 1;
                  }
			}
			else {
				number = 48;
			}

			cout << char(number);
		}
		cout << '|' << endl << "+---+---+---+" << endl;
}



bool number_can_only_go(unsigned char pos, unsigned char check_number) {
	bool row_only_check, column_only_check, bigsquare_only_check;

	row_only_check = true;
	for (int k = (pos - (pos % 9)); k < (pos - (pos % 9) +9); k++) {
		if (k==pos) {continue;}
		row_only_check &= !(board.numbers[k] & number_masks[check_number-1]);
	}


	column_only_check = true;
	for (int k = (pos%9); k < 81; k+=9) {
	    if(k==pos) {continue;}
		column_only_check &= !(board.numbers[k] & number_masks[check_number-1]);
	}
	bigsquare_only_check = true;
		unsigned char bigsquare = bigsquare_refs[pos];

	for (int k = 0; k < 9; k++) {
		if(bigsquare_refs_pos[bigsquare][k] == pos) { continue ;}
		  bigsquare_only_check &= !(board.numbers[bigsquare_refs_pos[bigsquare][k]] & number_masks[check_number-1]);
		}
    // TODO: other cases??

	if (bigsquare_only_check || row_only_check
			|| column_only_check) {
		return true;
	}
	return false;
}

unsigned char possibility_count(unsigned char pos) {
	// Work out possible numbers
	if(board.numbers[pos] & 0x80000000) {
		return 0;
	}
	unsigned char count = 0;
	uint32_t working_copy = board.numbers[pos];
	// Do a POPCOUNT of the lower 9 bits
   count += ((working_copy) %2);
   count += ((working_copy >>= 1) %2);
   count += ((working_copy >>= 1) %2);
   count += ((working_copy >>= 1) %2);
   count += ((working_copy >>= 1) %2);
   count += ((working_copy >>= 1) %2);
   count += ((working_copy >>= 1) %2);
   count += ((working_copy >>= 1) %2);
   count += ((working_copy >>= 1) %2);
   return count;
}

/**
 *  Set a number on the board and remove possiblites from other squares.
 *  There will be a maximium of 82 sets so this can be more expensive if
 *  it makes checks quicker
 */
void set_number(unsigned char pos, unsigned char number) {
	uint32_t number_mask = number_masks[number-1];
	uint32_t shifted_mask = number_mask << 16;
	board.numbers[pos] |= 0x80000000 | shifted_mask; // Set the number and the solved flag.
    board.numbers[pos] &= ~0x000001FF; // Remove any possiblities from the square.
// TODO: check here for pos 33 on creation and change.
	unsigned char start = pos - (pos % 9);
	board.numbers[start] &= ~number_mask;
	board.numbers[start+1] &= ~number_mask;
	board.numbers[start+2] &= ~number_mask;
	board.numbers[start+3] &= ~number_mask;
	board.numbers[start+4] &= ~number_mask;
	board.numbers[start+5] &= ~number_mask;
	board.numbers[start+6] &= ~number_mask;
	board.numbers[start+7] &= ~number_mask;
	board.numbers[start+8] &= ~number_mask;

	start = pos%9;
    // Check the numbers in the col and remove them from possible numbers.
	board.numbers[start] &= ~number_mask;
	board.numbers[start+9] &= ~number_mask;
	board.numbers[start+18] &= ~number_mask;
	board.numbers[start+27] &= ~number_mask;
	board.numbers[start+36] &= ~number_mask;
	board.numbers[start+45] &= ~number_mask;
	board.numbers[start+54] &= ~number_mask;
	board.numbers[start+63] &= ~number_mask;
	board.numbers[start+72] &= ~number_mask;

	start = bigsquare_refs[pos];

	board.numbers[bigsquare_refs_pos[start][0]] &= ~number_mask;
	board.numbers[bigsquare_refs_pos[start][1]] &= ~number_mask;
	board.numbers[bigsquare_refs_pos[start][2]] &= ~number_mask;
	board.numbers[bigsquare_refs_pos[start][3]] &= ~number_mask;
	board.numbers[bigsquare_refs_pos[start][4]] &= ~number_mask;
	board.numbers[bigsquare_refs_pos[start][5]] &= ~number_mask;
	board.numbers[bigsquare_refs_pos[start][6]] &= ~number_mask;
	board.numbers[bigsquare_refs_pos[start][7]] &= ~number_mask;
	board.numbers[bigsquare_refs_pos[start][8]] &= ~number_mask;
}

int solve_board(const char instring[82]) {


	//std::fill_n(board, 81, 0x1FF);
    //TODO: set the location number

	// Put string into 9x9 array for easier refernce
	for (int i = 0; i < 81; i++) {
		board.numbers[i] = 0x000001FF;
	}
	for (int i = 0; i < 81; i++) {
        if (instring[i] > 48 && instring[i] < 58) {
			set_number(i,instring[i] - 48);
		}
	}
	// Output board
    #ifdef DEBUG
	print_board();
    #endif
	unsigned char check_number = 0;
	bool board_changed;
	// Start with a slow but potentially easy to understand algrothim
	for (;;) {
		board_changed = false;
		// Iterate over the numbers 1-9 indefintly.
		for (check_number = 1; check_number < 10; check_number++) {
			for (unsigned char i = 0; i < 81; i++) {
						// First check if it is possible to place check_number in this square
						if ((board.numbers[i] & 0x80000000) || !(number_masks[check_number-1] & board.numbers[i])) {
							continue;
						}
						// Then check if check_number HAS to go in this square
						// Work out possible numbers
						// TODO: investigate sets.
						int possible_count = possibility_count(i); // Is this correct?
						//cout << possible_count << endl;
						// TODO: debug from here on in.
						if (possible_count == 1) {
							set_number(i,check_number);
							board_changed = true;
                            #ifdef DEBUG
							cout << char(i%9+48) << ',' << char(i/9+48) << '=' << char(check_number+48) << " has to go"<< endl;
							print_board();
                            #endif
							continue;
						}

						// Finally check if it is only possible for check_number to go in this square.
                       // TODO: debug this.
						if(number_can_only_go(i,check_number)) {
                    	    set_number(i,check_number);
                    	   	board_changed = true;
                            #ifdef DEBUG
							cout << char(i%9+48) << ',' << char(i/9+48)  << '=' << char(check_number+48) << " only possible" << endl;
							print_board();
                            #endif
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
    	if (!(board.numbers[i] & 0x80000000)) solved = false;
    }
    // TODO: add validator to check results (very important for testing).

	// Output final board
    #ifdef DEBUG
	print_board();
    #endif

	return (int) solved;

	return 0;
}
