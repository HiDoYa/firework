OBJ = main.o
all: game

game: $(OBJ)
	g++ $(OBJ) -o fireworks.out -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./fireworks.out -g

main.o: main.cpp
	g++ -std=c++11 -c $<

# Battle.o: include/Battle.cpp
# 	g++ -std=c++11 -c $<

clean:
	rm *.o
