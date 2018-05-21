#include"Bishop.h"
#include<vector>
#include<iostream>

bool Bishop::movePiece(std::string to) {
    std::vector<std::string> possibleSquares = getAreasOfInfluence();
    for (std::string square : possibleSquares) {
        if (square.compare(to) == 0) {
            return true;
        }
    }
    return false;
}
std::vector<std::string> Bishop::getAreasOfInfluence() {
    std::vector<std::string> squares;

    std::string currentPosition = getPosition();

    int x = currentPosition.at(1) - '0';
    int y = currentPosition.at(0) - '0';
    
    //  Calculate top left to bottom right diagonal
    //  Get coords to top left square of path
    int startx1 = x - std::min(x, y);
    int starty1 = y - std::min(x, y);

    int min = 0;
    if (startx1 > starty1) {
        min = 8 - startx1;
    } else if (starty1 > startx1) {
        min = 8 - starty1;
    } else if (startx1 == starty1) {
        min = 8 - startx1;
    }
    for (int i = 0; i < min; i++) {
        if (((startx1 + i) != x) && ((starty1 + i) != y)) {
            squares.push_back(toStrCoord(startx1 + i, starty1 + i));
        } 
    }
    //  Calculate top right to bottom left diagonal
    //  Get coords of top right
    int startx2 = x + std::min(7 - x, y);
    int starty2 = y - std::min(7 - x, y);

    int min2 = 0;
    if (startx2 + starty2 > 7) {
        min2 = 8 - starty2;
    } else if (startx2 + starty2 < 7) {
        min2 = startx2 + 1;
    } else if (startx2 + starty2 == 7) {
        min2 = startx2 + 1;
    }
    for (int i = 0; i < min2; i++) {
        if (((startx2 - i) != x) && ((starty2 + i) != y)) {
            squares.push_back(toStrCoord(startx2 - i, starty2 + i));
        } 
    }
    return squares;
}