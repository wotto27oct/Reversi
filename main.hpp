#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <random>
using namespace std;

extern int field[8][8];

extern int eval_board1[8][8];

extern int eval_board2[8][8];

// field info
extern int remain_field;
extern int piece_num[2];
extern int turn; // 0 or 1

// player info 
extern int player[2]; // 0:CPU 1:MAN

void field_initialize();
void config_initialize();

int get_score(int, int, int);
int search_reversable_num_indir(int, int, int);
void reverse_field(int, int);
void reverse_field_indir(int, int, int);

void draw_field();

void CPU_move();

void MAN_move();

#endif
