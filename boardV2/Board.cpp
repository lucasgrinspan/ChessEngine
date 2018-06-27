#include"Board.h"
#include<string>
#include<vector>
#include<array>
#include<iostream>

//  Change DIAGNOSTICS to 1 to include diagnostic messages
#define DIAGNOSTICS 1

#if DIAGNOSTICS
    #define Log(X) std::cout<<X<<std::endl
#else
    #define Log(X) //
#endif


Board::Board(std::array<char, 64> pieces, std::array<bool, 6> movedPieces, std::string lastMove) {
    m_board = pieces;
    m_movedPiecesList = movedPieces;
    m_lastMove = lastMove;
    
    //  White has first move
    generateAttackedSquares(false);
}
int Board::getYCoord(int tileNumber) {
    return tileNumber / 8;
}
int Board::getXCoord(int tileNumber) {
    return tileNumber % 8;
}
int Board::getTileNumber(int x, int y) {
    return (y * 8) + x;
}
bool Board::isWhite(char piece) {
    //  Returns true if piece is white
    return std::islower(piece);
}
bool Board::isOpponentPiece(char piece, bool color) {
    if (piece == ' ') {
        return false;
    } else {
        return std::islower(piece) != color;
    }
}
bool Board::withinBounds(int x, int y) {
    //  Checks if x and y are in the 8x8 board
    return (x >= 0) && (x <= 7) && (y >= 0) && (y <= 7);
}
bool Board::isInCheck(int tileNumber) {
    return m_attackedSquares[tileNumber];
}
void Board::hideKing(bool color) {
    //  Hide the king in the board so that ray pieces do not take the king into account
    int kingPosition = color ? kingPositionWhite : kingPositionBlack;
    m_board[kingPosition] = ' ';
}
void Board::resetKing(bool color) {
    //  Reset the king position
    char kingPiece = color ? 'k' : 'K';
    int kingPosition = color ? kingPositionWhite : kingPositionBlack;
    m_board[kingPosition] = kingPiece;
}
void Board::printBoard() {
    for (int i = 0; i < NUM_TILES; i++) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << m_board[i] << " ";
    }
    std::cout << std::endl;
}
std::vector<int> Board::getStraightLineMoves(int tileNumber, bool color, int range, bool influence) {

    std::vector<int> possibleMoves;
    //  Handle limits in horizontal direction
    int limitRight = BOARD_LENGTH - getXCoord(tileNumber);
    int limitLeft = getXCoord(tileNumber) + 1;
    int limitUp = getYCoord(tileNumber) + 1;
    int limitDown = BOARD_LENGTH - getYCoord(tileNumber);

    //  Iterate over squares to the right
    for (int j = 1; j < std::min(limitRight, range); j++) {
        int tile = tileNumber + j;
        if (m_board[tile] == ' ') {
            possibleMoves.push_back(tile);
            continue;
        } else if (isOpponentPiece(m_board[tile], color)) {
            possibleMoves.push_back(tile);
            break;
        } else {
            if (influence) {
                possibleMoves.push_back(tile);
            }
            break;
        }
    }
    //  Iterate over squares to the left
    for (int j = 1; j < std::min(limitLeft, range); j++) {
        int tile = tileNumber - j;
        if (m_board[tile] == ' ') {
            possibleMoves.push_back(tile);
            continue;
        } else if (isOpponentPiece(m_board[tile], color)) {
            possibleMoves.push_back(tile);
            break;
        } else {
            if (influence) {
                possibleMoves.push_back(tile);
            }
            break;
        }
    }
    //  Iterate over squares above
    for (int j = 1; j < std::min(limitUp, range); j++) {
        int tile = tileNumber - (j * 8);
        if (m_board[tile] == ' ') {
            possibleMoves.push_back(tile);
            continue;
        } else if (isOpponentPiece(m_board[tile], color)) {
            possibleMoves.push_back(tile);
            break;
        } else {
            if (influence) {
                possibleMoves.push_back(tile);
            }
            break;
        }
    }
    //  Iterate over squares below
    for (int j = 1; j < std::min(limitDown, range); j++) {
        int tile = tileNumber + (j * 8);
        if (m_board[tile] == ' ') {
            possibleMoves.push_back(tile);
            continue;
        } else if (isOpponentPiece(m_board[tile], color)) {
            possibleMoves.push_back(tile);
            break;
        } else {
            if (influence) {
                possibleMoves.push_back(tile);
            }
            break;
        }
    }
    return possibleMoves;
}
std::vector<int> Board::getDiagonalMoves(int tileNumber, bool color, int range, bool influence) {
    std::vector<int> possibleMoves;
    int distanceRight = BOARD_LENGTH - getXCoord(tileNumber);
    int distanceLeft = getXCoord(tileNumber) + 1;
    int distanceUp = getYCoord(tileNumber) + 1;
    int distanceDown = BOARD_LENGTH - getYCoord(tileNumber);

    int limitUpRight = std::min(distanceRight, distanceUp);
    int limitUpLeft = std::min(distanceLeft, distanceUp);
    int limitDownRight = std::min(distanceDown, distanceRight);
    int limitDownLeft = std::min(distanceDown, distanceLeft);

    //  Iterate diagonal up right
    for (int j = 1; j < std::min(limitUpRight, range); j++) {
        //  Subtracting 7 gives you the tile up and to the right
        int tile = tileNumber - (7 * j);
        if (m_board[tile] == ' ') {
            possibleMoves.push_back(tile);
            continue;
        } else if (isOpponentPiece(m_board[tile], color)) {
            possibleMoves.push_back(tile);
            break;
        } else {
            if (influence) {
                possibleMoves.push_back(tile);
            }
            break;
        }
    }
    //  Iterate diagonal up left
    for (int j = 1; j < std::min(limitUpLeft, range); j++) {
        //  Subtracting 9 gives you the tile up and to the left
        int tile = tileNumber - (9 * j);
        if (m_board[tile] == ' ') {
            possibleMoves.push_back(tile);
            continue;
        } else if (isOpponentPiece(m_board[tile], color)) {
            possibleMoves.push_back(tile);
            break;
        } else {
            if (influence) {
                possibleMoves.push_back(tile);
            }
            break;
        }
    }
    //  Iterate diagonal down right
    for (int j = 1; j < std::min(limitDownRight, range); j++) {
        //  Adding 9 gives you the tile down and to the right
        int tile = tileNumber + (9 * j);
        if (m_board[tile] == ' ') {
            possibleMoves.push_back(tile);
            continue;
        } else if (isOpponentPiece(m_board[tile], color)) {
            possibleMoves.push_back(tile);
            break;
        } else {
            if (influence) {
                possibleMoves.push_back(tile);
            }
            break;
        }
    }
    //  Iterate diagonal up right
    for (int j = 1; j < std::min(limitDownLeft, range); j++) {
        //  Adding 7 gives you the tile up and to the right
        int tile = tileNumber + (7 * j);
        if (m_board[tile] == ' ') {
            possibleMoves.push_back(tile);
            continue;
        } else if (isOpponentPiece(m_board[tile], color)) {
            possibleMoves.push_back(tile);
            break;
        } else {
            if (influence) {
                possibleMoves.push_back(tile);
            }
            break;
        }
    }
    return possibleMoves;
}
std::vector<int> Board::getKnightMoves(int tileNumber, bool color, bool influence) {
    
    std::vector<int> possibleMoves;
    
    int x = getXCoord(tileNumber);
    int y = getYCoord(tileNumber);

    //  Set up the x, y offsets for the knight
    std::array<int, 16> knightOffsets {x - 1, y - 2, x - 1, y + 2, 
                                       x + 1, y - 2, x + 1, y + 2, 
                                       x - 2, y - 1, x - 2, y + 1, 
                                       x + 2, y - 1, x + 2, y + 1};
    //  Go through each possible move in the knight and check
    for (int i = 0; i < knightOffsets.size(); i++) {
        int x1 = knightOffsets[i];
        int y1 = knightOffsets[++i];
        if (withinBounds(x1, y1)) {
            int tile = getTileNumber(x1, y1);
            if (m_board[tile] == ' ') {
                possibleMoves.push_back(tile);
            } else if (isOpponentPiece(m_board[tile], color)) {
                possibleMoves.push_back(tile);
            } else if (influence) {
                possibleMoves.push_back(tile);
            }
        }
    }
    return possibleMoves;
}
std::vector<int> Board::getPawnMoves(int tileNumber, bool color, bool influence) {
    std::vector<int> possibleMoves;

    int modifier = color ? -1 : 1;
    int startingRow = color ? 6 : 1;
    int x = getXCoord(tileNumber);
    int y = getYCoord(tileNumber);

    if (!influence) {
        int tile = tileNumber + (modifier * 8);
        if (m_board[tile] == ' ') {
            possibleMoves.push_back(tile);
            
            //  Check if the pawn is on the second row
            //  so that it can start with a double move forward
            int tile = tileNumber + (modifier * 16);
            if (getYCoord(tileNumber) == startingRow) {
                if (m_board[tile] == ' ') {
                    possibleMoves.push_back(tile);
                }
            }
        }
    }
    //  Check for diagonal capture moves
    if (x != 0) {
        //  Get tile to the left diagonal
        int tile = tileNumber + (modifier * 8) - 1;
        if (isOpponentPiece(m_board[tile], color) || influence) {
            possibleMoves.push_back(tile);
        }
    }
    if (x != 7) {
        //  Get tile to the right diagonal
        int tile = tileNumber + (modifier * 8) + 1;
        if (isOpponentPiece(m_board[tile], color) || influence) {
            possibleMoves.push_back(tile);
        }
    }
    //  Check for en passant
    int enPassantColumn = color ? 3 : 4;
    if (y == enPassantColumn) {
        //TODO: check last move and apply rule
    }
    return possibleMoves;
}
std::vector<int> Board::getKingMoves(int tileNumber, bool color, bool influence) {
    std::vector<int> possibleMoves;

    int x = getXCoord(tileNumber);
    int y = getYCoord(tileNumber);

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            //  Filter out squares out of bounds
            if (withinBounds(x + i, y + j)) {
                //  Filter out the king square
                if ((i != 0) || (j != 0)) {
                    int tile = getTileNumber(x + i, y + j);
                    if (influence) {
                        possibleMoves.push_back(tile);
                    } else {
                        //  Check if the tile is in check
                        if (!isInCheck(tile)) {
                            if (m_board[tile] == ' ') {
                                possibleMoves.push_back(tile);
                            } else if (isOpponentPiece(m_board[tile], color)) {
                                possibleMoves.push_back(tile);
                            }
                        }
                    }
                }
            }
        }
    }
    return possibleMoves;
}
void Board::generateAttackedSquares(bool color) {
    //  Get the squares attacked by the color in the parameter
    std::array<bool, 64> attackedSquares;
    attackedSquares.fill(false);
    
    //  Remove the king from the board so that the ray pieces do not take it into account
    hideKing(!color);
    for (int i = 0; i < NUM_TILES; i++) {
        if (!isOpponentPiece(m_board[i], color)) {
            char piece = std::tolower(m_board[i]);
            int position = i;
            switch (piece) {
                case 'r': {
                    //  Get the squares that the rook attacks and set it to true in bitboard
                    std::vector<int> attackingSquares = getStraightLineMoves(i, color, MAX_RANGE, INFLUENCE);
                    for (int square : attackingSquares) {
                        attackedSquares[square] = true;
                    }
                    break;
                }
                case 'q': {
                    std::vector<int> attackingSquares = getStraightLineMoves(position, color, MAX_RANGE, INFLUENCE);
                    //  Insert diagonal moves
                    std::vector<int> diagonalMoves = getDiagonalMoves(position, color, MAX_RANGE, INFLUENCE);
                    attackingSquares.insert(attackingSquares.end(), 
                                               diagonalMoves.begin(), 
                                               diagonalMoves.end());
                    for (int square : attackingSquares) {
                        attackedSquares[square] = true;
                    }
                    break;
                }
                case 'k': {
                    std::vector<int> attackingSquares = getKingMoves(position, color, INFLUENCE);
                    for (int square : attackingSquares) {
                        attackedSquares[square] = true;
                    }
                    break;
                }
                case 'n': {
                    std::vector<int> attackingSquares = getKnightMoves(position, color, INFLUENCE);
                    for (int square : attackingSquares) {
                        attackedSquares[square] = true;
                    }
                    break;
                }
                case 'b': {
                    std::vector<int> attackingSquares = getDiagonalMoves(position, color, MAX_RANGE, INFLUENCE);
                    for (int square : attackingSquares) {
                        attackedSquares[square] = true;
                    }
                    break;
                }
                case 'p': {
                    std::vector<int> attackingSquares = getPawnMoves(position, color, INFLUENCE);
                    for (int square : attackingSquares) {
                        attackedSquares[square] = true;
                    }
                    break;
                }
            }
        }
    }
    //  Put the king back in the board
    printBoard();
    resetKing(!color);


    //  Print attacking squares
    // for (int i = 0; i < NUM_TILES; i++) {
    //     if (i % 8 == 0) {
    //         std::cout << std::endl;
    //     }
    //     std::cout << attackedSquares[i] << " ";
    // }
    // std::cout << std::endl;

    m_attackedSquares = attackedSquares;
}
std::array<std::vector<int>, 64> Board::getPossibleMoves(bool color) {
    std::array<std::vector<int>, 64> possibleMoves;
    
    //  Determine if king is in check

    for (int i = 0; i < NUM_TILES; i++) {
        if (m_board[i] == ' ') {continue;}
        if (isOpponentPiece(m_board[i], color)) {continue;}

        //TODO: add way to check by what pieces the king is in check
        int position = i;
        char piece = std::tolower(m_board[i]);
        switch (piece) {
            case 'r': {
                possibleMoves[position] = getStraightLineMoves(position, color, MAX_RANGE, MOVEMENT);
                break; 
            }      
            case 'q': {
                possibleMoves[position] = getStraightLineMoves(position, color, MAX_RANGE, MOVEMENT);
                //  Insert diagonal moves
                std::vector<int> diagonalMoves = getDiagonalMoves(position, color, MAX_RANGE, MOVEMENT);
                possibleMoves[position].insert(possibleMoves[position].end(), 
                                               diagonalMoves.begin(), 
                                               diagonalMoves.end());
                break;
            }
            case 'k': {
                possibleMoves[position] = getKingMoves(position, color, MOVEMENT);
                break;
            }
            case 'n': {
                
                possibleMoves[position] = getKnightMoves(position, color, MOVEMENT);
                break;
            }
            case 'b': {
                possibleMoves[position] = getDiagonalMoves(position, color, MAX_RANGE, MOVEMENT);
                break;
            }
            case 'p': {
                possibleMoves[position] = getPawnMoves(position, color, MOVEMENT);
                break;
            }
            default: {
                Log("ERROR: invalid piece icon found: " << piece);
                return possibleMoves;
            }
        }
    }
    return possibleMoves;
}
bool Board::movePiece(int tileNum0, int tileNum1, int promotionCase) {
    //  Set up special cases flags
    bool castling = false;
    bool enPassant = false;
    bool capture = false;
    bool promotion = promotionCase > 0;

    //  Set up coordinates
    int y0 = getYCoord(tileNum0);
    int x0 = getXCoord(tileNum0);
    int y1 = getYCoord(tileNum1);
    int x1 = getXCoord(tileNum1);
  
    int delx = x1 - x0;
    int dely = y1 - y0;

    //  Set up pieces information
    char pieceIcon = m_board[tileNum0];
    char targetIcon = m_board[tileNum1];
    //  True if white
    bool pieceColor = pieceIcon == std::tolower(pieceIcon);
    
    if (pieceIcon != ' ') {
        Log("Found piece...");
    } else {
        Log("ERROR: no piece found at tile");
        return false;
    }

    
    if (targetIcon != ' ') {
        Log("Capturing piece...");
        capture = true;
    }
    
    bool straight = (delx == 0) || (dely == 0);
    bool diagonal = std::abs(delx) == std::abs(dely);
    bool knight = (!straight && !diagonal);

    if (straight && diagonal) {
        Log("ERROR: bool straight and bool diagonal are both true");
        return false;
    }
    //  Code for moving a piece in a straight line
    if (straight) {
        switch(std::tolower(pieceIcon)) {
            case 'r': {
                Log("Moving rook...");
                bool horizontal = (dely == 0);
                //  Find the length of the movement line
                int lengthOfMovement = std::max(std::abs(delx), std::abs(dely));
                for (int i = 1; i < lengthOfMovement; i++) {
                    //  Find way to include negative
                    if (m_board[tileNum0 + (i * (horizontal ? 1 : 8))] == ' ') {
                        Log("ERROR: collision detected");
                        return false;
                    }
                }
                break; 
            }      
            case 'q': {
                Log("Moving queen...");
                break;
            }
            case 'k': {
                Log("Moving king...");
                break;
            }
            case 'n': {
                Log("ERROR: attempting to move knight in a straight line");
                return false;
            }
            case 'b': {
                Log("ERROR: attempting to move bishop in a straight line");
                return false;
            }
        }
    }
}