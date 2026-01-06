#include "grid.hpp"
#include "block.hpp"

#include <iostream>
#include "raylib.h"
#include <chrono>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

using steadyClock = std::chrono::steady_clock;

typedef enum {CONTINUE_GAMEPLAY, PAUSE_GAMEPLAY, GAME_OVER, EXIT_GAMEPLAY} gameState;

int main(){
    gameState currentState = CONTINUE_GAMEPLAY;

    const auto fallInterval = std::chrono::milliseconds(50);

    steadyClock::time_point lastFall = steadyClock::now();
    steadyClock::time_point currentTime;

    board grid(SCREEN_WIDTH, SCREEN_HEIGHT);
    int defaultX = NUM_COLS / 2 - 3;
    block piece(defaultX);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TETRIS take 1");

    piece.selectPiece();
    // std::cout<<grid.canPlace(piece)<<std::endl;

    // std::cout<<piece.getX()<<"\t"<<piece.getY()<<std::endl;
    while (!WindowShouldClose()){
        currentTime = steadyClock::now();
        
        BeginDrawing();
        ClearBackground(BLACK);
        grid.drawGrid();
        grid.checkLine();
        grid.drawScore(piece);

        if(IsKeyPressed(KEY_P)){
            if(currentState == CONTINUE_GAMEPLAY) currentState = PAUSE_GAMEPLAY;
            else currentState = CONTINUE_GAMEPLAY;
        }
        
        if(grid.isGameOver(piece)){
            currentState = GAME_OVER;
        }
        
        if(currentState == CONTINUE_GAMEPLAY){
            grid.trackKeys(piece);
            if(currentTime - lastFall >= fallInterval){
                if (grid.canFall(piece)) piece.fallDown();
                
                else{
                    grid.placePerm(piece);
                    piece.selectPiece();

                    if (grid.canPlace(piece) == 0){
                        break;
                    }
                }
                lastFall = steadyClock::now();
                }
            
                grid.drawPiece(piece);
            }
        else if(currentState == PAUSE_GAMEPLAY){
            grid.drawPiece(piece);
            grid.drawScore(piece, 1);
            if(IsKeyPressed(KEY_ENTER)){
                grid.resetBoard();
                piece.reset();
                piece.selectPiece();
                currentState = CONTINUE_GAMEPLAY;
                continue;
            }
            else if(IsKeyPressed(KEY_Q)){
                EndDrawing();
                break;
            }
        }
        else if(currentState == GAME_OVER) {
            grid.drawPiece(piece);
            grid.drawScore(piece, 2);
            if(IsKeyPressed(KEY_ENTER)){
                grid.resetBoard();
                piece.reset();
                piece.selectPiece();
                currentState = CONTINUE_GAMEPLAY;
                continue;
            }
            else if(IsKeyPressed(KEY_Q)){
                EndDrawing();
                break;
            }
        }
        EndDrawing();
    }
    CloseWindow();
}