#pragma once

#include "settings.h"

typedef struct {
	int bomb;
	int flag;
	int opened;
	int surround;
	int checking;
}block;

int checkBlock(block block_state[ROW][COLUMN], int* remain);
int checkBomb(block block_state[ROW][COLUMN], int row, int column, int* re_check);