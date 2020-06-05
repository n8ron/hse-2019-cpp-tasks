all: hw_03 test_hw_03

CXX = g++ 
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -Werror

obj:
	mkdir obj;

hw_03: obj/main.o obj/bin_manip.o obj/HuffmanArchiver.o obj/Huffman.o obj/CLI.o 
	$(CXX)  $(CXXFLAGS) obj/main.o obj/HuffmanArchiver.o obj/bin_manip.o obj/Huffman.o obj/CLI.o -o hw_03

obj/main.o: src/main.cpp include/HuffmanArchiver.h  include/bin_manip.h include/CLI.h | obj
	$(CXX) $(CXXFLAGS) -c -Iinclude src/main.cpp -o obj/main.o

obj/HuffmanArchiver.o: src/HuffmanArchiver.cpp include/HuffmanArchiver.h include/bin_manip.h include/Huffman.h | obj
	$(CXX) $(CXXFLAGS) -c -Iinclude src/HuffmanArchiver.cpp -o obj/HuffmanArchiver.o

obj/bin_manip.o: src/bin_manip.cpp include/bin_manip.h | obj
	$(CXX) $(CXXFLAGS)  -c -Iinclude src/bin_manip.cpp -o obj/bin_manip.o

obj/Huffman.o: src/Huffman.cpp include/Huffman.h | obj
	$(CXX) $(CXXFLAGS)  -c -Iinclude src/Huffman.cpp -o obj/Huffman.o

obj/CLI.o: src/CLI.cpp include/CLI.h | obj
	$(CXX) $(CXXFLAGS)  -c -Iinclude src/CLI.cpp -o obj/CLI.o

test_hw_03: obj/TestMain.o obj/TestTree.o obj/Huffman.o obj/bin_manip.o  obj/HuffmanArchiver.o obj/TestArchiver.o obj/TestCli.o | obj
	$(CXX) $(CXXFLAGS) obj/TestMain.o obj/TestTree.o obj/TestCli.o obj/Huffman.o obj/HuffmanArchiver.o obj/TestArchiver.o obj/CLI.o obj/bin_manip.o -o test_hw_03

obj/TestMain.o: test/TestMain.cpp test/doctest.h | obj
	$(CXX) $(CXXFLAGS)  -c -Iinclude test/TestMain.cpp -o obj/TestMain.o

obj/TestTree.o: test/TestTree.cpp test/doctest.h include/Huffman.h | obj
	$(CXX) $(CXXFLAGS) -c -Iinclude test/TestTree.cpp -o obj/TestTree.o

obj/TestArchiver.o: test/TestArchiver.cpp test/doctest.h include/bin_manip.h include/HuffmanArchiver.h | obj
	$(CXX) $(CXXFLAGS) -c -Iinclude test/TestArchiver.cpp -o obj/TestArchiver.o

obj/TestCli.o: test/TestCli.cpp test/doctest.h include/CLI.h | obj
	$(CXX) $(CXXFLAGS) -c -Iinclude test/TestCli.cpp -o obj/TestCli.o
clean:
	rm -f hw_03 test_hw_03
	rm -Rf obj/
