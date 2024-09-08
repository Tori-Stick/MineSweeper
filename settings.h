#pragma once

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define ROW 9
#define COLUMN 9
#define BOMB 12

#define BLOCK_WIDTH (WINDOW_WIDTH / ROW)
#define BLOCK_HEIGHT (WINDOW_HEIGHT / COLUMN)

#define BLACK GetColor(0, 0, 0)
#define GRAY GetColor(128, 128, 128)
#define WHITE GetColor(255, 255, 255)
#define RED GetColor(255, 0, 0)
#define GREEN GetColor(0, 255, 0)
#define BLUE GetColor(0, 0, 255)