all: CSI.o main.o
	g++ CSI.o main.o -o build/file-b

debug: CSI.o main.o file.o data.o
	g++ -g main.o CSI.o file.o data.o -o build/file-b.exe
CSI.o: src/CSI.cpp src/CSI.h
	g++ -g -c src/CSI.cpp -o CSI.o
main.o: src/main.cpp
	g++ -g -c src/main.cpp -o main.o
file.o: src/file.cpp data.o
	g++ -g -c src/file.cpp -o file.o
data.o: src/data.cpp
	g++ -g -c src/data.cpp -o data.o

clean:
	rm *.o

build/file-b:
	make debug

run: build/file-b
	./build/file-b