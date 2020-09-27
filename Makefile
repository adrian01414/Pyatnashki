all:
	gcc src/Source.c -o Source src/init.c src/swap.c src/load.c src/getRand.c -lSDL2
	gcc -Wall -Wextra -Wconversion -Wredundant-decls -Wshadow -Wno-unused-parameter test/main.c test/test.c src/init.c src/swap.c src/load.c src/getRand.c -lSDL2 -o tests
	

