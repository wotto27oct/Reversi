#include "main.hpp"

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

// field info
int remain_field = 0;
int piece_num[2]= {};
int turn = 0; // 0 or 1

// player info 
int player[2] = {}; // 0:CPU 1:MAN

int main() {

	field_initialize();
	config_initialize();

	while (remain_field != 0 || piece_num[0] == 0 || piece_num[1] == 0) {
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
