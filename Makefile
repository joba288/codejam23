CFLAGS=-O2 -Wall
build:
	gcc ./src/main.cpp -o main.exe $(CFLAGS) 	\
	-I ./include/ -L ./lib/ 		\
	-lraylib -lopengl32 -lgdi32 -lwinmm
run: build
	./main.exe
