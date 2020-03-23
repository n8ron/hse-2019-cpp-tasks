all: lab13 smoke

lab13: obj/main.o
	g++ -std=c++17 -o lab13 obj/main.o -g 
smoke: obj/smoke_compiler.o
	g++ -std=c++17 -o smoke obj/smoke_compiler.o -g

obj:
	mkdir obj 
clean:
	rm  lab13 smoke -R obj

obj/main.o: src/main.cpp include/my_array.h include/my_array_impl.h | obj
	g++  -std=c++17 -o obj/main.o  -c -g -Iinclude src/main.cpp -Wall -Wextra -Werror

obj/smoke_compiler.o: src/smoke_compiler.cpp include/my_array.h include/my_array_impl.h | obj
	g++  -std=c++17 -o obj/smoke_compiler.o  -c -g -Iinclude src/smoke_compiler.cpp -Wall -Wextra -Werror

.PHONY: all clean

