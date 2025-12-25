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
        int drawY = row * cellHeight;
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
    int l = 0;

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

    if(pieceX<0 || pieceX >= NUM_COLS) return 2;
    
    for (int i = pieceY; i<pieceY+visRows; i++){
        for (int j = pieceX; j<pieceX+5; j++){
            if (piece[k][l] == 1 && grid[i][j] == 2 &&  visRows<5) return 0;
            else if ((piece[k][l] == 1 && i>NUM_ROWS) || (piece[k][l] == 1 && j > NUM_COLS)) return 2;
            else if ((piece[k][l] == 1 && grid[i][j] == 2) || (piece[k][l] == 1 && i==NUM_ROWS)) return 2;
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

