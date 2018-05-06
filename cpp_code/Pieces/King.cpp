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
    bool whiteKingMoved = movedPiecesBool[0];
    bool blackKingMoved = movedPiecesBool[1];
    bool rookA1Moved = movedPiecesBool[2];
    bool rookA8Moved = movedPiecesBool[3];
    bool rookH1Moved = movedPiecesBool[4];
    bool rookH8Moved = movedPiecesBool[5];

    
    std::vector<std::string> squares;
    std::string currentPosition = getPosition();

    int x = currentPosition.at(1) - '0';
    int y = currentPosition.at(0) - '0';

    if (!getColor()) {
        if (!whiteKingMoved) {
            if (!rookA1Moved) {
                squares.push_back(toStrCoord(x - 2, y));
            }
            if (!rookA8Moved) {
                squares.push_back(toStrCoord(x + 2, y));
            }
        }
    } else {
        if (!blackKingMoved) {
            if (!rookH1Moved) {
                squares.push_back(toStrCoord(x - 2, y));
            }
            if (!rookH8Moved) {
                squares.push_back(toStrCoord(x + 2, y));
            }
        }
    }

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (withinBounds(x + i, y + j)) {
                if (i != 0 || j != 0) {
                squares.push_back(toStrCoord(x + i, y + j));
                }
            }
        }
    }
    return squares;
}