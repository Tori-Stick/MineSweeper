#pragma once

#include "time.h"
#include "stdlib.h"

#include "settings.h"
#include "block.h"

void generateBomb(block block_state[ROW][COLUMN], int row, int column);
int get_random(int min, int max);