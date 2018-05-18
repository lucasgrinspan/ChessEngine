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

Board::Board(char board[8][8], bool movedPieces[6], std::vector<std::string> moves) {
    //Save the moves from the move list
    for (int i = 0; i < moves.size(); i++) {
        moveList.push_back(moves[i]);
    }

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
void Board::printMoves() {
    for (int i = 0; i < moveList.size(); i++) {
        std::cout << std::to_string(i + 1) + ": " + moveList[i].substr(0, 2) + " " + moveList[i].substr(2, 2) << std::endl;
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
            //Create new pieces with those positions
            //This is done because pawns can threaten a square while not being able to move there
            //The new placeholder pieces trick the pawn into thinking there is a piece there
            //this allows inCheck() to return the correct value
            Piece* placeHolder = new Blank(std::to_string(y0) + std::to_string(std::min(x0, x1) + i), color);
            currentPieces.push_back(placeHolder);
            if (inCheck(std::to_string(y0) + std::to_string(std::min(x0, x1) + i), !color)) {
                currentPieces.pop_back();
                delete placeHolder;
                return false;
            }
            currentPieces.pop_back();
            delete placeHolder;
        }
    }
    //If the move is to move the pawn diagonally, check if possible
    bool diagonalPawn = (std::tolower(boardState[y0][x0]) == 'p') && (x0 != x1);
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
        //Checks if en passant is possible
        if (!color && (y0 == 3)) {
            //represents the square to the immediate left/right
            std::string enPassantTarget = std::to_string(3) + std::to_string(x1);
            //En passant is only possible if target moved two squares the move prior
            std::string lastMove = moveList.back();

            if (lastMove.compare((std::to_string(1) + std::to_string(x1) + enPassantTarget)) == 0) {
                //Only works on pawns
                if (boardState[3][x1] == 'P') {
                    for (Piece* targetPiece : currentPieces) {
                        if (targetPiece->getColor()) {
                            if (targetPiece->getPosition().compare(enPassantTarget) == 0) {
                                goto skip;
                            }
                        }
                    }
                }
            }
        } else if (color && (y0 == 4)) {
            std::string enPassantTarget = std::to_string(4) + std::to_string(x1);
            std::string lastMove = moveList.back();
            if (lastMove.compare((std::to_string(6) + std::to_string(x1) + enPassantTarget)) == 0) {
                //Only works on pawns
                if (boardState[4][x1] == 'p') {
                    for (Piece* targetPiece : currentPieces) {
                        if (!targetPiece->getColor()) {
                            if (targetPiece->getPosition().compare(enPassantTarget) == 0) {
                                goto skip;
                            }
                        }
                    }
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
    std::cout << "found piece" << std::endl;
    //First test
    //Make sure move is a valid piece move
    bool result = selectedPiece->movePiece(to); 
    std::cout << "first test: " << result << std::endl;
    //Second test
    //Make sure the move is not blocked
    if (result) {
        result = validateMove(selectedPiece, to);
    }
    std::cout << "second test: " << result << std::endl;
    
    //Setup variables in case of castling
    bool castling = (tolower(boardState[y0][x0]) == 'k') && (std::abs(delx) == 2);
    std::string fromRook;
    std::string toRook;
    Piece* rook;
    if (castling) {
        std::cout << "castling detected" << std::endl;
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
                std::cout << "rook found" << std::endl;
            }
        }
    }
    
    //True if the move is en passant
    bool enPassant =    (std::tolower(boardState[y0][x0]) == 'p') &&
                        (x0 != x1) &&
                        (boardState[y1][x1] == ' ');
   
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
        
        //Detect if a piece is being taken
        char previousPiece = boardState[y1][x1];
        if (previousPiece != ' ') {
            for (int i = 0; i < currentPieces.size(); i++) {
                if (currentPieces[i]->getPosition().compare(to) == 0) {
                    delete currentPieces[i];
                    currentPieces.erase(currentPieces.begin() + i + 1);
                }
            }
        }

        //Delete taken piece due to enpassant
        if (enPassant) {
            std::cout << "En Passant detected" << std::endl;
            std::string enPassantTarget;
            if (!selectedPiece->getColor()) {
                enPassantTarget = std::to_string(3) + std::to_string(x1);
            } else {
                enPassantTarget = std::to_string(4) + std::to_string(x1);
            }
            for (int i = 0; i < currentPieces.size(); i++) {
                if (currentPieces[i]->getPosition().compare(enPassantTarget) == 0) {
                    delete currentPieces[i];
                    currentPieces.erase(currentPieces.begin() + i + 1);
                }
            }
            boardState[enPassantTarget.at(0) - '0'][enPassantTarget.at(1) - '0'] = ' ';
        }

        //Perform swap
        char pieceLetter = boardState[y0][x0];
        boardState[y0][x0] = ' ';
        boardState[y1][x1] = pieceLetter;

        //Add move to the move list
        if (!castling) {
            moveList.push_back(from + to);
        } else {
            moveList.push_back("OOOO");
        }
    }
    return result;
}
std::vector<std::string> Board::getPossibleMoves(bool color) {
    std::vector<std::string> possibleMoves;
    return possibleMoves;
}