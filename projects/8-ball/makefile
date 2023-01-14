CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++20
SRC=src

all: main.o game.o table.o ball.o line.o vector.o point.o
	@mkdir -p bin
	$(CC) $(CFLAGS) obj/main.o obj/game.o obj/table.o obj/ball.o obj/line.o obj/vector.o obj/point.o -o bin/8-ball.out

main.o: $(SRC)/main.cpp
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $(SRC)/main.cpp -o obj/main.o

game.o: $(SRC)/game/Game.cpp
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $(SRC)/game/Game.cpp -o obj/game.o

table.o: $(SRC)/field/Field.cpp
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $(SRC)/field/Field.cpp -o obj/table.o

ball.o: $(SRC)/ball/Ball.cpp
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $(SRC)/ball/Ball.cpp -o obj/ball.o

line.o: $(SRC)/objects/Line.cpp
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $(SRC)/objects/line.cpp -o obj/line.o

vector.o: $(SRC)/objects/Vector.cpp
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $(SRC)/objects/vector.cpp -o obj/vector.o

point.o: $(SRC)/objects/Point.cpp
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $(SRC)/objects/point.cpp -o obj/point.o

clean:
	find . -type f -name '*.o' -exec rm {} +
	find . -type f -name '*.dSYM' -exec rm -r {} +
	find . -type f -name '*.out' -exec rm {} +
	find . -type f -name '*.exe' -exec rm {} +
	rm -rf obj