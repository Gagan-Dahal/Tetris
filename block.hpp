#pragma once
#include <array>
#include <random>


class block{
    private:
        std::array<std::array<int, 5>, 5> piece;
        std::array<std::array<int, 5>, 5> testPiece;
        int x, y;
        int defaultX;
        std::mt19937 gen;
        std::uniform_int_distribution<int> dist;
    public:
        block(const int);
        void checkRotate();
        void swapRotatedBlock();
        std::array<std::array<int, 5>, 5> rotate();
        void selectPiece();
        void fallDown();
        int getX() const;
        int getY() const;
        const std::array<std::array<int, 5>, 5>& shape() const; 
        const std::array<std::array<int, 5>, 5>& testShape() const; 

        void move(int dx);
};