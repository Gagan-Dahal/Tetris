#include "block.hpp"

#include <iostream>
#include <ostream>
#include <algorithm>
#include "raylib.h"

const std::array<std::array<std::array<int, 5>, 5>, 7> TETROMINO = {{
    {{
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0}
    }},

    {{
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0}
    }},

    {{
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0}
    }},

    {{
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0}
    }},

    {{
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0}
    }},

    {{
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0}
    }},

    {{
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0}
    }}
}};

std::ostream& operator<<(std::ostream& os,
    const std::array<std::array<int,5>,5>& a)
{
    for (const auto& row : a) {
        for (int v : row)
            os << v << ' ';
        os << '\n';
    }
    return os;
}


block::block(const int defaultX) {
    this->defaultX = defaultX;
    x = defaultX;
    y = -4;
}

void block::rotate(std::array<std::array<int, 5>, 5>& curPiece){
    for (int i = 0; i<5; i++){
        for (int j = i+1; j<5; j++){
            std::swap(curPiece[i][j], curPiece[j][i]);
        }
    }

    for(std::array<int, 5>& row : curPiece){
        std::reverse(row.begin(), row.end());
    }
}

void block::selectPiece(){
    // to select a number from 0 to 6 randomly
    int selectedPieceNo = 0;
    piece = TETROMINO[selectedPieceNo];
    // std::cout<<piece<<std::endl;
    x = defaultX;
    y = -4;
}

const std::array<std::array<int, 5>, 5>& block::shape() const{
    return piece;
}

void block::fallDown(){
    y+=1;
}
    
void block::move(int dx){
    x+=dx;
}

int block::getX() const{
    return x;
}

int block::getY() const{
    return y;
}



