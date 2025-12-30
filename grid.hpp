#pragma once
#include <array>
#include "block.hpp"



inline constexpr int NUM_ROWS = 40;
inline constexpr int NUM_COLS = 20;

class board{
    private:
        int cellHeight;
        int cellWidth;
        int grid[NUM_ROWS][NUM_COLS] = {0};
        int curBlockX;
        int curBlockY;
        int visRows;
        int visCols;
    public:
        board(int, int);

        void checkCell(int, int);
        void drawGrid();
        int canPlace(const block& tetro, int pieceX = -100, int pieceY = -100);
        bool canFall(const block& tetro);
        void drawPiece(const block& tetro);
        void placePerm(const block& tetro);
        void trackKeys(block& tetro);
        void checkLine(void);
        void deleteLine(int rowNum);
};
