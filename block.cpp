#include "block.h"

int checkBlock(block block_state[ROW][COLUMN], int* remain) {
    int bomb = 0;
    int re_check = 0;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			if (block_state[i][j].checking == 1) {
                if (checkBomb(block_state, i, j, &re_check) == -1) { return -1; }
                *remain -= 1;
                block_state[i][j].checking += 1;
			}
		}
	}
    if (re_check == 1) {
        checkBlock(block_state, remain);
    }
    return 0;
}

int checkBomb(block block_state[ROW][COLUMN], int row, int column, int* re_check) {
    if (block_state[row][column].bomb == 1) {
        block_state[row][column].opened = 1;
        return -1;
    }
    else {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (row + i >= 0 && row + i < ROW && column + j >= 0 && column + j < COLUMN) {
                    if (block_state[row + i][column + j].bomb == 1) {
                        block_state[row][column].surround += 1;
                    }
                }
            }
        }
    }
    if (block_state[row][column].surround == 0) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (row + i >= 0 && row + i < ROW && column + j >= 0 && column + j < COLUMN) {
                    if (block_state[row + i][column + j].checking == 0) {
                        block_state[row + i][column + j].checking = 1;
                    }
                }
            }
        }
        *re_check = 1;
    }
    block_state[row][column].checking = 2;
    block_state[row][column].opened = 1;
    return 0;
}