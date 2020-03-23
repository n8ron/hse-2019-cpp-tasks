all: lab12 

lab12: obj/main.o
	g++ -std=c++17 -o lab12 obj/main.o -g 
obj:
	mkdir obj 
clean:
	rm  lab12 -R obj

obj/main.o: src/main.cpp include/my_vector.h include/my_vector_impl.h | obj
	g++  -std=c++17 -o obj/main.o  -c -g -Iinclude src/main.cpp -Wall -Wextra -Werror

.PHONY: all clean

