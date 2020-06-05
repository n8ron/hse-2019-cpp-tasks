#include "HuffmanArchiver.h"
#include "bin_manip.h"
#include <assert.h>
#include <memory>

namespace huffman_archiver {

std::ostream& operator<<(std::ostream& out, const std::vector<int32_t>& frequency) {
    for (int32_t i = 0; i < MAX_CODE; i++) {
        out << bin_manip::write_le_int32(frequency[i]); 
    }
    return out;
}

std::istream& operator>>(std::istream& in, std::vector<int32_t>& frequency) {
    for (int32_t i = 0; i < MAX_CODE; i++) { 
        in >> bin_manip::read_le_int32(frequency[i]);
    }
    return in;
}


size_t BitWriter::get_written_text_size() const noexcept {
    return numb_of_written_byte;
}

void BitWriter::write_bit(bool bit) {
    byte |= bit << last_bit;
    last_bit--;
    if (last_bit == -1) {
        out.write(&byte, 1);
        byte = 0;
        numb_of_written_byte++;
        last_bit = CHAR_BIT - 1;
    }
}

void BitWriter::write_byte() {
    if (last_bit == 7) {
        return;
    }
    for (; last_bit >= 0; last_bit--) {
        byte |= (1u << last_bit);
    }
    out.write(&byte, 1);
    byte = 0;
    numb_of_written_byte++;
    last_bit = CHAR_BIT - 1;
}

size_t BitReader::get_read_text_size() const noexcept {
    return numb_of_read_byte;
}

bool BitReader::read_bit() {
    if (last_bit == -1) {
        in.read(&byte, 1);
        numb_of_read_byte++;
        last_bit = CHAR_BIT - 1;
    }
    return (byte >> last_bit--) & 1u;    
}

void HuffmanArchiver::write_encoded_text(int32_t total_char_numb,
                                         std::vector<std::vector<bool>>& symbol_to_codes) {
    for (int32_t cur_char_numb = 0; cur_char_numb < total_char_numb; cur_char_numb++) {
        char ch1;
        in.read(&ch1, 1);
        for (auto cur_bit : symbol_to_codes[static_cast<unsigned char>(ch1)]) {
            writer.write_bit(cur_bit);
        }
    }
    writer.write_byte();
    stat.output_size = writer.get_written_text_size();
}

void HuffmanArchiver::write_decoded_text(int32_t total_char_numb, 
                                         huffman_tree::HuffmanTree& tree) {
    for (int32_t cur_char_numb = 0; cur_char_numb < total_char_numb; cur_char_numb++) {
        huffman_tree::HuffmanNode* cur_node = &tree.get_root();
        do {
            bool bit = reader.read_bit();
            if (!cur_node->is_leaf()) {
                if (bit) {
                    cur_node = &cur_node->get_right();    
                }
                else {
                    cur_node = &cur_node->get_left(); 
                }  
            }            
        } while (!cur_node->is_leaf());
        char ch = static_cast<char>(cur_node->get_symbol());
        out.write(&ch, 1);
        stat.output_size++;
    }
    stat.input_size = reader.get_read_text_size();
}

HuffmanStat HuffmanArchiver::compress() {
    in.clear();
    in.seekg(0, in.beg);
    char byte;
    std::vector<int32_t> symbol_to_frequency(MAX_CODE, 0);
    while (in.peek() != EOF) {
        in.read(&byte, 1);
        symbol_to_frequency[static_cast<unsigned char>(byte)]++;
        stat.input_size++;
    }
    in.clear();
    in.seekg(0, in.beg);
    out << bin_manip::write_le_int32(stat.input_size);
    if (stat.input_size == 0) {
        stat.table_size = 4;
        return stat;
    }
    huffman_tree::HuffmanTree tree(symbol_to_frequency); 
    std::vector<std::vector<bool>> symbol_to_codes = tree.get_codes(); 
    out << symbol_to_frequency;
    write_encoded_text(stat.input_size, symbol_to_codes);
    return stat;
}

HuffmanStat HuffmanArchiver::extract() {
    int32_t total_char_numb;
    in >> bin_manip::read_le_int32(total_char_numb);
    if (total_char_numb == 0) {
        stat.table_size = 4;
        return stat;
    }
    in >> symbol_to_frequency;
    huffman_tree::HuffmanTree tree(symbol_to_frequency);
    write_decoded_text(total_char_numb, tree);   
    return stat;
}

std::ostream& operator<<(std::ostream& os, const HuffmanStat & stat) {
    os << stat.input_size << '\n';
    os << stat.output_size << '\n';
    os << stat.table_size << '\n';
    return os;
} 

}
