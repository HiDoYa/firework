OBJ = main.o firework.o
all: game

game: $(OBJ)
	g++ $(OBJ) -o fireworks.out -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./fireworks.out -g

main.o: main.cpp
	g++ -std=c++14 -c $<

firework.o: include/Firework.cpp
	g++ -std=c++14 -c $<

clean:
	rm *.o
