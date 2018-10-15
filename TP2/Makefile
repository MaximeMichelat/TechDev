#CC=clang -g


all: main

main: alea.o io.o tri.o main.o
	$(CC) -o main main.o io.o tri.o alea.o -lm

main.o: main.c
	$(CC) -c main.c

io.o: io.c
	$(CC) -c io.c

tri.o: tri.c
	$(CC) -c tri.c

clean:
	rm -rf main *.o
