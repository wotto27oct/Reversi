#include "main.hpp"

// return reversable num in the direction of (k, l) from (i, j)
int search_reversable_num_indir(int m, int i, int j) {
	int k, l;
	if (m == 0 || m == 1 || m == 7) k = -1;
	else if (m == 2 || m == 6) k = 0;
	else k = 1;
	if (m == 1 || m == 2 || m == 3) l = -1;
	else if (m == 0 || m == 5) l = 0;
	else l = 1;

	int n = 1;
	while (i + n * k >= 0 && i + n * k < 8 && j + n * l >= 0 && j + n * l < 8) {
		if (field[i + n * k][j + n * l] == -1) return 0;
		else if (field[i + n * k][j + n * l] == turn) {
			// eg) 1, -1, -1, 1 (n = 3)
			return n - 1;
		}
		n++;
	}
	return 0;
}

// reverse field of putting a piece to (i, j)
void reverse_field(int i, int j) {
	// (-1,0), (-1,-1), (0,-1),...
	for (int m = 0; m < 8; m++) {
		reverse_field_indir(m, i, j);
	}
	return;
}

// reverse field in direction of (k, l) from (i, j)
void reverse_field_indir(int m, int i, int j) {
	int k, l;
	if (m == 0 || m == 1 || m == 7) k = -1;
	else if (m == 2 || m == 6) k = 0;
	else k = 1;
	if (m == 1 || m == 2 || m == 3) l = -1;
	else if (m == 0 || m == 5) l = 0;
	else l = 1;

	int reverse_num = search_reversable_num_indir(m, i, j);
	for (int n = 1; n <= reverse_num; n++) {
		field[i + k * n][j + l * n] = field[i + k * n][j + l * n] ^ 1;
	}
	piece_num[turn] += reverse_num;
	piece_num[turn^1] -= reverse_num;
	return;
}
