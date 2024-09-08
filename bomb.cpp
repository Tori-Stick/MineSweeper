#include "bomb.h"

void generateBomb(block block_state[ROW][COLUMN], int row, int column) {
	srand((unsigned int)time(NULL));

    int i = 0;
    while (i < BOMB) {
        int r = get_random(0, ROW - 1);
        int c = get_random(0, COLUMN);
        if (block_state[r][c].bomb == 0 && (row + 1 < r || row - 1 > r) && (column + 1 < c || column > c)) {
            block_state[r][c].bomb = 1;
            i++;
        }
    }
}

int get_random(int min, int max) {
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}