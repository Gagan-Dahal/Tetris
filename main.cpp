#include "grid.hpp"
#include "block.hpp"

#include <iostream>
#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 900

int main(){
    board grid(SCREEN_WIDTH, SCREEN_HEIGHT);
    int defaultX = NUM_COLS / 2 - 3;
    block piece(defaultX);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TETRIS take 1");
    int count = 0;
    int status;
    piece.selectPiece();
    // std::cout<<grid.canPlace(piece)<<std::endl;

    // std::cout<<piece.getX()<<"\t"<<piece.getY()<<std::endl;
    while (!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);
        status = grid.canPlace(piece);
        if(count >= 25){
            if (grid.canFall(piece)) piece.fallDown();
            
            else{
                grid.placePerm(piece);
                piece.selectPiece();

                if (grid.canPlace(piece) == 0){
                    break;
                }
            }
            count = 0;
            }
        count++;
        grid.drawPiece(piece);
       
        // else if(status == 0){
        //     EndDrawing();
        //     break;
        // }
        grid.drawGrid();
        EndDrawing();
    }
    CloseWindow();
}