#include "DxLib.h"

#include "bomb.h"
#include "block.h"
#include "draw.h"
#include "settings.h"

static block block_state[ROW][COLUMN];
int flag_generate = 0;
int flag_bomb = 0;
int remain = ROW * COLUMN;

void initGame();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    SetWindowUserCloseEnableFlag(FALSE);
    
    ChangeWindowMode(TRUE); // ウィンドウモードに設定
    SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32); //ウィンドウの最大サイズの指定
    SetBackgroundColor(255, 255, 255);
    
    if (DxLib_Init() == -1) { return -1; };   // DXライブラリ初期化処理

    initGame();

    while (1) {
        ClearDrawScreen();
        SetDrawScreen(DX_SCREEN_BACK);

        drawBlock(block_state);

        ScreenFlip();

        if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
            int mouseX, mouseY;
            int row, column;

            GetMousePoint(&mouseX, &mouseY);

            row = mouseX * ROW / WINDOW_WIDTH;
            column = mouseY * COLUMN / WINDOW_HEIGHT;

            if (block_state[row][column].opened == 0 && block_state[row][column].flag == 0) {
                block_state[row][column].checking = 1;
            }

            if (flag_generate == 0) {
                generateBomb(block_state, row, column);
                flag_generate++;
            }

            if (checkBlock(block_state, &remain) == -1) { flag_bomb = 1; }
        }
        else if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
            int mouseX, mouseY;
            int row, column;

            GetMousePoint(&mouseX, &mouseY);

            row = mouseX * ROW / WINDOW_WIDTH;
            column = mouseY * COLUMN / WINDOW_HEIGHT;
            
            if (block_state[row][column].flag == 0) {
                block_state[row][column].flag = 1;
            }
            else {
                block_state[row][column].flag = 0;
            }
        }

        if (GetWindowUserCloseFlag(TRUE)) {
            int id = 0;
            
            id = MessageBox(NULL, "終了しますか?", "", MB_OKCANCEL | MB_ICONQUESTION);    

            if (id == IDOK) {
                break;
            }
            else {
                id = MessageBox(NULL, "リスタートしますか?", "", MB_YESNO | MB_ICONQUESTION);
                if (id == IDYES) {
                    initGame();
                }
            }
        }

        if ((remain <= BOMB) || (flag_bomb == 1)) {
            int restart;
            for (int i = 0; i < ROW; i++) {
                for (int j = 0; j < COLUMN; j++) {
                    if (block_state[i][j].bomb == 1) {
                        block_state[i][j].opened += 1;
                    }
                }
            }
            ClearDrawScreen();
            SetDrawScreen(DX_SCREEN_BACK);

            drawBlock(block_state);
            
            ScreenFlip();

            restart = drawResult(flag_bomb);
            if (restart == -1) { break; }
            initGame();
        }
    }

    DxLib_End();    // DXライブラリ終了処理
    return 0;
}

void initGame() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            block_state[i][j].bomb = 0;
            block_state[i][j].flag = 0;
            block_state[i][j].opened = 0;
            block_state[i][j].surround = 0;
            block_state[i][j].checking = 0;
            remain = ROW * COLUMN;
        }
    }
    flag_generate = 0;
    flag_bomb = 0;
    return;
}