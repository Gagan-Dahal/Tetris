#include "raylib.h"
#include "grid.hpp"
#include <iostream>


board::board(int screenWidth, int screenHeight){

    curBlockX = 0;
    curBlockY = 0;

    cellWidth = screenWidth / NUM_COLS;
    cellHeight = screenHeight / NUM_ROWS;
}
        

void board::checkCell(int row, int column){
    if(grid[row][column] == 1 || grid[row][column] == 2){
        int drawX = column * cellWidth;
        int  drawY = row * cellHeight;
        Color cellColor;
        cellColor = BLUE;
        DrawRectangle(drawX, drawY, cellWidth, cellHeight, cellColor);
    }
}
void board::drawGrid(){
    int currentX = 0;
    int currentY = 0;
    for (int i = 0; i<NUM_ROWS; i++){
        for (int j = 0; j<NUM_COLS; j++){
            DrawRectangleLines(currentX, currentY, cellWidth, cellHeight, WHITE);
            checkCell(i, j);
            currentX += cellWidth;
        }
        currentX = 0;
        currentY += cellHeight;
    }
}
// 0 for game over, 1 for valid position, 2 for invalid position but still in game, 3 to fix
int board::canPlace(block& tetro, int pieceX, int pieceY, bool toTest){
    int k;
    int l;
    int coloff;
    std::array<std::array<int, 5>, 5> piece;

    if(pieceX == -100 and pieceY == -100){
        pieceX = tetro.getX();
        pieceY = tetro.getY();
    }
    if(!toTest){
        piece = tetro.shape();
    }
    else{
        piece = tetro.testShape();
    }

    if(pieceY<0) {
        k = -pieceY;
        visRows = pieceY + 5;
        pieceY = 0;
    }
    else {
        visRows = 5;
        k = 0;
    }

    if(pieceX<-4 || pieceX >= NUM_COLS) return 2;
    
    if(pieceX<0){
        for(int i = 0; i<5;i++){
            for(int j = 0; j<-pieceX; j++){
                if(piece[i][j] == 1) return 2;
            }
        }
        coloff = -pieceX;
        visCols = pieceX + 5;
        pieceX = 0;
    }

    else{
        visCols = 5;
        coloff = 0;
    }

    
    for (int i = pieceY; i<pieceY+visRows; i++){
        l = coloff;
        for (int j = pieceX; j<pieceX+visCols; j++){
            if (piece[k][l] == 1){
                if(i<0 || j<0 || j>=NUM_COLS || i>=NUM_ROWS) return 2;
                if(grid[i][j] == 2) return 2;
            }
            l++;
        }
        k++;
    }
    return 1;
}

bool board::canFall(block& tetro){
    int pieceX = tetro.getX();
    int pieceY = tetro.getY() + 1;
    if (canPlace(tetro, pieceX, pieceY) == 1) return true;
    else return false;
}

void board::drawPiece(const block& tetro){
    int pieceX = tetro.getX();
    int pieceY = tetro.getY();
    int boardX, boardY;
    const auto& piece = tetro.shape();
        for (int i = 0; i<5; i++){
            for (int j = 0; j<5; j++){
                if(piece[i][j] == 1){ 

                    boardX = pieceX+j;
                    boardY = pieceY+i;

                    if(boardX<0 || boardX>=NUM_COLS || boardY<0 || boardY>=NUM_ROWS) continue;

                    int drawX = boardX * cellWidth;
                    int drawY = boardY * cellHeight;
                    DrawRectangle(drawX, drawY, cellWidth, cellHeight, RED);
                    DrawRectangleLines(drawX, drawY, cellWidth, cellHeight, WHITE);
                }
            }
        }
}

void board::placePerm(const block& tetro){
    int pieceX = tetro.getX();
    int pieceY = tetro.getY();
    int boardX, boardY;
    std::array<std::array<int, 5>, 5> piece = tetro.shape();
        for (int i = 0; i<5; i++){
            for (int j = 0; j<5; j++){
                if(piece[i][j] == 1){
                    boardX = pieceX +j;
                    boardY = pieceY + i;

                    if(boardX<0 || boardX>=NUM_COLS || boardY<0 || boardY>=NUM_ROWS) continue;

                    grid[boardY][boardX] = 2;
                }
            }
        }
}


void board::trackKeys(block& tetro){
    int pressed_key = GetKeyPressed();
    if (pressed_key == KEY_LEFT) {
        int pieceX = tetro.getX();
        int pieceY = tetro.getY();

        pieceX--;
        if(canPlace(tetro, pieceX, pieceY) == 1) {
            tetro.move(-1);
        }
    }
    else if(pressed_key == KEY_RIGHT){
        int pieceX = tetro.getX();
        int pieceY = tetro.getY();
        pieceX++;
        if(canPlace(tetro, pieceX, pieceY) == 1) tetro.move(1);
    }
    else if (pressed_key == KEY_DOWN || pressed_key == KEY_UP){
        std::array<std::array<int, 5>, 5> testBlock;
        tetro.checkRotate();
        testBlock = tetro.testShape();
        if(canPlace(tetro, -100, -100, true) == 1){
            tetro.swapRotatedBlock();
        }
    }
}


void board::checkLine(){
    int writerow = NUM_ROWS - 1;
    bool full;

    for (int readrow = NUM_ROWS - 1; readrow>=0; readrow--){
        full = true;
        for (int a: grid[readrow]){
            if (a == 0){
                full = false;
                break;
            }
        }
        if (!full){
            grid[writerow] = grid[readrow];
            writerow--;
        }
    }

    for (int i = writerow; i>=0; i--){
        grid[i] = {};
    }
}
