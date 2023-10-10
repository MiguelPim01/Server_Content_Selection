PROJ_NAME=main

CC=gcc
CFLAGS=-g -Wall

C_SOURCE=$(wildcard ./src/*/*.c)

H_SOURCE=$(wildcard ./headers/*.h)

OBJ=$(C_SOURCE:./headers/%.h=./objects/%.o)

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ) ./objects/main.o
	$(CC) -o $@ $^ $(CFLAGS)

./objects/%.o: ./src/*/%.c ./headers/%.h
	$(CC) -c -o $@ $< $(CFLAGS)

./objects/main.o: ./main.c $(H_SOURCE)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf ./objects/*.o $(PROJ_NAME)