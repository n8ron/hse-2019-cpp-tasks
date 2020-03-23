all: lab14

lab14: obj/main.o obj/matrix.o
	g++ -std=c++17 -o lab14 obj/main.o obj/matrix.o -g 
obj:
	mkdir obj 
clean:
	rm  lab14 -R obj

obj/main.o: src/main.cpp include/matrix.h | obj
	g++  -std=c++17 -o obj/main.o  -c -g -Iinclude src/main.cpp -Wall -Wextra -Werror
obj/matrix.o: src/matrix.cpp include/matrix.h | obj
	g++  -std=c++17 -o obj/matrix.o  -c -g  -Iinclude src/matrix.cpp -Wall -Wextra -Werror
.PHONY: all clean

