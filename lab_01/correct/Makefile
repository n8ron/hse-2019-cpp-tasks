all: lab1

lab1: bin/main.o bin/algorithm.o bin/io.o bin/util.o
	gcc -o lab1 bin/main.o bin/algorithm.o bin/io.o bin/util.o
bin:
	mkdir bin 
clean:
	rm  lab1 -Rf bin

bin/main.o: src/main.c | bin
	gcc -o bin/main.o -c -Iinclude src/main.c -Wall -Wextra -Werror
bin/algorithm.o: src/algorithm.c | bin
	gcc -o bin/algorithm.o -c -Iinclude src/algorithm.c -Wall -Wextra -Werror
bin/io.o: src/io.c | bin
	gcc -o bin/io.o -c -Iinclude src/io.c -Wall -Wextra -Werror
bin/util.o: src/util.c  | bin
	gcc -o bin/util.o -c -Iinclude src/util.c -Wall -Wextra -Werror
.PHONY: all clean
