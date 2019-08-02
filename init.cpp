#include "main.hpp"

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
