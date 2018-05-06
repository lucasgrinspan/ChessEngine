#include"King.h"
#include<vector>
#include<iostream>

bool King::movePiece(std::string to) {
    std::vector<std::string> possibleSquares = getAreasOfInfluence();
    for (std::string square : possibleSquares) {
        if (square.compare(to) == 0) {
            return true;
        }
    }
    return false;
}
std::vector<std::string> King::getAreasOfInfluence() {
    std::vector<std::string> squares;
    std::string currentPosition = getPosition();

    int x = currentPosition.at(1) - '0';
    int y = currentPosition.at(0) - '0';

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (withinBounds(x + i, y + j)) {
                if (i != 0 || j != 0) {
                std::cout << toStrCoord(x + i, y + j) << std::endl;
                squares.push_back(toStrCoord(x + i, y + j));
                }
            }
        }
    }
    return squares;
}