#include "main.hpp"

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
	
