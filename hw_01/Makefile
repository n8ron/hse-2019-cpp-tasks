all: hw_01

obj:
	mkdir obj 

hw_01: obj/main.o obj/bmp.o | obj
	gcc -g -o hw_01 obj/main.o obj/bmp.o  

clean:
	rm hw_01 -Rf obj

obj/main.o: src/main.c include/bmp.h  | obj
	gcc -g -o obj/main.o  -c -Iinclude src/main.c -Wall -Wextra -Werror
obj/bmp.o: src/bmp.c include/bmp.h  | obj
	gcc -g -o  obj/bmp.o  -c -Iinclude src/bmp.c -Wall -Wextra -Werror
.PHONY: all clean
