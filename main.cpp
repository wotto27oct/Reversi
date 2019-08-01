#include <iostream>
#include "main.hpp"
using namespace std;

int field[8][8] = {};

int eval_board1[8][8] = {
	100, -50, 20, 10, 10, 20, -50, 100,
	-50, -50, -10, -10, -10, -10, -50, -50,
	20, -10, 5, 5, 5, 5, -10, 20,
	10, -10, 5, 5, 5, 5, -10, 20,
	10, -10, 5, 5, 5, 5, -10, 20,
	20, -10, 5, 5, 5, 5, -10, 20,
	-50, -50, -10, -10, -10, -10, -50, -50,
	100, -50, 20, 10, 10, 20, -50, 100
};

int eval_board2[8][8] = {};

int get_score(int turn, int eval, int i, int j) {
	int score = 0;
	score += search_reversable_num_indir(-1, 0, i, j, turn);
	score += search_reversable_num_indir(-1, -1, i, j, turn);
	score += search_reversable_num_indir(0, -1, i, j, turn);
	score += search_reversable_num_indir(1, -1, i, j, turn);
	score += search_reversable_num_indir(1, 0, i, j, turn);
	score += search_reversable_num_indir(1, 1, i, j, turn);
	score += search_reversable_num_indir(0, 1, i, j, turn);
	score += search_reversable_num_indir(-1, 1, i, j, turn);

	// no reversable piece
	if (score == 0) return -1000;
	else return eval + 10 * score;
}

// return reversable num in the direction of (k, l) from (i, j)
int search_reversable_num_indir(int k, int l, int i, int j, int turn) {
	int n = 1;
	while (i + n * k > 0 && i + n * k < 8 && j + n * l > 0 && j + n * l < 8) {
		if (field[i + n * k][j + n * l] == 0) return 0;
		else if (field[i + n * k][j + n * l] == turn) {
			// eg) 1, -1, -1, 1 (n = 3)
			return n - 1;
		}
		n++;
	}
	return 0;
}

void reverse_field(int turn, int i, int j) {
	reverse_field_indir(-1, 0, i, j, turn);
	reverse_field_indir(-1, -1, i, j, turn);
	reverse_field_indir(0, -1, i, j, turn);
	reverse_field_indir(1, -1, i, j, turn);
	reverse_field_indir(1, 0, i, j, turn);
	reverse_field_indir(1, 1, i, j, turn);
	reverse_field_indir(0, 1, i, j, turn);
	reverse_field_indir(-1, 1, i, j, turn);
	cout << endl;
	return;
}

void reverse_field_indir(int k, int l, int i, int j, int turn) {
	int reverse_num = search_reversable_num_indir(k, l, i, j, turn);
	cout << reverse_num << " ";
	for (int n = 1; n <= reverse_num; n++) {
		field[i + k * n][j + l * n] *= -1;
	}
	return;
}
	
int main() {

	field[3][3] = 1;
	field[3][4] = -1;
	field[4][3] = -1;
	field[4][4] = 1;

	int remain_field = 60;
	int turn = 1;

	while (remain_field != 0) {
		int maxscore = -1000;
		int maxi = 0;
		int maxj = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (field[i][j] != 0) continue;
				int score = 0;
				if (turn == 1) {
					score = get_score(turn, eval_board1[i][j], i, j);
				} else {
					score = get_score(turn, eval_board2[i][j], i, j);
				}
				if (score > maxscore) {
					maxscore = score;
					maxi = i;
					maxj = j;
				}
			}
		}
		if (maxscore != -1000) {
			cout << maxscore << endl;
			field[maxi][maxj] = turn;
			reverse_field(turn, maxi, maxj);
			remain_field--;
		}
		turn *= -1;

		cout << "remain: " << remain_field << endl;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (field[i][j] == 1) cout << "○ ";
				else if (field[i][j] == -1) cout << "● ";
				else cout << "  ";
			}
			cout << endl;
		}
		cout << endl;
		getchar();
	}
	return 0;
}
