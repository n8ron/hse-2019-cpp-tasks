all: hw_02 test_hw_02

hw_02: obj/main.o obj/Board.o obj/StdioBoardView.o obj/GameController.o obj/NcursesBoardView.o
	g++ -std=c++17 -o hw_02 obj/main.o obj/Board.o obj/StdioBoardView.o obj/GameController.o obj/NcursesBoardView.o -g -lncurses 

test_hw_02: obj/test.o obj/Board.o obj/BoardTest.o obj/Test.o
	g++ -std=c++17 -o test_hw_02 obj/test.o obj/Board.o obj/BoardTest.o obj/Test.o -g 

obj:
	mkdir obj 
clean:
	rm test_hw_02 hw_02 -R obj

obj/main.o: src/main.cpp include/Board.h include/BoardView.h  include/StdioBoardView.h  include/GameController.h | obj
	g++  -std=c++17 -o obj/main.o  -c -g -Iinclude src/main.cpp -Wall -Wextra -Werror -lncurses
obj/Board.o: src/Board.cpp include/Board.h include/BoardView.h include/StdioBoardView.h | obj
	g++  -std=c++17 -o obj/Board.o -c -g -Iinclude src/Board.cpp -Wall -Wextra -Werror -lncurses
obj/StdioBoardView.o: src/StdioBoardView.cpp include/Board.h include/BoardView.h include/StdioBoardView.h | obj
	g++  -std=c++17 -o obj/StdioBoardView.o -c -g -Iinclude src/StdioBoardView.cpp -Wall -Wextra -Werror -lncurses
obj/BoardTest.o: test/BoardTest.cpp include/BoardTest.h include/Board.h include/Test.h | obj
	g++  -std=c++17 -o obj/BoardTest.o -c -g -Iinclude test/BoardTest.cpp -Wall -Wextra -Werror
obj/test.o: test/test.cpp include/Board.h include/BoardTest.h include/Test.h | obj
	g++  -std=c++17 -o obj/test.o -c -g -Iinclude test/test.cpp -Wall -Wextra -Werror
obj/Test.o: test/Test.cpp include/Test.h include/Board.h include/BoardTest.h include/Test.h | obj
	g++  -std=c++17 -o obj/Test.o -c -g -Iinclude test/Test.cpp -Wall -Wextra -Werror
obj/GameController.o: src/GameController.cpp include/Board.h include/StdioBoardView.h include/BoardView.h | obj
	g++ -std=c++17 -o obj/GameController.o -c -g -Iinclude src/GameController.cpp -Wall -Wextra -Werror -lncurses
obj/NcursesBoardView.o: src/NcursesBoardView.cpp include/NcursesBoardView.h include/Board.h include/BoardView.h include/StdioBoardView.h | obj
	g++ -std=c++17 -o obj/NcursesBoardView.o -c -g -Iinclude src/NcursesBoardView.cpp -Wall -Wextra -Werror -lncurses

.PHONY: all clean

