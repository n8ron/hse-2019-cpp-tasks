all: lab5

lab5: obj/main.o obj/clist.o obj/point_list.o
	gcc -o lab5 obj/main.o obj/clist.o obj/point_list.o  
obj:
	mkdir obj 
clean:
	rm  lab5 -R obj

obj/main.o: src/main.c include/clist.h include/point_list.h | obj
	gcc -o  obj/main.o  -c -Iinclude src/main.c -Wall -Wextra -Werror
obj/clist.o: src/clist.c include/clist.h include/point_list.h | obj
	gcc -o  obj/clist.o  -c -Iinclude src/clist.c -Wall -Wextra -Werror
obj/point_list.o: src/point_list.c include/clist.h include/point_list.h | obj
	gcc -o  obj/point_list.o  -c -Iinclude src/point_list.c -Wall -Wextra -Werror
.PHONY: all clean
