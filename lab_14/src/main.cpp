#include <cstdio>
#include <iostream>
#include "matrix.h"

int main() {
    char reg_char;
    int register_first, register_second;
    int x, y;
    std::cout.exceptions(std::cout.failbit | std::cout.badbit);
    std::cin.exceptions(std::cin.failbit | std::cin.badbit);
    try {
        std::string command;
        std::string filename;
        MatrixArray cur_storage;
        while (true) {
            try {
                std::cin >> command;
                if (command == "load") {
                    std::cin >> reg_char >> register_first;
                    std::cin >> filename;
                    cur_storage.load(register_first, filename);
                }
                else if (command == "print") {
                    std::cin >> reg_char >> register_first;
                    cur_storage.print(register_first);
                }
                else if (command == "add") {
                    std::cin >> reg_char >> register_first;
                    std::cin >> reg_char >> register_second;
                    cur_storage.add(register_first, register_second);
                }
                else if (command == "mul") {
                    std::cin >> reg_char >> register_first;
                    std::cin >> reg_char >> register_second;
                    cur_storage.mul(register_first, register_second);
                }
                else if (command == "elem") {
                    std::cin >> reg_char >> register_first;
                    std::cin >> x >> y;
                    cur_storage.elem(register_first, x, y);
                }
                else if (command == "exit") {
                    break;
                }
                else {
                    std::cout << "Incorrect command!\n";
                }
            }
            catch (const MatrixException & exception) {
                std::cout << exception.message();
            }
            catch (const std::bad_alloc& e) {
                std::cout << "Unable to allocate memory.\n";
            }
        }
        return 0;
    }
    catch(std::ios_base::failure & fail) {
        return 1;
    }
}