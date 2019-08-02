#include <iostream>
#include <random>
#include "main.hpp"
using namespace std;


// field initialization
void field_initialize() {
	for (int i = 0; i < 8; i++) 
		for (int j = 0; j < 8; j++) field[i][j] = -1;

	field[3][3] = 1;
	field[3][4] = 0;
	field[4][3] = 0;
	field[4][4] = 1;

	remain_field = 60;
	piece_num[0]= 2;
	piece_num[1] = 2;

	random_device rnd;
	mt19937 mt(rnd());
	turn = mt() % 2;
	return;
}

// config initialization
void config_initialize() {
	while(1) {
		int input = 0;
		cout << "CPU1 vs CPU2 : 0" << endl;
		cout << "CPU1 vs MAN2 : 1" << endl;
		cout << "MAN1 vs MAN2 : 2" << endl;
		cin >> input;
		if (input == 0) {
			player[0] = player[1] = 0;
			break;
		} else if (input == 1) {
			player[0] = 0;
			player[1] = 1;
			break;
		} else if (input == 2) {
			player[0] = player[1] = 1;
			break;
		}
		cout << "invalid input" << endl << endl;;
	}
	cin.get(); // read Enter (TODO: how to ignore Enter...?)
	return;
}

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

// draw field
void draw_field() {
	cout << "--------------------------------------\n";
	if (player[0] == 0) cout << "CPU1 :◯  " << piece_num[0] << "     ";
	else cout << "MAN1 :◯ " << piece_num[0] << " ";
	if (player[1] == 0) cout << "CPU2 :●  " << piece_num[1];
	else cout << "MAN2 :● " << piece_num[1];
	
	cout << "    remain: " << remain_field << endl;

	if (remain_field != 0) {
		if (turn == 0) cout << "Now: 1's turn" << endl;
		else cout << "Now: 2's turn" << endl;
	} else {
		if (piece_num[0] > piece_num[1]) {
			cout << "Player 1 win!" << endl;
		} else if (piece_num[0] == piece_num[1]) {
			cout << "Draw!" << endl;
		} else {
			cout << "Player 2 win!" << endl;
		}
	}
	
	cout << endl;
	cout << "  |0 |1 |2 |3 |4 |5 |6 |7 |" << endl;
	for (int i = 0; i < 8; i++) {
		cout << " " << i << "|";
		for (int j = 0; j < 8; j++) {
			if (field[i][j] == 0) cout << "○ |";
			else if (field[i][j] == 1) cout << "● |";
			else cout << "  |";
		}
		cout << endl;
	}
	cout << endl;
	return;
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

void MAN_move() {
	int puttable_flag = 0;
	int puttable[8][8] = {};
	for (int k = 0; k < 8; k++) {
		for (int l = 0; l < 8; l++) {
			if (field[k][l] != -1) continue;
			for (int m = 0; m < 8; m++) {
				if (search_reversable_num_indir(m, k, l) > 0) {
					puttable[k][l] = 1;
					puttable_flag = 1;
					break;
				}
			}
		}
	}

	if (puttable_flag == 0) return;

	int i, j;
	cout << "Enter where to put (height width)" << endl;
	while (1) {
		cin >> i >> j;
		if (i >= 0 && i <= 7 && j >= 0 && j <= 7) {
			if (puttable[i][j] == 1) {
				field[i][j] = turn;
				reverse_field(i, j);
				piece_num[turn]++;
				remain_field--;
				cin.get(); // read Enter
				return;
			}
		}
		cout << "Invalid input. Enter where to put (height width)" << endl;
	}
	return;
}
	
int main() {

	field_initialize();
	config_initialize();

	while (remain_field != 0) {
		draw_field();

		if (player[turn] == 0) {
			CPU_move();
		} else {
			MAN_move();
		}
		turn = turn ^ 1;
	}
	cout << "--------------------------------------\n";
	cout << "result" << endl;
	draw_field();
	return 0;
}
