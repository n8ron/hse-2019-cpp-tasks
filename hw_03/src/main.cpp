#include "HuffmanArchiver.h"
#include "CLI.h"
#include <fstream> 
#include <iostream> 

#include <vector>
#include <string>

int main(int argc, char const *argv[])
{
    std::vector<std::string> all_args;

    all_args.assign(argv, argv + argc);
    try {
        cli::CLI parser{all_args};
        std::ifstream in(parser.get_input_file(), std::ios::binary);
        std::ofstream out(parser.get_output_file(), std::ios::binary);
        huffman_archiver::HuffmanArchiver h(in, out);
        huffman_archiver::HuffmanStat cur_stat;
        if (parser.get_mode() == cli::Mode::compress) {
            cur_stat = h.compress();
        }
        else {
            cur_stat = h.extract();
        }
        std::cout << cur_stat;
    }
    catch(const cli::ArgParseException& e){
        std::cout << e.what() << '\n';
        return 1;
    } 
    return 0;
}