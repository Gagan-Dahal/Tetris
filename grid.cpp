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
        if(grid[row][column] == 1 ) cellColor = RED;
        else cellColor = BLUE;
        DrawRectangle(drawX, drawY, cellWidth, cellHeight, cellColor);
    }
}
void board::drawGrid(){
    int currentX = 0;
    int currentY = 0;
    for (int i = 0; i<NUM_ROWS; i++){
        for (int j = 0; j<NUM_COLS; j++){
            DrawRectangleLines(currentX, currentY, cellWidth, cellHeight, BLACK);
            checkCell(i, j);
            currentX += cellWidth;
        }
        currentX = 0;
        currentY += cellHeight;
    }
}
// 0 for game over, 1 for valid position, 2 for invalid position but still in game, 3 to fix
int board::canPlace(const block& tetro, int pieceX, int pieceY){
    int k;
    int l;

    if(pieceX == -100 and pieceY == -100){
        pieceX = tetro.getX();
        pieceY = tetro.getY();
    }

    std::array<std::array<int, 5>, 5> piece = tetro.shape();
    if(pieceY<0) {
        k = -pieceY;
        visRows = pieceY + 5;
        pieceY = 0;
    }
    else {
        visRows = 5;
        k = 0;
    }
    if(pieceX<0){
        l = -pieceX;
        visCols = pieceX + 5;
        pieceX = 0;
    }
    else{
        visCols = 5;
        l = 0;
    }

    if(pieceX<-4 || pieceX >= NUM_COLS) return 2;
    if(pieceX<0){
        for(int i = 0; i<5;i++){
            for(int j = 0; j<=-pieceX; j++){
                if(piece[i][j] == 1) return 2;
            }
        }
    }
    
    for (int i = pieceY; i<pieceY+visRows; i++){
        for (int j = pieceX; j<pieceX+visCols; j++){
            if (piece[k][l] == 1){
                if(j>=NUM_COLS || i>=NUM_ROWS) return 2;
                if(grid[i][j] == 2){
                    if (visRows<5) return 0;
                    else return 2;
                }
            }
            l++;
        }
        l = 0;
        k++;
    }
    return 1;
}

bool board::canFall(const block& tetro){
    int pieceX = tetro.getX();
    int pieceY = tetro.getY() + 1;
    if (canPlace(tetro, pieceX, pieceY) == 1) return true;
    else return false;
}

void board::drawPiece(const block& tetro){
    int pieceX = tetro.getX();
    int pieceY = tetro.getY();
    const auto& piece = tetro.shape();
        for (int i = 0; i<5; i++){
            for (int j = 0; j<5; j++){
                if(piece[i][j] == 1){ 
                    int drawX = (pieceX + j) * cellWidth;
                    int drawY = (pieceY + i) * cellHeight;
                    DrawRectangle(drawX, drawY, cellWidth, cellHeight, RED);
                    DrawRectangleLines(drawX, drawY, cellWidth, cellHeight, BLACK);
                }
            }
        }
}

void board::placePerm(const block& tetro){
    int pieceX = tetro.getX();
    int pieceY = tetro.getY();
    std::array<std::array<int, 5>, 5> piece = tetro.shape();
        for (int i = 0; i<5; i++){
            for (int j = 0; j<5; j++){
                if(piece[i][j] == 1){
                    grid[pieceY+i][pieceX+j] = 2;
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
}

void board::deleteLine(int row_num){
    for (int i = 0; i < NUM_COLS; i++){
        grid[row_num][i] = 0;
    }
}

void board::checkLine(){
    for (int i = NUM_ROWS - 1; i>=0; i--){
        for (int j = NUM_COLS - 1; j>=0; j--){
            if (grid[i][j] != 2){
                break;
            }
            if (j == 0) deleteLine(i);
        }
    }
}