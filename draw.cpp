#include "draw.h"

void drawBlock(block block_state[ROW][COLUMN]) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			if (block_state[i][j].opened >= 1) {
				if (block_state[i][j].bomb == 1) {
						drawBomb(i * BLOCK_WIDTH, j * BLOCK_HEIGHT, block_state[i][j].opened);
				}
				else if(block_state[i][j].surround != 0) {
					drawNumber(i * BLOCK_WIDTH, j * BLOCK_HEIGHT, block_state[i][j].surround);
				}
				else {
					DrawBox(i * BLOCK_WIDTH + 1, j * BLOCK_HEIGHT + 1, i * BLOCK_WIDTH + BLOCK_WIDTH - 1, j * BLOCK_HEIGHT + BLOCK_HEIGHT - 1, WHITE, TRUE);
				}
			} 
			else if(block_state[i][j].flag == 1) {
				drawFlag(i * BLOCK_WIDTH, j * BLOCK_HEIGHT);
			} 
			else {
				DrawBox(i * BLOCK_WIDTH + 1, j * BLOCK_HEIGHT + 1, i * BLOCK_WIDTH + BLOCK_WIDTH - 1, j * BLOCK_HEIGHT + BLOCK_HEIGHT - 1, GRAY, TRUE);
			}
		}
	}
	return;
}

int drawResult(int flag_bomb) {
	int id = 0;

	switch (flag_bomb) {
	case 0:
		id = MessageBox(NULL, "リスタートしますか?", "Game Clear!!", MB_YESNO | MB_ICONQUESTION);
		break;

	case 1:
		id = MessageBox(NULL, "リスタートしますか?", "Game Over", MB_YESNO | MB_ICONQUESTION);
		break;
	}

	switch (id) {
	case IDYES:
		return 0;
		break;
	case IDNO:
		return -1;
	}
}

//Xの形を描画
void drawBomb(int x, int y, int num) {
	if (num == 1) {
		DrawBox(x + 1, y + 1, x + BLOCK_WIDTH - 1, y + BLOCK_HEIGHT - 1, WHITE, TRUE);
	}else{
		DrawBox(x + 1, y + 1, x + BLOCK_WIDTH - 1, y + BLOCK_HEIGHT - 1, BLACK, TRUE);
	}
	DrawTriangle(x + 11, y + 1, x + 1, y + 11, x + BLOCK_WIDTH - 1, y + BLOCK_HEIGHT - 11, RED, TRUE);
	DrawTriangle(x + BLOCK_WIDTH - 11, y + BLOCK_HEIGHT - 1, x + 1, y + 11, x + BLOCK_WIDTH - 1, y + BLOCK_HEIGHT - 11, RED, TRUE);

	DrawTriangle(x + 1, y + BLOCK_HEIGHT - 11, x + 11, y + BLOCK_HEIGHT - 1, x + BLOCK_WIDTH - 11, y + 1, RED, TRUE);
	DrawTriangle(x + BLOCK_WIDTH - 1, y + 11, x + 11, y + BLOCK_HEIGHT - 1, x + BLOCK_WIDTH - 11, y + 1, RED, TRUE);

	return;
}

void drawNumber(int x, int y, int num) {
	DrawBox(x + 1, y + 1, x + BLOCK_WIDTH - 1, y + BLOCK_HEIGHT - 1, WHITE, TRUE);

	SetFontSize((BLOCK_WIDTH + BLOCK_HEIGHT) / 4);

	switch (num) {
	case 1:
		DrawFormatString(x + BLOCK_WIDTH / 4, y + BLOCK_HEIGHT / 4, BLUE, "%d", num);
		break;

	case 2:
		DrawFormatString(x + BLOCK_WIDTH / 4, y + BLOCK_HEIGHT / 4, GREEN, "%d", num);
		break;

	case 3:
		DrawFormatString(x + BLOCK_WIDTH / 4, y + BLOCK_HEIGHT / 4, RED, "%d", num);
		break;

	default:
		DrawFormatString(x + BLOCK_WIDTH / 4, y + BLOCK_HEIGHT / 4, BLACK, "%d", num);
		break;
	}

	return;
}

void drawFlag(int x, int y) {
	DrawBox(x + 1, y + 1, x + BLOCK_WIDTH - 1, y + BLOCK_HEIGHT - 1, GRAY, TRUE);

	DrawBox(x + 1 + BLOCK_WIDTH / 6, y + 1 + BLOCK_HEIGHT / 8, x + 1 + BLOCK_WIDTH / 4, y + BLOCK_HEIGHT - 1 - BLOCK_HEIGHT / 8, WHITE, TRUE);
	DrawBox(x + 1 + BLOCK_WIDTH / 4, y + 1 + BLOCK_HEIGHT / 7, x + BLOCK_WIDTH - 1 - BLOCK_WIDTH / 6, y + BLOCK_HEIGHT / 2, RED, TRUE);

	return;
}