#include "main.hpp"

// get score of (i, j)
int get_score(int eval, int i, int j) {
	int score = 0;
	// (-1,0), (-1,-1), (0,-1),...
	for (int m = 0; m < 8; m++) {
		score += search_reversable_num_indir(m, i, j);
	}

	// no reversable piece
	if (score == 0) return -1000;
	else return eval + 10 * score;
}

// decide the move of CPU
void CPU_move() {
	cout << "Pless Enter...";
	cin.get();

	int maxscore = -1000;
	int maxi = 0;
	int maxj = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (field[i][j] != -1) continue;
			int score = 0;
			if (turn == 0) {
				score = get_score(eval_board1[i][j], i, j);
			} else {
				score = get_score(eval_board2[i][j], i, j);
			}
			if (score > maxscore) {
				maxscore = score;
				maxi = i;
				maxj = j;
			}
		}
	}
	// maxscore == -1000 means there's no suitable place to put
	if (maxscore != -1000) {
		field[maxi][maxj] = turn;
		reverse_field(maxi, maxj);
		piece_num[turn]++;
		remain_field--;
	}
}
