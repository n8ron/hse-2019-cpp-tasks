all: lab2

lab2: obj/test.o obj/test_str.o obj/str.o 
	gcc -o lab2 obj/test.o obj/test_str.o obj/str.o
obj:
	mkdir obj 
clean:
	rm  lab2 -Rf obj

obj/test.o: src/test.c | obj
	gcc -o obj/test.o -c -Iinclude src/test.c -Wall -Wextra -Werror
obj/test_str.o: src/test_str.c | obj
	gcc -o obj/test_str.o -c -Iinclude src/test_str.c -Wall -Wextra -Werror
obj/str.o: src/str.c | obj
	gcc -o obj/str.o -c -Iinclude src/str.c -Wall -Wextra -Werror
.PHONY: all clean
