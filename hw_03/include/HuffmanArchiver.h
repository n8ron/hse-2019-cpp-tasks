#ifndef HUFFMANARCHIVER_H_
#define HUFFMANARCHIVER_H_

#include "Huffman.h"
#include <istream>
#include <ostream>
#include <cstdint>

namespace huffman_archiver {

struct HuffmanStat final {
    size_t input_size = 0;
    size_t output_size = 0;
    size_t table_size = 4 * (MAX_CODE + 1);	
};

std::ostream& operator<<(std::ostream& os, const HuffmanStat & stat);

std::ostream& operator<<(std::ostream&, const std::vector<int32_t>&);
std::istream& operator>>(std::istream&, std::vector<int32_t>&);

class BitWriter final {
public:
    explicit BitWriter(std::ostream& os) : out(os) {}
    size_t get_written_text_size() const noexcept;
    void write_bit(bool bit);
    void write_byte();
private:
    char byte = 0;
    size_t numb_of_written_byte = 0;
    int32_t last_bit = CHAR_BIT - 1;
    std::ostream& out;
};

class BitReader final {
public:
    explicit BitReader(std::istream& input_stream) : in(input_stream) {}
    size_t get_read_text_size() const noexcept;
    bool read_bit();
private:
    char byte = 0;
    size_t numb_of_read_byte = 0;
    int32_t last_bit = -1;
    std::istream& in;    
};

class HuffmanArchiver final {
public:
    HuffmanArchiver(std::istream& input_stream, std::ostream& output_stream) : writer(output_stream)
                                                                               , reader(input_stream)
                                                                               , in(input_stream)
                                                                               , out(output_stream) {} 
    HuffmanStat compress(); 
    HuffmanStat extract();
private:
    HuffmanStat stat;
    BitWriter writer;
    BitReader reader;  
    void write_encoded_text(int32_t, std::vector<std::vector<bool>>&);
    void write_decoded_text(int32_t, huffman_tree::HuffmanTree&);  

    std::vector<int32_t> symbol_to_frequency = std::vector<int32_t>(MAX_CODE, 0);
    std::istream& in;
    std::ostream& out;
};

}

#endif
