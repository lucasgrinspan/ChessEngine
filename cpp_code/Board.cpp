#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
#include"Board.h"
#include"Piece.h"
#include"Pieces/Pawn.h"
#include"Pieces/Rook.h"
#include"Pieces/Knight.h"
#include"Pieces/Bishop.h"
#include"Pieces/Queen.h"
#include"Pieces/King.h"
#include"Pieces/Blank.h"

Board::Board(char board[8][8], std::vector<std::string> moves) {
    //  White king, black king, a1, a8, h1, h8
    bool movedPieces[6] = {false, false, false, false, false, false};
    
    //  Save the moves from the move list
    for (int i = 0; i < moves.size(); i++) {
        moveList.push_back(moves[i]);

        //  Set up variables for checking if pieces moved for castling
        //  King is not allowed to castle if the pieces involved have moved
        std::vector<std::string> kingRookSquares {"74", "04", "70", "77", "00", "07"};
        std::string initSquare = moves[i].substr(0, 2);
        std::string endSquare = moves[i].substr(2, 2);
        //  Check the move list and see if any of the rooks/kings moved
        for (int j = 0; j < kingRookSquares.size(); j++) {
            std::size_t found1 = initSquare.find(kingRookSquares[j]);
            std::size_t found2 = endSquare.find(kingRookSquares[j]);
            if (found1 != std::string::npos) {
                movedPieces[j] = true;
            } 
            if (found2 != std::string::npos) {
                movedPieces[j] = true;
            }
        }
    }
    for (int i = 0; i < 6; i++) {
        movedPiecesState[i] = movedPieces[i];
    }

    //  Read from parameter board
    for (int i = 0; i < 8; i++) {
         for (int j = 0; j < 8; j++) {
            //  Copy to internal board object
            boardState[i][j] = board[i][j];

            //  Initialize Piece objects
            if (board[i][j] == 'r' || board[i][j] == 'R') {
                //  Create position
                std::string position = std::to_string(i) + std::to_string(j);
                //  True if uppercase
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
                Piece* king = new King(position, board[i][j] == 'K');
                if (board[i][j] == 'K') {
                    blackKing = king;
                } else {
                    whiteKing = king;
                }
                currentPieces.push_back(king);
            } else if (board[i][j] == 'p' || board[i][j] == 'P') {
                std::string position = std::to_string(i) + std::to_string(j);
                Piece* pawn = new Pawn(position, board[i][j] == 'P');
                currentPieces.push_back(pawn);
            } else if (board[i][j] == ' ') {
                //  std::string position = std::to_string(i) + std::to_string(j);
                //  Piece* blank = new Blank(position, true);
                //  currentPieces.push_back(blank);
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
    std::cout << std::endl;
    for (int i = 0; i < moveList.size(); i++) {
        std::cout << std::to_string(i + 1) + ": " + moveList[i].substr(0, 2) + " " + moveList[i].substr(2) << std::endl;
    }
    std::cout << std::endl;
}
bool Board::validateMove(Piece* piece, std::string to) {
    bool color = piece->getColor();
    //  Draw a line between the two squares
    //  If the line only consists of empty spaces, then the move is valid.

    std::string position = piece->getPosition();
    int x0 = position.at(1) - '0';
    int y0 = position.at(0) - '0'; 
    int x1 = to.at(1) - '0';
    int y1 = to.at(0) - '0';

    //  Get change in x and y
    int delx = x1 - x0;
    int dely = y1 - y0;

    //  If requested move is along a straight horizontal line
    if (dely == 0) {
        for (int i = 1; i < std::abs(delx); i++) {
            if (boardState[y0][std::min(x0, x1) + i] != ' ') {
                return false;
            }
        }
    }
    //  If requested move is along a straight vertical line
    else if (delx == 0) {
        for (int i = 1; i < std::abs(dely); i++) {
            if (boardState[std::min(y0, y1) + i][x0] != ' ') {
                return false;
            }
        }
    }
    //  If requested move is along a diagonal
    else if (dely == delx) {
        for (int i = 1; i < std::abs(delx); i++) {
            if (boardState[std::min(y0, y1) + i][std::min(x0, x1) + i] != ' ') {
                return false;
            }
        }
    }
    //  If requested move is along the second diagonal
    else if (delx == -dely) {
        for (int i = 1; i < std::abs(delx); i++) {
            if (boardState[std::max(y0, y1) - i][std::min(x0, x1) + i] != ' ') {
                return false;
            }
        }
    }
    //  Check if requested spot is taken by friendly piece
    for (Piece* piece : currentPieces) {
        if (piece->getPosition().compare(to) == 0) {
            if (piece->getColor() == color) {
                return false;
            }
        }
    }
    //  Check if piece is occupied for pawn
    //  Pawns cannot take headon
    if (std::tolower(boardState[y0][x0]) == 'p') {
        if (delx == 0) {
            if (boardState[y1][x1] != ' ') {
                return false;
            } 
        }
    }
    //  If the move is to castle, check if it is possible
    bool castling = (tolower(boardState[y0][x0]) == 'k') && (std::abs(delx) == 2);
    if (castling) {
        //  King is not allowed to castle if it has previously moved
        if (color) {
            if (movedPiecesState[1]) {
                return false;
            }
        } else {
            if (movedPiecesState[0]) {
                return false;
            }
        }
        
        std::string fromRook;
        std::string toRook;
        Piece* rook;
        if (boardState[y0][x0] == 'k') {
            if (delx == 2) {
                //  Check if rook has moved previously
                if (movedPiecesState[3]) {
                    return false;
                }
                //  Move rook
                fromRook = "77";
                toRook = "75";
            } else if (delx == -2) {
                if (movedPiecesState[2]) {
                    return false;
                }
                fromRook = "70";
                toRook = "73";
            }
        } else if (boardState[y0][x0] == 'K') {
            if (delx == 2) {
                if (movedPiecesState[5]) {
                    return false;
                }
                fromRook = "07";
                toRook = "05";
            } else if (delx == -2) {
                if (movedPiecesState[4]) {
                    return false;
                }
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

        //  King is not allowed to castle across check
        for (int i = 0; i < 3; i++) {
            //  Create new pieces with those positions
            //  This is done because pawns can threaten a square while not being able to move there
            //  The new placeholder pieces trick the pawn into thinking there is a piece there
            //  this allows inCheck() to return the correct value
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
    //  If the move is to move the pawn diagonally, check if possible
    bool diagonalPawn = (std::tolower(boardState[y0][x0]) == 'p') && (x0 != x1);
    if (diagonalPawn) {
        //  This would be simplified with Python's for ... else loop
        for (Piece* targetPiece : currentPieces) {
            if (color != targetPiece->getColor()) {
                if (targetPiece->getPosition().compare(to.substr(0, 2)) == 0) {
                    //  If piece is found, jump to end. If not, return false
                    goto skip;
                }
            }
        }
        //  Checks if en passant is possible
        if (!color && (y0 == 3)) {
            //  represents the square to the immediate left/right
            std::string enPassantTarget = std::to_string(3) + std::to_string(x1);
            //  En passant is only possible if target moved two squares the move prior
            std::string lastMove = moveList.back();

            if (lastMove.compare((std::to_string(1) + std::to_string(x1) + enPassantTarget)) == 0) {
                //  Only works on pawns
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
                //  Only works on pawns
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
bool Board::getMoveInCheck(int checkCount, bool color, Piece* selectedPiece, std::string from, std::string to) {
    //  Convert string coordinates to int coordinates
    int x0 = from.at(1) - '0';
    int y0 = from.at(0) - '0';
    int x1 = to.at(1) - '0';
    int y1 = to.at(0) - '0';
    //  Get the coordinates of the king piece
    Piece* kingPiece = color ? blackKing : whiteKing;
    std::string kingPosString = kingPiece->getPosition();
    //  In case that the move is en passant
    bool enPassant =    (std::tolower(boardState[y0][x0]) == 'p') &&
                        (x0 != x1) &&
                        (boardState[y1][x1] == ' ');

    //  If not in check, king can not be placed into check, or a pinned piece can not be moved
    if (checkCount == 0) {
        //  Check if king is moving to invalid square
        if (std::tolower(boardState[y0][x0]) == 'k') {
            if (inCheck(std::to_string(y1) + std::to_string(x1), !color)) {
                return false;
            }
        } 
        //  Check if the piece being moved is currently pinned
        else {
            //  Move the piece and check if the king is in check
            char previousPiece = boardState[y1][x1];
            char movedPiece = boardState[y0][x0];
            boardState[y1][x1] = movedPiece;
            boardState[y0][x0] = ' ';
            if (inCheck(kingPosString, !color)) {
                boardState[y0][x0] = movedPiece;
                boardState[y1][x1] = previousPiece;
                return false;
            }
            boardState[y1][x1] = previousPiece;
            boardState[y0][x0] = movedPiece;
        }
    }
    //  If king is in check once, then the king must move or the check must be blocked
    else if (checkCount == 1) {
        //  Check the case that the king is moving to a square in check
        if (std::tolower(boardState[y0][x0]) == 'k') {
            if (inCheck(std::to_string(y1) + std::to_string(x1), !color)) {
                return false;
            }
            if (boardState[y1][x1] != ' ') {
                char previousPieceIcon = boardState[y1][x1];
                boardState[y1][x1] = ' ';
                Piece* targetPiece;
                for (Piece* piece : currentPieces) {
                    targetPiece = piece;
                    targetPiece->setPosition("--");
                    if (inCheck(std::to_string(y1) + std::to_string(x1), !color)) {
                        targetPiece->setPosition(std::to_string(y1) + std::to_string(x1));
                        boardState[y1][x1] = previousPieceIcon;
                        return false;
                    }
                    targetPiece->setPosition(std::to_string(y1) + std::to_string(x1));
                    boardState[y1][x1] = previousPieceIcon;
                }
            }
        }
        //  Check the case of en passant
        else if (enPassant) {
            std::string enPassantTarget = std::to_string(y0) + std::to_string(x1);
            Piece* targetPiece;
            for (Piece* piece : currentPieces) {
                if (piece->getPosition().compare(enPassantTarget) == 0) {
                    targetPiece = piece;
                    //  Placeholder
                    targetPiece->setPosition("--");
                }
            }
            if (inCheck(kingPosString, !color)) {
                targetPiece->setPosition(to);
                return false;
            }
            targetPiece->setPosition(to);
        }
        //  Check the case of pin, block, or piece take
        else {
            //  Move the piece and check if the king is in check
            char previousPiece = boardState[y1][x1];
            char movedPiece = boardState[y0][x0];
            boardState[y1][x1] = movedPiece;
            boardState[y0][x0] = ' ';
            Piece* takenPiece;
            if (previousPiece != ' ') {
                for (Piece* piece : currentPieces) {
                    if (piece->getPosition().compare(to.substr(0, 2)) == 0) {
                        takenPiece = piece;
                        //  Placeholder
                        takenPiece->setPosition("--");
                    }
                }
            }
            if (inCheck(kingPosString, !color)) {
                boardState[y0][x0] = movedPiece;
                boardState[y1][x1] = previousPiece;
                if (previousPiece != ' ') {
                    takenPiece->setPosition(to.substr(0, 2));
                }
                return false;
            }
            boardState[y1][x1] = previousPiece;
            boardState[y0][x0] = movedPiece;
            if (previousPiece != ' ') {
                takenPiece->setPosition(to.substr(0, 2));
            }
        }
    }
    //  If king is in check twice, then the king must move
    else if (checkCount == 2) {
        if (std::tolower(boardState[y0][x0] != 'k')) {
            return false;
        } else {
            if (inCheck(std::to_string(y1) + std::to_string(x1), !color)) {
                return false;
            }
        }
    }
    //  Else, an error happened
    else {
        std::cout << "Invalid state: The king can not be in check more than twice" << std::endl;
        return false;
    }
    return true;
}
bool Board::inCheck(std::string square, bool color) {
    for (Piece* piece : currentPieces) {
        //  Get only one side
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
int Board::getKingStatus(bool color) {
    int index = 0;
    std::string square = color ? blackKing->getPosition() : whiteKing->getPosition();
    for (Piece* piece : currentPieces) {
        //  Get only one side
        if (color != piece->getColor()) {
            if (piece->movePiece(square)) {
                if (validateMove(piece, square)) {
                    index++;
                }
            }
        }
    }
    return index;
}
bool Board::movePiece(std::string from, std::string to, bool diagnostics, bool apply) {
    //  bool apply is by default set to true
    //  It determines if the move is applied to the board
    //  bool diagnostics is by default set to true
    //  If false, the diagnostic messages do not print

    int x0 = from.at(1) - '0';
    int y0 = from.at(0) - '0';
    int x1 = to.at(1) - '0';
    int y1 = to.at(0) - '0';

    int delx = x1 - x0;

    Piece* selectedPiece;
    //  Iterate through the pieces and find the one being moved
    for (Piece* piece : currentPieces) {
        if (piece->getPosition().compare(from) == 0) {
            selectedPiece = piece;
        }
    }
    if (diagnostics) {std::cout << "Found piece" << std::endl;}
    //  First test
    //  Make sure move is a valid piece move
    bool result = selectedPiece->movePiece(to); 
    if (diagnostics) {std::cout << "First test: " << result << std::endl;}
    
    //  Second test
    //  Make sure the move is not blocked
    if (result) {
        result = validateMove(selectedPiece, to);
    }
    if (diagnostics) {std::cout << "Second test: " << result << std::endl;}

    //  Third test
    //  Make sure king is not in check now
    if (result) {
        //  Check if king is currently in check and by how many times
        bool color = selectedPiece->getColor();
        int checkCount = getKingStatus(color);
        result = getMoveInCheck(checkCount, color, selectedPiece, from, to);
    }
    if (diagnostics) {std::cout << "Third test: " << result << std::endl;}

    //  Setup variables in case of castling
    bool castling = (tolower(boardState[y0][x0]) == 'k') && (std::abs(delx) == 2);
    std::string fromRook;
    std::string toRook;
    Piece* rook;

    if (castling) {
        if (diagnostics) {std::cout << "castling detected" << std::endl;}
        if (boardState[y0][x0] == 'k') {
            if (delx == 2) {
                //  Move rook
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
                if (diagnostics) {std::cout << "Rook found" << std::endl;}
            }
        }
    }

    //  True if the move is en passant
    bool enPassant =    (std::tolower(boardState[y0][x0]) == 'p') &&
                        (x0 != x1) &&
                        (boardState[y1][x1] == ' ');
    if (apply) {
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

            //  Detect if a piece is being taken
            char previousPiece = boardState[y1][x1];
            if (previousPiece != ' ') {
                for (int i = 0; i < currentPieces.size(); i++) {
                    if (currentPieces[i]->getPosition().compare(to.substr(0, 2)) == 0) {
                        delete currentPieces[i];
                        currentPieces.erase(currentPieces.begin() + i);
                    }
                }
            }

            selectedPiece->setPosition(to.substr(0, 2));
            
            //  Delete taken piece due to enpassant
            if (enPassant) {
                if (diagnostics) {std::cout << "En Passant detected" << std::endl;}
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

            //  Perform swap
            char pieceLetter = boardState[y0][x0];
            boardState[y0][x0] = ' ';
            boardState[y1][x1] = pieceLetter;

            //  Check if the move is a pawn promotion
            bool pawnPromotion =    (std::tolower(boardState[y1][x1]) == 'p') &&
                                    (y1 == 7 || y1 == 0);

            if (pawnPromotion) {
                //  Get the promotion piece
                boardState[y1][x1] = to.at(2);
                if (diagnostics) {std::cout << "Pawn promotion detected" << std::endl;}

                //  Delete promoted pawn
                for (int i = 0; i < currentPieces.size(); i++) {
                    if (currentPieces[i]->getPosition().compare(to) == 0) {
                        delete currentPieces[i];
                        currentPieces.erase(currentPieces.begin() + i + 1);
                    }
                }

                //  Create new piece and push it to the piece list
                char promotedPiece = to.at(2);
                std::string newSquare = to.substr(0, 2);
                switch (std::tolower(promotedPiece)) {
                    case 'q': {
                        Piece* promotedQueen = new Queen(newSquare, selectedPiece->getColor());
                        currentPieces.push_back(promotedQueen);
                        break;
                    }
                    case 'b': {
                        Piece* promotedBishop = new Bishop(newSquare, selectedPiece->getColor());
                        currentPieces.push_back(promotedBishop);
                        break;
                    }
                    case 'r': {
                        Piece* promotedRook = new Rook(newSquare, selectedPiece->getColor());
                        currentPieces.push_back(promotedRook);
                        break;
                    }
                    case 'n': {
                        Piece* promotedKnight = new Knight(newSquare, selectedPiece->getColor());
                        currentPieces.push_back(promotedKnight);
                        break;
                    }
                }
            }
            //  Add move to the move list
            moveList.push_back(from + to);

            //  Check to see if the king or rook moved, so that the castling state is updated
            std::vector<std::string> kingRookSquares {"74", "04", "70", "77", "00", "07"};
            
            for (int j = 0; j < kingRookSquares.size(); j++) {
                std::size_t found1 = from.find(kingRookSquares[j]);
                std::size_t found2 = to.find(kingRookSquares[j]);
                if (found1 != std::string::npos) {
                    movedPiecesState[j] = true;
                } 
                if (found2 != std::string::npos) {
                    movedPiecesState[j] = true;
                }
            }
            
        }
    }
    return result;
}
std::vector<std::string> Board::getPossibleMoves(bool color) {
    std::vector<std::string> possibleMoves;
    for (Piece* piece : currentPieces) {
        if (piece->getColor() == color) {
            std::string currentPos = piece->getPosition();
            std::vector<std::string> tiles = piece->getAreasOfInfluence();
            for (std::string tile : tiles) {
                if (movePiece(currentPos, tile, false, false)) {
                    possibleMoves.push_back(currentPos + tile);
                }    
            }
        }
    }
    return possibleMoves;
}
// std::vector<std::string> Board::getPossibleMovesOfPiece(std::string tile) {
//     std::vector<std::string> possibleMoves;
//     for (Piece* piece : currentPieces){
//         if (piece->getPosition().compare(tile) == 0) {
//             for (int i = 0; i < 8; i++) {
//                 for (int j = 0; j < 8; j++) {
//                     if (piece->movePiece(std::to_string(i) + std::to_string(j))) {
//                         if (validateMove(piece, std::to_string(i) + std::to_string(j))) {
//                             possibleMoves.push_back(std::to_string(i) + std::to_string(j));
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     return possibleMoves;
// }
