#include"Pawn.h"
#include<vector>
#include<string>
#include<iostream>

bool Pawn::movePiece(std::string to) {
    std::vector<std::string> possibleSquares = getAreasOfInfluence();
    for (std::string square : possibleSquares) {
        if (square.compare(to) == 0) {
            return true;
        }
    }
    return false;
}
std::vector<std::string> Pawn::getAreasOfInfluence() {
    std::vector<std::string> squares;
    
    //Initialize piece variables
    std::string currentPosition = getPosition();
    bool white = !getColor();
    int x = currentPosition.at(1) - '0';
    int y = currentPosition.at(0) - '0';
    
    //Possible pieces the pawn can promote to
    char promotionPieces[4] = {'q', 'b', 'n', 'r'};
    char promotionPiecesBlack[4] = {'Q', 'B', 'N', 'R'};

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

        //If next move leads to a pawn promotion
        if (squares[0].at(0) - '0' == 0) {
            std::vector<std::string> promotionMoves;
            //Has to be directly set because the size will change
            int limit = squares.size();
            for (int i = 0; i < limit; i++) {
                //Duplicate each square 4 times for each square in squares
                //This is done because there are 4 possible promotions
                for (int j = 0; j < 4; j++) {
                    promotionMoves.push_back(squares[i]);
                }
            }
            squares.clear();
            for (int i = 0; i < promotionMoves.size(); i++) {
                //Adds the promotion piece to the move (06q, 06b, etc.)
                promotionMoves[i] += promotionPieces[i % 4];    
                squares.push_back(promotionMoves[i]);
            }
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
        //Copy of pawn promotion but for black pieces
        if (squares[0].at(0) - '0' == 7) {
            std::vector<std::string> promotionMoves;
            int limit = squares.size();
            for (int i = 0; i < limit; i++) {
                for (int j = 0; j < 4; j++) {
                    promotionMoves.push_back(squares[i]);
                }
            }
            squares.clear();
            for (int i = 0; i < promotionMoves.size(); i++) {
                promotionMoves[i] += promotionPiecesBlack[i % 4];    
                squares.push_back(promotionMoves[i]);
            }
        }
    }
    return squares;
}