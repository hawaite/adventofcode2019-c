.PHONY = clean build
.DEFAULT_GOAL := build

CC := gcc
FLAGS := -std=c11

bin/part1.out: part1.c
	mkdir -p bin
	$(CC) $(FLAGS) -o bin/part1.out part1.c

bin/part2.out: part2.c
	mkdir -p bin
	$(CC) $(FLAGS) -o bin/part2.out part2.c

build: bin/part1.out bin/part2.out

clean:
	rm -rf bin