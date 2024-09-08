#pragma once

#include "settings.h"
#include "block.h"
#include "DxLib.h"
#include "WinUser.h"

void drawBlock(block block_state[ROW][COLUMN]);
int drawResult(int flag_bomb);
void drawBomb(int x, int y, int num);
void drawNumber(int x, int y, int num);
void drawFlag(int x, int y);