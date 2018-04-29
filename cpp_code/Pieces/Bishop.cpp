#include"Bishop.h"
#include<vector>

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
    return squares;
}