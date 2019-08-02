a.out: main.o draw.o init.o move.o util.o CPU1.o
	g++ -o a.out main.o draw.o init.o move.o util.o CPU1.o
main.o: main.cpp
	g++ -c main.cpp
draw.o: draw.cpp
	g++ -c draw.cpp
init.o: init.cpp
	g++ -c init.cpp
move.o: move.cpp
	g++ -c move.cpp
util.o: util.cpp
	g++ -c util.cpp
CPU1.o: CPU1.cpp
	g++ -c CPU1.cpp

clean:
	rm -f *.o a.out
