C=clang++
FLAGS=-std=c++1y -stdlib=libc++ -c -g -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function	#flags for compiler (turns .c files into .o files
LDFLAGS=-std=c++1y -stdlib=libc++ -lc++abi	#flags for linker (grabs .o files and links them)

all: main.o graph.o airport.o route.o fileio.o BFS.o Djikstra.o cs225.a Image.o StickerSheet.o shortestPathVisualizer.o
	$(C) $(LDFLAGS) main.o graph.o airport.o route.o fileio.o BFS.o Djikstra.o cs225.a Image.o StickerSheet.o shortestPathVisualizer.o -o main

test: test.o graph.o airport.o route.o fileio.o BFS.o Djikstra.o cs225.a Image.o StickerSheet.o shortestPathVisualizer.o catchmain.o
	$(C) $(LDFLAGS) test.o graph.o airport.o route.o fileio.o BFS.o Djikstra.o cs225.a Image.o StickerSheet.o shortestPathVisualizer.o catchmain.o -o test

main.o: main.cpp
	$(C) $(FLAGS) main.cpp

catchmain.o: drawUtils/cs225/catch/catchmain.cpp
	$(C) $(FLAGS) drawUtils/cs225/catch/catchmain.cpp

test.o: test.cpp
	$(C) $(FLAGS) test.cpp

graph.o: graph.cpp
	$(C) $(FLAGS) graph.cpp

airport.o: airport.cpp
	$(C) $(FLAGS) airport.cpp

route.o: route.cpp
	$(C) $(FLAGS) route.cpp

fileio.o: fileio.cpp
	$(C) $(FLAGS) fileio.cpp

BFS.o: BFS.cpp
	$(C) $(FLAGS) BFS.cpp

Djikstra.o: Djikstra.cpp
	$(C) $(FLAGS) Djikstra.cpp

#all the cs225 stuff is in one archive file because that won't change no matter what
cs225.a: drawUtils/cs225/lodepng/lodepng.cpp drawUtils/cs225/PNG.cpp drawUtils/cs225/HSLAPixel.cpp
	$(C) $(FLAGS) drawUtils/cs225/lodepng/lodepng.cpp drawUtils/cs225/PNG.cpp drawUtils/cs225/HSLAPixel.cpp
	ar cr cs225.a lodepng.o PNG.o HSLAPixel.o

Image.o: drawUtils/Image.cpp
	$(C) $(FLAGS) drawUtils/Image.cpp

StickerSheet.o: drawUtils/StickerSheet.cpp
	$(C) $(FLAGS) drawUtils/StickerSheet.cpp

shortestPathVisualizer.o: shortestPathVisualizer.cpp
	$(C) $(FLAGS) shortestPathVisualizer.cpp

clean:
	rm -f *.o
	rm cs225.a
	rm main
	rm test
