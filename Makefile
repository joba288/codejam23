CFLAGS=-O2 -Wall
SRCS = $(wildcard src/*.cpp)
build:	
	g++ -static $(SRCS) -o main.exe $(CFLAGS) 	\
	-I ./include/ -L ./lib/ 		\
	-lraylib -lopengl32 -lgdi32 -lwinmm
# copied the entire thing for now
build-linux:
	x86_64-w64-mingw32-g++-win32 -static $(SRCS) -o main.exe $(CFLAGS) 	\
	-I ./include/ -L ./lib/ 		\
	-lraylib -lopengl32 -lgdi32 -lwinmm
run: build
	./main.exe
run-linux: build-linux
	wine ./main.exe
