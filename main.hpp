#ifndef MAIN_HPP
#define MAIN_HPP

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

void field_initialize();
void config_initialize();

int get_score(int, int, int);
int search_reversable_num_indir(int, int, int);
void reverse_field(int, int);
void reverse_field_indir(int, int, int);

void draw_field();

void CPU_move();

#endif
