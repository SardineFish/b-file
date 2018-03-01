all: CSI.o main.o
	g++ CSI.o main.o -o build/file-b
CSI.o: src/CSI.cpp src/CSI.h
	g++ -c src/CSI.cpp -o CSI.o
main.o: src/main.cpp
	g++ -c src/main.cpp -o main.o


debug: CSI-debug.o main-debug.o
	g++ -g main-debug.o CSI-debug.o -o build/file-b
CSI-debug.o: src/CSI.cpp src/CSI.h
	g++ -g -c src/CSI.cpp -o CSI-debug.o
main-debug.o: src/main.cpp
	g++ -g -c src/main.cpp -o main-debug.o

clean:
	rm *.o

build/file-b:
	make debug

run: build/file-b
	./build/file-b