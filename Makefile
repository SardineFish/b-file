all: CSI.o main.o
	g++ CSI.o main.o -o build/b-file
CSI.o: 
	g++ -c src/CSI.cpp -o CSI.o
main.o:
	g++ -c src/main.cpp -o main.o


debug: CSI-debug.o main-debug.o
	g++ -g main-debug.o CSI-debug.o -o build/b-file
CSI-debug.o:
	g++ -g -c src/CSI.cpp -o CSI-debug.o
main-debug.o:
	g++ -g -c src/main.cpp -o main-debug.o

clean:
	rm *.o