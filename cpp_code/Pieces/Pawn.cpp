#include"Pawn.h"
#include<vector>

bool Pawn::movePiece(std::string to) {
    return true;
}
std::vector<std::string> Pawn::getAreasOfInfluence() {
    std::vector<std::string> squares;
    
    //Initialize piece variables
    std::string currentPosition = getPosition();
    bool white = getColor();
    bool inStartingPosition = false;
    int x = currentPosition[1];
    int y = currentPosition[0];

    //If white piece
    if (white) {
        //Determine if pawn is currently in starting position
        if (y == 6) {
            //Add tile two spaces in front
            squares.push_back(toStrCoord(x, y - 2));
        }
        
        //Add square directly in front
        squares.push_back(toStrCoord(x, y - 1));

        //Add diagonal squares
        if (x == 0) {
            //In left column
            squares.push_back(toStrCoord(x + 1, y - 1));
        } else if (x == 7) {
            //In right column
            squares.push_back(toStrCoord(x - 1, y - 1));
        } else {
            squares.push_back(toStrCoord(x + 1, y - 1));
            squares.push_back(toStrCoord(x - 1, y - 1));
        }
    } 
    //If black piece
    else {
        //Determine if pawn is currently in starting position
        if (y == 1) {
            //Add tile two spaces under
            squares.push_back(toStrCoord(x, y + 2));
        }
        
        //Add square directly under
        squares.push_back(toStrCoord(x, y + 1));

        //Add diagonal squares
        if (x == 0) {
            //In left column
            squares.push_back(toStrCoord(x + 1, y + 1));
        } else if (x == 7) {
            //In right column
            squares.push_back(toStrCoord(x - 1, y + 1));
        } else {
            squares.push_back(toStrCoord(x + 1, y + 1));
            squares.push_back(toStrCoord(x - 1, y + 1));
        }
    }
    return squares;
}