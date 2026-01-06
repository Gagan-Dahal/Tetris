#pragma once
#include <array>
#include "block.hpp"



inline constexpr int NUM_ROWS = 25;
inline constexpr int NUM_COLS = 20;
inline constexpr int LINE_SUM = NUM_COLS*2;

class board{
    private:
        int screenWidthText;
        int screenWidthGrid;
        int screenHeight;
        int cellHeight;
        int cellWidth;
        std::array<std::array<int, NUM_COLS>, NUM_ROWS> grid = {};
        int curBlockX;
        int curBlockY;
        int visRows;
        int visCols;
        int score;
    public:
        board(int, int);

        void checkCell(int, int);
        void drawGrid();
        int canPlace(block& tetro, int pieceX = -100, int pieceY = -100, bool toTest = false);
        bool canFall(block& tetro);
        void drawPiece(const block& tetro);
        void placePerm(const block& tetro);
        void trackKeys(block& tetro);
        void checkLine(void);
        void deleteLine(const int& rowNum);
        void collapseRowWise(const int& rowNUm);
        bool isGameOver(block& tetro);
        void drawScore(block& tetro, int gameStatus = 0);
        void resetBoard();
};
