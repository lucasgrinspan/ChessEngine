FLAGS = -std=c++11 -Wall -c
WARNINGS = -std=c++11 -Wall
all: program

program: main.o Board.o Pieces.o
	g++ -std=c++11 Main.o Board.o Bishop.o King.o Knight.o Pawn.o Queen.o Rook.o -o program

main.o: main.cpp
	g++ $(FLAGS) main.cpp

Board.o: Board.cpp
	g++ $(FLAGS) Board.cpp

Pieces.o: Pieces/Pawn.cpp Pieces/Rook.cpp Pieces/Bishop.cpp Pieces/Knight.cpp Pieces/Queen.cpp Pieces/King.cpp
	g++ $(FLAGS) Pieces/Pawn.cpp Pieces/Rook.cpp Pieces/Bishop.cpp Pieces/Knight.cpp Pieces/Queen.cpp Pieces/King.cpp

clean:
	rm -rf *o program