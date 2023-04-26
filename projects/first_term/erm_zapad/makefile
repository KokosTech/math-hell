CC=g++
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c++20 
SRC=src
OBJ=obj
BIN=bin

all: cez

checker.o: $(SRC)/Checker/Checker.cpp $(SRC)/Checker/Checker.hpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(SRC)/Checker/Checker.cpp -o $(OBJ)/checker.o

matrix.o: $(SRC)/Matrix/Matrix.cpp $(SRC)/Matrix/Matrix.hpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(SRC)/Matrix/Matrix.cpp -o $(OBJ)/matrix.o

main.o: $(SRC)/main.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

cez: checker.o matrix.o main.o
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(OBJ)/checker.o $(OBJ)/matrix.o $(OBJ)/main.o -o $(BIN)/cez.out

clean:
	find . -type f -name '*.o' -exec rm {} +
	find . -type f -name '*.dSYM' -exec rm -r {} +
	find . -type f -name '*.out' -exec rm {} +
	find . -type f -name '*.exe' -exec rm {} +
	rm -rf obj
	rm -rf bin
