all: lab11

lab11: obj/main.o obj/bin_manip.o obj/employees.o
	g++ -std=c++17 -o lab11 obj/main.o obj/bin_manip.o obj/employees.o -g 
obj:
	mkdir obj 
clean:
	rm  lab11 -R obj

obj/main.o: src/main.cpp include/employees.h include/bin_manip.h | obj
	g++  -std=c++17 -o obj/main.o  -c -g -Iinclude src/main.cpp -Wall -Wextra -Werror
obj/bin_manip.o: src/bin_manip.cpp include/bin_manip.h include/employees.h | obj
	g++  -std=c++17 -o obj/bin_manip.o  -c -g  -Iinclude src/bin_manip.cpp -Wall -Wextra -Werror
obj/employees.o: src/employees.cpp include/employees.h include/bin_manip.h | obj
	g++  -std=c++17 -o obj/employees.o  -c -g -Iinclude src/employees.cpp -Wall -Wextra -Werror
.PHONY: all clean

