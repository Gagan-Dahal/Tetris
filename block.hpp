#pragma once
#include <array>


class block{
    private:
        std::array<std::array<int, 5>, 5> piece;
        int x, y;
        int defaultX;
    public:
        block(const int);
        void rotate(std::array<std::array<int, 5>, 5>&);
        void selectPiece();
        void fallDown();
        int getX() const;
        int getY() const;
        const std::array<std::array<int, 5>, 5>& shape() const;  
        void move(int dx);
};