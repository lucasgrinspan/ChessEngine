#include"Rook.h"
#include<vector>
#include<string>
#include<iostream>

bool Rook::movePiece(std::string to) {
    std::vector<std::string> possibleSquares = getAreasOfInfluence();
    for (std::string square : possibleSquares) {
        if (square.compare(to) == 0) {
            return true;
        }
    }
    return false;
}
std::vector<std::string> Rook::getAreasOfInfluence() {
    std::vector<std::string> squares;
    
    std::string currentPosition = getPosition();

    int x = currentPosition.at(1) - '0';
    int y = currentPosition.at(0) - '0';

    //Add squares over and under
    for (int i = 0; i < 8; i++) {
        if (i != x) {
            squares.push_back(toStrCoord(i, y));
        }
    }
    //Add squares to the left and right
    for (int i = 0; i < 8; i++) {
        if (i != y) {
            squares.push_back(toStrCoord(x, i));
        }
    }
    //TODO: add support for castling
    return squares;
}