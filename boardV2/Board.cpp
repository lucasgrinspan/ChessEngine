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
bool Board::withinBounds(int x, int y) {
    //  Checks if x and y are in the 8x8 board
    return (x >= 0) && (x <= 7) && (y >= 0) && (y <= 7);
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
std::vector<int> Board::getStraightLineMoves(int tileNumber, bool color, int range) {
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
        } else if (isWhite(m_board[tile]) != color) {
            possibleMoves.push_back(tile);
            break;
        } else {
            break;
        }
    }
    //  Iterate over squares to the left
    for (int j = 1; j < std::min(limitLeft, range); j++) {
        int tile = tileNumber - j;
        if (m_board[tile] == ' ') {
            possibleMoves.push_back(tile);
            continue;
        } else if (isWhite(m_board[tile]) != color) {
            possibleMoves.push_back(tile);
            break;
        } else {
            break;
        }
    }
    //  Iterate over squares above
    for (int j = 1; j < std::min(limitUp, range); j++) {
        int tile = tileNumber - (j * 8);
        if (m_board[tile] == ' ') {
            possibleMoves.push_back(tile);
            continue;
        } else if (isWhite(m_board[tile]) != color) {
            possibleMoves.push_back(tile);
            break;
        } else {
            break;
        }
    }
    //  Iterate over squares below
    for (int j = 1; j < std::min(limitDown, range); j++) {
        int tile = tileNumber + (j * 8);
        if (m_board[tile] == ' ') {
            possibleMoves.push_back(tile);
            continue;
        } else if (isWhite(m_board[tile]) != color) {
            possibleMoves.push_back(tile);
            break;
        } else {
            break;
        }
    }
    return possibleMoves;
}
std::vector<int> Board::getDiagonalMoves(int tileNumber, bool color, int range) {
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
        } else if (isWhite(m_board[tile]) != color) {
            possibleMoves.push_back(tile);
            break;
        } else {
            break;
        }
    }
    //  Iterate diagonal up left
    for (int j = 1; j < std::min(limitUpLeft, range); j++) {
        //  Subtracting 9 gives you the tile up and to the left
        int tile = tileNumber - (7 * j);
        if (m_board[tile] == ' ') {
            possibleMoves.push_back(tile);
            continue;
        } else if (isWhite(m_board[tile]) != color) {
            possibleMoves.push_back(tile);
            break;
        } else {
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
        } else if (isWhite(m_board[tile]) != color) {
            possibleMoves.push_back(tile);
            break;
        } else {
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
        } else if (isWhite(m_board[tile]) != color) {
            possibleMoves.push_back(tile);
            break;
        } else {
            break;
        }
    }
    return possibleMoves;
}
std::vector<int> Board::getKnightMoves(int tileNumber, bool color) {
    
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
            }
            if (isWhite(m_board[tile]) != color) {
                possibleMoves.push_back(tile);
            }
        }
    }
    return possibleMoves;
}
std::vector<int> Board::getPawnMoves(int tileNumber, bool color) {
    std::vector<int> possibleMoves;

    int modifier = color ? -1 : 1;
    int startingRow = color ? 6 : 1;

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
    return possibleMoves;
}
std::array<std::vector<int>, 64> Board::getPossibleMoves() {
    std::array<std::vector<int>, 64> possibleMoves;
    for (int i = 0; i < NUM_TILES; i++) {
        if (m_board[i] == ' ') {continue;}

        int position = i;
        char piece = std::tolower(m_board[i]);
        bool color = isWhite(m_board[i]);
        switch (piece) {
            case 'r': {
                possibleMoves[position] = getStraightLineMoves(position, color, MAX_RANGE);
                break; 
            }      
            case 'q': {
                possibleMoves[position] = getStraightLineMoves(position, color, MAX_RANGE);
                //  Insert diagonal moves
                std::vector<int> diagonalMoves = getDiagonalMoves(position, color, MAX_RANGE);
                possibleMoves[position].insert(possibleMoves[position].end(), 
                                               diagonalMoves.begin(), 
                                               diagonalMoves.end());
                break;
            }
            case 'k': {
                possibleMoves[position] = getStraightLineMoves(position, color, KING_RANGE);
                //  Insert diagonal moves
                std::vector<int> diagonalMoves = getDiagonalMoves(position, color, KING_RANGE);
                possibleMoves[position].insert(possibleMoves[position].end(), 
                                               diagonalMoves.begin(), 
                                               diagonalMoves.end());
                break;
            }
            case 'n': {
                
                possibleMoves[position] = getKnightMoves(position, color);
                break;
            }
            case 'b': {
                possibleMoves[position] = getDiagonalMoves(position, color, MAX_RANGE);
                break;
            }
            case 'p': {
                possibleMoves[position] = getPawnMoves(position, color);
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