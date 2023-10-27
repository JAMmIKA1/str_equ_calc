cc = gcc

build: *.c
	$(cc) *.c -o run
run: *.c
	$(cc) *.c -o run && ./run
debug: *.c
	$(cc) *.c -o debug -g -O0
