#include<iostream>
#include<string>
#include<vector>
#include"Board.h"
#include"Piece.h"
#include"Pieces/Pawn.h"
#include"Pieces/Rook.h"
#include"Pieces/Knight.h"
#include"Pieces/Bishop.h"
#include"Pieces/Queen.h"
#include"Pieces/King.h"
#include"Pieces/Blank.h"

Board::Board(char board[8][8], bool movedPieces[6]) {
    //Read from parameter board
    for (int i = 0; i < 8; i++) {
         for (int j = 0; j < 8; j++) {
            //Copy to internal board object
            boardState[i][j] = board[i][j];

            //Initialize Piece objects
            if (board[i][j] == 'r' || board[i][j] == 'R') {
                //Create position
                std::string position = std::to_string(i) + std::to_string(j);
                //True if uppercase
                Piece* rook = new Rook(position, board[i][j] == 'R');
                currentPieces.push_back(rook);
            } else if (board[i][j] == 'b' || board[i][j] == 'B') {
                std::string position = std::to_string(i) + std::to_string(j);
                Piece* bishop = new Bishop(position, board[i][j] == 'B');
                currentPieces.push_back(bishop);
            } else if (board[i][j] == 'n' || board[i][j] == 'N') {
                std::string position = std::to_string(i) + std::to_string(j);
                Piece* knight = new Knight(position, board[i][j] == 'N');
                currentPieces.push_back(knight);
            } else if (board[i][j] == 'q' || board[i][j] == 'Q') {
                std::string position = std::to_string(i) + std::to_string(j);
                Piece* queen = new Queen(position, board[i][j] == 'Q');
                currentPieces.push_back(queen);
            } else if (board[i][j] == 'k' || board[i][j] == 'K') {
                std::string position = std::to_string(i) + std::to_string(j);
                Piece* king = new King(position, board[i][j] == 'K', movedPieces);
                currentPieces.push_back(king);
            } else if (board[i][j] == 'p' || board[i][j] == 'P') {
                std::string position = std::to_string(i) + std::to_string(j);
                Piece* pawn = new Pawn(position, board[i][j] == 'P');
                currentPieces.push_back(pawn);
            } else if (board[i][j] == ' ') {
                //std::string position = std::to_string(i) + std::to_string(j);
                //Piece* blank = new Blank(position, true);
                //currentPieces.push_back(blank);
            }
        }
    }
}
std::vector<int> Board::stringCoordtoInt(std::string square) {
    std::vector<int> intChords;
    intChords.push_back(square.at(1) - '0');
    intChords.push_back(square.at(0) - '0');
    return intChords;
}
std::vector<Piece*> Board::getCurrentPieces() {
    return currentPieces;
}
void Board::printBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << boardState[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
bool Board::validateMove(Piece* piece, std::string to) {
    bool color = piece->getColor();
    //Draw a line between the two squares
    //If the line only consists of empty spaces, then the move is valid.

    std::string position = piece->getPosition();
    int x0 = position.at(1) - '0';
    int y0 = position.at(0) - '0'; 
    int x1 = to.at(1) - '0';
    int y1 = to.at(0) - '0';

    //Get change in x and y
    int delx = x1 - x0;
    int dely = y1 - y0;

    //If requested move is along a straight horizontal line
    if (dely == 0) {
        for (int i = 1; i < std::abs(delx); i++) {
            if (boardState[y0][std::min(x0, x1) + i] != ' ') {
                std::cout << std::to_string(y0) + std::to_string(std::min(x0, x1) + i) << std::endl;
                return false;
            }
        }
    }
    //If requested move is along a straight vertical line
    else if (delx == 0) {
        for (int i = 1; i < std::abs(dely); i++) {
            if (boardState[std::min(y0, y1) + i][x0] != ' ') {
                return false;
            }
        }
    }
    //If requested move is along a diagonal
    else if (dely == delx) {
        for (int i = 1; i < std::abs(delx); i++) {
            if (boardState[std::min(y0, y1) + i][std::min(x0, x1) + i] != ' ') {
                return false;
            }
        }
    }
    //If requested move is along the second diagonal
    else if (delx == -dely) {
        for (int i = 1; i < std::abs(delx); i++) {
            if (boardState[std::max(y0, y1) - 1][std::min(x0, x1) + 1] != ' ') {
                return false;
            }
        }
    }
    //Check if requested spot is taken by friendly piece
    for (Piece* piece : currentPieces) {
        if (piece->getPosition().compare(to) == 0) {
            if (piece->getColor() == color) {
                return false;
            }
        }
    }

    //If the move is to castle, check if it is possible
    bool castling = (tolower(boardState[y0][x0]) == 'k') && (std::abs(delx) == 2);
    if (castling) {
        std::string fromRook;
        std::string toRook;
        Piece* rook;
        if (boardState[y0][x0] == 'k') {
            if (delx == 2) {
                //Move rook
                fromRook = "77";
                toRook = "75";
            } else if (delx == -2) {
                fromRook = "70";
                toRook = "73";
            }
        } else if (boardState[y0][x0] == 'K') {
            if (delx == 2) {
                fromRook = "07";
                toRook = "05";
            } else if (delx == -2) {
                fromRook = "00";
                toRook = "03";
            }   
        }
        for (Piece* piece : currentPieces) {
            if (piece->getPosition().compare(fromRook) == 0) {
                rook = piece;
            }
        }
        if (!validateMove(rook, toRook)) {
            return false;
        }

        //King is not allowed to castle across check
        for (int i = 0; i < 3; i++) {
            if (inCheck(std::to_string(y0) + std::to_string(std::min(x0, x1) + i), !color)) {
                return false;
            }
        }
    }
    //If the move is to move the pawn diagonally, check if possible
    bool diagonalPawn = (std::tolower(boardState[y0][x0]) == 'p') && (y0 != y1);
    if (diagonalPawn) {
        //This would be simplified with Python's for ... else loop
        for (Piece* targetPiece : currentPieces) {
            if (color != targetPiece->getColor()) {
                if (targetPiece->getPosition().compare(to) == 0) {
                    //If piece is found, jump to end. If not, return false
                    goto skip;
                }
            }
        }
        return false;
    }
    skip:
    return true;
}
bool Board::inCheck(std::string square, bool color) {
    for (Piece* piece : currentPieces) {
        //Get only one side
        if (color == piece->getColor()) {
            if (piece->movePiece(square)) {
                if (validateMove(piece, square)) {
                    return true;
                }
            }
        }
    }
    return false;
}
bool Board::movePiece(std::string from, std::string to) {
    int x0 = from.at(1) - '0';
    int y0 = from.at(0) - '0';
    int x1 = to.at(1) - '0';
    int y1 = to.at(0) - '0';

    int delx = x1 - x0;

    Piece* selectedPiece;
    //Iterate through the pieces and find the one being moved
    for (Piece* piece : currentPieces) {
        if (piece->getPosition().compare(from) == 0) {
            selectedPiece = piece;
        }
    }
    //First test
    //Make sure move is a valid piece move
    bool result = selectedPiece->movePiece(to); 

    //Second test
    //Make sure the move is not blocked
    if (result) {
        result = validateMove(selectedPiece, to);
    }

    //Setup variables in case of castling
    bool castling = (tolower(boardState[y0][x0]) == 'k') && (std::abs(delx) == 2);
    std::string fromRook;
    std::string toRook;
    Piece* rook;
    if (castling) {
        if (boardState[y0][x0] == 'k') {
            if (delx == 2) {
                //Move rook
                fromRook = "77";
                toRook = "75";
            } else if (delx == -2) {
                fromRook = "70";
                toRook = "73";
            }
        } else if (boardState[y0][x0] == 'K') {
            if (delx == 2) {
                fromRook = "07";
                toRook = "05";
            } else if (delx == -2) {
                fromRook = "00";
                toRook = "03";
            }   
        }
        for (Piece* piece : currentPieces) {
            if (piece->getPosition().compare(fromRook) == 0) {
                rook = piece;
            }
        }
    }
    if (result) {
        if (castling) {
            int x0rook = fromRook.at(1) - '0';
            int y0rook = fromRook.at(0) - '0';
            int x1rook = toRook.at(1) - '0';
            int y1rook = toRook.at(0) - '0';

            boardState[y1rook][x1rook] = boardState[y0rook][x0rook];
            boardState[y0rook][x0rook] = ' ';
            rook->setPosition(toRook);
        }
        selectedPiece->setPosition(to);
        //Perform swap
        char pieceLetter = boardState[y0][x0];
        boardState[y0][x0] = ' ';
        boardState[y1][x1] = pieceLetter;

    }
    return result;
}
std::vector<std::string> Board::getPossibleMoves(bool color) {
    std::vector<std::string> possibleMoves;
    return possibleMoves;
}