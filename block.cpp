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


block::block(const int defaultX): gen(std::random_device{}()),dist(0, 6){
    this->defaultX = defaultX;
    x = defaultX;
    y = -4;
    nextPieceNum = std::nullopt;
}

void block::checkRotate(){
    testPiece = piece;
    for (int i = 0; i<5; i++){
        for (int j = i+1; j<5; j++){
            std::swap(testPiece[i][j], testPiece[j][i]);
        }
    }

    for(std::array<int, 5>& row : testPiece){
        std::reverse(row.begin(), row.end());
    }
    
}

void block::swapRotatedBlock(){
    piece = testPiece;
}

void block::selectPiece(){
    // to select a number from 0 to 6 randomly
    int selectedPieceNo;
    if(!nextPieceNum.has_value()){
        selectedPieceNo = dist(gen);
    }
    else{
        selectedPieceNo  = *nextPieceNum;
    }
    nextPieceNum = dist(gen);
    // std::cout<<"Random number generated successfully as "<<selectedPieceNo<<std::endl;
    piece = TETROMINO[selectedPieceNo];
    // std::cout<<piece<<std::endl;
    x = defaultX;
    y = -4;
}

const std::array<std::array<int, 5>, 5>& block::shape() const{
    return piece;
}
const std::array<std::array<int, 5>, 5>& block::testShape() const{
    return testPiece;
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

const std::array<std::array<int, 5>, 5>& block:: nextPiece()const{
    return TETROMINO[*nextPieceNum];
}

void block::reset(){
    nextPieceNum = std::nullopt;
}
