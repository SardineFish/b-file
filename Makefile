all: CSI.o main.o file.o data.o cli_mgr.o
	g++ --std=c++11 CSI.o main.o cli_mgr.o -o build/file-b

debug: CSI.o main.o file.o data.o cli_mgr.o
	g++ -g --std=c++11 main.o CSI.o file.o data.o cli_mgr.o -o build/file-b.exe

CSI.o: src/CSI.cpp src/CSI.h
	g++ -g -c --std=c++11 src/CSI.cpp -o CSI.o

main.o: src/main.cpp
	g++ -g -c --std=c++11 src/main.cpp -o main.o

file.o: src/file.cpp src/file.h data.o
	g++ -g -c --std=c++11 src/file.cpp -o file.o

data.o: src/data.cpp src/data.h
	g++ -g -c --std=c++11 src/data.cpp -o data.o

cli_mgr.o: src/cli_mgr.cpp src/cli_mgr.h
	g++ -g -c --std=c++11 src/cli_mgr.cpp -o cli_mgr.o

clean:
	rm *.o

build/file-b:
	make debug

run: build/file-b
	./build/file-b