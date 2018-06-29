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
    m_lastMove0 = std::stoi(lastMove.substr(0, 2));
    m_lastMove1 = std::stoi(lastMove.substr(2));
    
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
bool Board::checkMask(int tileNumber) {
    return (m_blockMask[tileNumber] || m_captureMask[tileNumber]);
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
void Board::printBitBoard(std::array<bool, 64> board) {
    for (int i = 0; i < NUM_TILES; i++) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << board[i] << " ";
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
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
                continue;
            }
        } else if (isOpponentPiece(m_board[tile], color)) {
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
                break;
            }
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
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
                continue;
            }
        } else if (isOpponentPiece(m_board[tile], color)) {
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
                break;
            }
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
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
                continue;
            }
        } else if (isOpponentPiece(m_board[tile], color)) {
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
                break;
            }
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
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
                continue;
            }
        } else if (isOpponentPiece(m_board[tile], color)) {
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
                break;
            }
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
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
                continue;
            }
        } else if (isOpponentPiece(m_board[tile], color)) {
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
                break;
            }
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
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
                continue;
            }
        } else if (isOpponentPiece(m_board[tile], color)) {
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
                break;
            }
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
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
                continue;
            }
        } else if (isOpponentPiece(m_board[tile], color)) {
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
                break;
            }
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
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
                continue;
            }
        } else if (isOpponentPiece(m_board[tile], color)) {
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
                break;
            }
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
                if (influence || checkMask(tile)) {
                    possibleMoves.push_back(tile);
                }
            } else if (isOpponentPiece(m_board[tile], color)) {
                if (influence || checkMask(tile)) {
                    possibleMoves.push_back(tile);
                }
            } else {
                if (influence) {
                    possibleMoves.push_back(tile);
                }
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
            if (m_blockMask[tile]) {
                possibleMoves.push_back(tile);
            }
            
            //  Check if the pawn is on the second row
            //  so that it can start with a double move forward
            int tile = tileNumber + (modifier * 16);
            if (getYCoord(tileNumber) == startingRow) {
                if (m_board[tile] == ' ') {
                    if (m_blockMask[tile]) {
                        possibleMoves.push_back(tile);
                    }
                }
            }
        }
    }
    //  Check for diagonal capture moves
    if (x != 0) {
        //  Get tile to the left diagonal
        int tile = tileNumber + (modifier * 8) - 1;
        if (isOpponentPiece(m_board[tile], color) || influence) {
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
            }
        }
    }
    if (x != 7) {
        //  Get tile to the right diagonal
        int tile = tileNumber + (modifier * 8) + 1;
        if (isOpponentPiece(m_board[tile], color) || influence) {
            if (influence || checkMask(tile)) {
                possibleMoves.push_back(tile);
            }
        }
    }
    //  Check for en passant
    int enPassantRow = color ? 3 : 4;
    if (y == enPassantRow) {
        char pawnIcon = color ? 'p' : 'P';
        int pawnStartRow = color ? 1 : 6;

        //  For en passant to apply, the last move must be a double push forward
        //  from a pawn, ending up directly next to an opponent's pawn
        if ((getYCoord(m_lastMove0) == pawnStartRow) &&
            (getYCoord(m_lastMove1) == enPassantRow) &&
            (std::tolower(m_board[m_lastMove1]) == 'p') &&
            (std::abs(tileNumber - m_lastMove1) == 1)) {
                int enPassantTarget = m_lastMove1;
                int modifier = color ? -1 : 1;
                int moveLocation = enPassantTarget + (modifier * 8);

                //  En passant is unique because either the opponent pawn is in the capture mask, 
                //  or the resulting tile is in the block mask
                if (m_captureMask[enPassantTarget] || 
                    m_blockMask[moveLocation]) {
                        possibleMoves.push_back(moveLocation);
                    }
        }
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
std::array<int, 2> Board::getCheckLocations(bool color) {
    //  Parameter is the color of the king in check
    std::array<int, 2> checkLocations = {-1, -1};
    int arrayIndex = 0;

    //  Setup variables
    int kingLocation = color ? kingPositionWhite : kingPositionBlack;
    char knightIcon = !color ? 'n' : 'N';
    char bishopIcon = !color ? 'b' : 'B';
    char queenIcon  = !color ? 'q' : 'Q';
    char rookIcon   = !color ? 'r' : 'R';
    char pawnIcon   = !color ? 'p' : 'P';

    //  Check for check against knight
    std::vector<int> knightMask = getKnightMoves(kingLocation, !color, INFLUENCE);
    for (int i = 0; i < knightMask.size(); i++) {
        if (m_board[knightMask[i]] == knightIcon) {
            checkLocations[arrayIndex++] = knightMask[i];
            //  It is not possible to be in check from two knights at the same time, 
            //  so it is safe to break here
            break;
        }
    }

    //  Check for check against bishop/queen
    std::vector<int> diagonalMask = getDiagonalMoves(kingLocation, !color, MAX_RANGE, INFLUENCE);
    for (int i = 0; i < diagonalMask.size(); i++) {
        if (m_board[diagonalMask[i]] == bishopIcon) {
            checkLocations[arrayIndex++] = diagonalMask[i];
        } else if (m_board[diagonalMask[i]] == queenIcon) {
            checkLocations[arrayIndex++] = diagonalMask[i];
        }
    }
    if (arrayIndex == 2) {
        return checkLocations;
    }

    //  Check for check from rooks
    std::vector<int> straightMask = getStraightLineMoves(kingLocation, !color, MAX_RANGE, INFLUENCE);
    for (int i = 0; i < straightMask.size(); i++) {
        if (m_board[straightMask[i]] == rookIcon) {
            checkLocations[arrayIndex++] = straightMask[i];
            //  It is not possible to be in check more than once by a rook or horizontal queen,
            //  so it is safe to break here
            break;
        } else if (m_board[straightMask[i]] == queenIcon) {
            checkLocations[arrayIndex++] = straightMask[i];
            break;
        }
    }
    if (arrayIndex == 2) {
        return checkLocations;
    }

    //  Check for check from pawns
    std::vector<int> pawnMask = getPawnMoves(kingLocation, color, INFLUENCE); 
    for (int i = 0; i < pawnMask.size(); i++) {    
        if (m_board[pawnMask[i]] == pawnIcon) {
            checkLocations[arrayIndex] = pawnMask[i];
            //  It is not possible to be in check more than once by a rook,
            //  so it is safe to break here
            break;
        }
    }
    return checkLocations;
}
std::array<int, 8> Board::getPinnedPieces(bool color) {
    //  This function works by iterating over squares in all of the eight possible
    //  directions from the king square. If a valid enemy piece is detected after a
    //  friendly piece, then the friendly piece is considered to be pinned. Diagonal
    //  pins can only be from a bishop or queen, and straight line pins can only be
    //  from a rook or queen.

    //  There can be at most 8 pins at a time
    std::array<int, 8> pinnedPieces;
    pinnedPieces.fill(-1);
    int arrayIndex = 0;

    int kingLocation = color ? kingPositionWhite : kingPositionBlack;

    //  Set up iteration limits
    int limitRight = BOARD_LENGTH - getXCoord(kingLocation);
    int limitLeft = getXCoord(kingLocation) + 1;
    int limitUp = getYCoord(kingLocation) + 1;
    int limitDown = BOARD_LENGTH - getYCoord(kingLocation);

    //  Check squares to the right
    int pinLocation = calculatePin(color, limitRight, 1, kingLocation, 'r');
    if (pinLocation != -1) {
        pinnedPieces[arrayIndex++] = pinLocation;
    }

    //  Check squares to the left
    pinLocation = calculatePin(color, limitLeft, -1, kingLocation, 'r');
    if (pinLocation != -1) {
        pinnedPieces[arrayIndex++] = pinLocation;
    }

    //  Check squares above
    pinLocation = calculatePin(color, limitUp, -8, kingLocation, 'r');
    if (pinLocation != -1) {
        pinnedPieces[arrayIndex++] = pinLocation;
    }

    //  Check squares below
    pinLocation = calculatePin(color, limitDown, 8, kingLocation, 'r');
    if (pinLocation != -1) {
        pinnedPieces[arrayIndex++] = pinLocation;
    }

    //  Check squares up right
    pinLocation = calculatePin(color, std::min(limitRight, limitUp), -7, kingLocation, 'b');
    if (pinLocation != -1) {
        pinnedPieces[arrayIndex++] = pinLocation;
    }

    //  Check squares up left
    pinLocation = calculatePin(color, std::min(limitLeft, limitUp), -9, kingLocation, 'b');
    if (pinLocation != -1) {
        pinnedPieces[arrayIndex++] = pinLocation;
    }

    //  Check squares down right
    pinLocation = calculatePin(color, std::min(limitRight, limitDown), 9, kingLocation, 'b');
    if (pinLocation != -1) {
        pinnedPieces[arrayIndex++] = pinLocation;
    }

    //  Check squares down left
    pinLocation = calculatePin(color, std::min(limitLeft, limitDown), 7, kingLocation, 'b');
    if (pinLocation != -1) {
        pinnedPieces[arrayIndex++] = pinLocation;
    }
    
    return pinnedPieces;
}
int Board::calculatePin(bool color, int limit, int increment, int initialPos, char validPinner) {
    int pinnedLocation = -1;

    bool possiblePin = false;
    for (int i = 1; i < limit; i++) {
        int tile = initialPos + (i * increment);
        if (m_board[tile] == ' ') {
            continue;
        } else if (!isOpponentPiece(m_board[tile], color)) {
            if (possiblePin) {
                //  No pin
                possiblePin = false;
                break;
            }
            pinnedLocation = tile;
            possiblePin = true;
            continue;
        } else {
            if (possiblePin) {
                char enemyPiece = std::tolower(m_board[tile]);
                if (enemyPiece == 'q') {
                    //  Pin
                    return pinnedLocation;
                } else if (enemyPiece == validPinner) {
                    //  Pin
                    return pinnedLocation;
                } else {
                    //  No pin
                    break;
                }
            } else {
                //  No pin
                break;
            }
        }
    }
    //  No pin returned
    return -1;
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
void Board::generateBlockMask(bool color, int checkLocation) {
    int kingLocation = color ? kingPositionWhite : kingPositionBlack;
    char checkPiece = std::tolower(m_board[checkLocation]);

    int x0 = getXCoord(kingLocation);
    int y0 = getYCoord(kingLocation);
    int x1 = getXCoord(checkLocation);
    int y1 = getYCoord(checkLocation);

    int delx = x1 - x0;
    int dely = y1 - y0;
    if (checkPiece == 'q') {
        //  Determine if queen is checking horizontally/vertically or diagonally
        if (std::abs(delx) == std::abs(dely)) {
            //  This would only be true if the queen was checking diagonally
            //  like a bishop
            checkPiece = 'b';
        } else {
            checkPiece = 'r';
        }
    }
    switch (checkPiece) {
        case 'n': {
            return;
        }
        case 'b': {
            //  Iterate through the squares along the diagonal
            int limit = std::max(std::abs(delx), std::abs(dely));
            //  Decides along which diagonal it is
            int horizontalModifier = (delx < 0) ? -1 : 1;
            int verticalModifier = (dely < 0) ? -8 : 8;

            for (int i = 1; i < limit; i++) {
                int tile = kingLocation + (i * (horizontalModifier + verticalModifier));
                m_blockMask[tile] = true;
            }
            break;
        }
        case 'r': {
            //  Iterate through the squares between the checing piece and the
            //  king piece
            int limit = std::max(std::abs(delx), std::abs(dely));
            //  Columns differ by 1, rows by 8 in terms of index
            int orientation = (delx == 0) ? 8 : 1;
            //  If either of the deltas are negative, the modifier is negative
            int modifier = ((delx < 0) || (dely < 0)) ? -1 : 1;
            
            for (int i = 1; i < limit; i++) {
                int tile = kingLocation + (i * orientation * modifier);
                m_blockMask[tile] = true;
            }
            break;
        }
    }

}
std::array<std::vector<int>, 64> Board::getPossibleMoves(bool color) {
    std::array<std::vector<int>, 64> possibleMoves;
    //  The masks should be true if no check is present
    m_blockMask.fill(true);
    m_captureMask.fill(true);

    //  Determine if king is in check
    int kingPosition = color ? kingPositionWhite : kingPositionBlack;
    bool check = isInCheck(kingPosition);
    //  Tracks the position of pieces checking the king
    std::array<int, 2> checkLocations;

    bool doubleCheck = false;
    if (check) {
        checkLocations = getCheckLocations(color);
        //  Determine if a capture mask can be used
        //  If a king is in double check, a capture/block mask can not be used and the king must move
        if (checkLocations[1] == -1) {
            //  Single check
            //  Generate capture and block mask
            m_captureMask.fill(false);
            m_blockMask.fill(false);
            
            int captureLocation = checkLocations[0];
            m_captureMask[captureLocation] = true;

            generateBlockMask(color, captureLocation);
        } else {
            //  Double check
            doubleCheck = true;
        }
    }
    //  Check for pins
    std::array<int, 8> pinnedPieces = getPinnedPieces(color);

    //  Check each piece
    for (int i = 0; i < NUM_TILES; i++) {
        if (m_board[i] == ' ') {continue;}
        if (isOpponentPiece(m_board[i], color)) {continue;}

        int position = i;
        char piece = std::tolower(m_board[i]);
        switch (piece) {
            case 'r': {
                if (doubleCheck) {break;}
                possibleMoves[position] = getStraightLineMoves(position, color, MAX_RANGE, MOVEMENT);
                break; 
            }      
            case 'q': {
                if (doubleCheck) {break;}
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
                if (doubleCheck) {break;}
                possibleMoves[position] = getKnightMoves(position, color, MOVEMENT);
                break;
            }
            case 'b': {
                if (doubleCheck) {break;}
                possibleMoves[position] = getDiagonalMoves(position, color, MAX_RANGE, MOVEMENT);
                break;
            }
            case 'p': {
                if (doubleCheck) {break;}
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