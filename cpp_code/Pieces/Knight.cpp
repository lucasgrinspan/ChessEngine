#include"Knight.h"
#include<vector>
#include<iostream>

bool Knight::movePiece(std::string to) {
    std::vector<std::string> possibleSquares = getAreasOfInfluence();
    for (std::string square : possibleSquares) {
        if (square.compare(to) == 0) {
            return true;
        }
    }
    return false;
}
bool withinBounds(int x, int y) {
    return (((x >= 0) && (x <= 7)) && ((y >= 0) && (y <= 7)));
}
std::vector<std::string> Knight::getAreasOfInfluence() {
    std::vector<std::string> squares;
    
    std::string currentPosition = getPosition();

    int x = currentPosition.at(1) - '0';
    int y = currentPosition.at(0) - '0';
    if (withinBounds(x - 1, y - 2)) 
        squares.push_back(toStrCoord(x - 1, y - 2));
    if (withinBounds(x - 1, y + 2)) 
        squares.push_back(toStrCoord(x - 1, y + 2));   
    if (withinBounds(x - 2, y - 1)) 
        squares.push_back(toStrCoord(x - 2, y - 1));
    if (withinBounds(x - 2, y + 1))
        squares.push_back(toStrCoord(x - 2, y + 1));
    if (withinBounds(x + 1, y - 2))
        squares.push_back(toStrCoord(x + 1, y - 2));
    if (withinBounds(x + 2, y - 1))
        squares.push_back(toStrCoord(x + 2, y - 1));
    if (withinBounds(x + 2, y + 1))
        squares.push_back(toStrCoord(x + 2, y + 1));
    if (withinBounds(x + 1, y + 2))
        squares.push_back(toStrCoord(x + 1, y + 2));
    
    for (int i = 0; i < squares.size(); i++) {
        std::cout << squares[i] << std::endl;
    }
    return squares;
}