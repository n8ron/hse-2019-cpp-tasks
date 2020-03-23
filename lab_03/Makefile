all: lab3

lab3: obj/main.o obj/clist.o
	gcc -o lab3 obj/main.o obj/clist.o -I/usr/include/flite/ -lflite_cmu_us_kal -lflite_usenglish -lflite_cmulex -lflite -lm
obj:
	mkdir obj 
clean:
	rm  lab3 -Rf obj

obj/main.o: src/main.c include/clist.h | obj
	gcc -o obj/main.o -c -Iinclude src/main.c -Wall -Wextra -Werror -I/usr/include/flite/ -lflite_cmu_us_kal -lflite_usenglish -lflite_cmulex -lflite -lm

obj/clist.o: src/clist.c include/clist.h | obj
	gcc -o obj/clist.o -c -Iinclude src/clist.c -Wall -Wextra -Werror -I/usr/include/flite/ -lflite_cmu_us_kal -lflite_usenglish -lflite_cmulex -lflite -lm
.PHONY: all clean
