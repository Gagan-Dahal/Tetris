#pragma once
#include <array>
#include <random>
#include <optional>


class block{
    private:
        std::array<std::array<int, 5>, 5> piece;
        std::array<std::array<int, 5>, 5> testPiece;
        int x, y;
        int defaultX;
        std::mt19937 gen;
        std::uniform_int_distribution<int> dist;
        std::optional<int> nextPieceNum;
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
        const std::array<std::array<int, 5>, 5>& nextPiece() const; 
        void move(int dx);
        void reset();
};