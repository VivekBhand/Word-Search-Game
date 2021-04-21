all: run
project: main.o puzzle_create.o trie.o solve.o entry.o
	cc main.o puzzle_create.o trie.o solve.o entry.o -o try
main.o: main.c puzzle_create.h
	cc -c main.c
puzzle_create.o: puzzle_create.c puzzle_create.h 
	cc -c puzzle_create.c
trie.o: trie.c trie.h
	cc -c trie.c
entry.o: entry.c entry.h puzzle_create.h
	cc -c entry.c
solve.o:  solve.c solve.h entry.h puzzle_create.h
	cc -c solve.c
run: project
	./try.exe
clean:
	rm *.o


