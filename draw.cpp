#include "main.hpp"

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
