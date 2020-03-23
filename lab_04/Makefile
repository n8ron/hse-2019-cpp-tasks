all: lab4

lab4: obj/main.o obj/mergesort.o
	gcc -o lab4 obj/main.o obj/mergesort.o
obj:
	mkdir obj 
clean:
	rm  lab4 -Rf obj

obj/main.o: src/main.c include/mergesort.h | obj
	gcc -o obj/main.o -c -Iinclude src/main.c -Wall -Wextra -Werror
obj/mergesort.o: src/mergesort.c include/mergesort.h | obj
	gcc -o obj/mergesort.o -c -Iinclude src/mergesort.c -Wall -Wextra -Werror
.PHONY: all clean
