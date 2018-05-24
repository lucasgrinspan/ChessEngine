FLAGS = -std=c++11 -Wall -c
WARNINGS = -std=c++11 -Wall
all: program

program: main.o Board.o Pieces.o Evaluator.o
	g++ -std=c++11 Main.o Board.o Evaluator.o Bishop.o King.o Knight.o Pawn.o Queen.o Rook.o Blank.o -o program

main.o: main.cpp
	g++ $(FLAGS) main.cpp

Board.o: Board.cpp
	g++ $(FLAGS) Board.cpp

Pieces.o: Pieces/Pawn.cpp Pieces/Rook.cpp Pieces/Bishop.cpp Pieces/Knight.cpp Pieces/Queen.cpp Pieces/King.cpp Pieces/Blank.cpp
	g++ $(FLAGS) Pieces/Pawn.cpp Pieces/Rook.cpp Pieces/Bishop.cpp Pieces/Knight.cpp Pieces/Queen.cpp Pieces/King.cpp Pieces/Blank.cpp

Evaluator.o: Evaluator.cpp
	g++ $(FLAGS) Evaluator.cpp

clean:
	rm -rf *o program