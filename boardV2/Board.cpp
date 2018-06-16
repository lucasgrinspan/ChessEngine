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
void Board::printBoard() {
    for (int i = 0; i < NUM_TILES; i++) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << m_board[i] << " ";
    }
    std::cout << std::endl;
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
                //  Handle limits in horizontal direction
                int limitRight = BOARD_LENGTH - getXCoord(position);
                int limitLeft = getXCoord(position) + 1;
                int limitUp = getYCoord(position) + 1;
                int limitDown = BOARD_LENGTH - getYCoord(position);

                //  Iterate over squares to the right
                for (int j = 1; j < limitRight; j++) {
                    int tile = position + j;
                    if (m_board[tile] == ' ') {
                        possibleMoves[position].push_back(tile);
                        continue;
                    } else if (isWhite(m_board[tile]) != color) {
                        possibleMoves[position].push_back(tile);
                    } else {
                        break;
                    }
                }
                //  Iterate over squares to the left
                for (int j = 1; j < limitLeft; j++) {
                    int tile = position - j;
                    if (m_board[tile] == ' ') {
                        possibleMoves[position].push_back(tile);
                        continue;
                    } else if (isWhite(m_board[tile]) != color) {
                        possibleMoves[position].push_back(tile);
                    } else {
                        break;
                    }
                }
                //  Iterate over squares above
                for (int j = 1; j < limitUp; j++) {
                    int tile = position - (j * 8);
                    if (m_board[tile] == ' ') {
                        possibleMoves[position].push_back(tile);
                        continue;
                    } else if (isWhite(m_board[tile]) != color) {
                        possibleMoves[position].push_back(tile);
                    } else {
                        break;
                    }
                }
                //  Iterate over squares below
                for (int j = 1; j < limitUp; j++) {
                    int tile = position + (j * 8);
                    if (m_board[tile] == ' ') {
                        possibleMoves[position].push_back(tile);
                        continue;
                    } else if (isWhite(m_board[tile]) != color) {
                        possibleMoves[position].push_back(tile);
                    } else {
                        break;
                    }
                }
                break; 
            }      
            case 'q': {
                break;
            }
            case 'k': {
                break;
            }
            case 'n': {
            }
            case 'b': {
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