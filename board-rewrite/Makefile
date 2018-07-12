FLAGS = -std=c++11 -Wall -c
DEBUG = -g

all: program

program: main.o Board.o 
	g++ -std=c++11 main.o Board.o -o chess

main.o: main.cpp
	g++ $(FLAGS) main.cpp

Board.o: Board.cpp
	g++ $(FLAGS) Board.cpp

clean:
	rm -rf *o chess  $$ rm -f move-log.txt