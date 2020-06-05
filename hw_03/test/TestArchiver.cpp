#include "doctest.h"
#include "HuffmanArchiver.h"
#include "bin_manip.h"
#include <sstream>

using namespace huffman_archiver;

constexpr int32_t t_size = 4 * (MAX_CODE + 1);

TEST_CASE("Test constructor archiver") {
    std::stringstream in;
    std::stringstream out;
    HuffmanArchiver h(in, out);
}

TEST_CASE("Test compress empty") {
    std::stringstream in;
    std::stringstream out;
    HuffmanArchiver h(in, out);
    HuffmanStat stat = h.compress();
    CHECK(stat.input_size == 0);
    CHECK(stat.output_size == 0);
    CHECK(stat.table_size == 4);
    int32_t number;
    out >> bin_manip::read_le_int32(number);
    CHECK(number == 0);
    for (int32_t i = 0; i < 256; i++) {
        out >> bin_manip::read_le_int32(number);
        CHECK(number == 0);
    }
}

TEST_CASE("Test extract empty") {
    std::stringstream in;
    std::stringstream out;
    in << bin_manip::write_le_int32(0);
    for (int32_t i = 0; i < 256; i++) {
        in << bin_manip::write_le_int32(0);;
    }
    HuffmanArchiver h(in, out);
    HuffmanStat stat = h.extract();
    CHECK(stat.input_size == 0);
    CHECK(stat.output_size == 0);
    CHECK(stat.table_size == 4);
}

TEST_CASE("Test empty text") {
    std::stringstream in;
    std::stringstream bin_out;
    std::stringstream res_out;
    HuffmanArchiver hcompress(in, bin_out);
    HuffmanStat stat = hcompress.compress();
    CHECK(stat.input_size == 0);
    CHECK(stat.output_size == 0);
    CHECK(stat.table_size == 4);
    HuffmanArchiver hextract(bin_out, res_out);
    stat = hextract.extract();
    CHECK(stat.input_size == 0);
    CHECK(stat.output_size == 0);
    CHECK(stat.table_size == 4);
    CHECK(res_out.str().size() == 0);
}

TEST_CASE("Test text with 1 symbol") {
    std::stringstream in;
    std::stringstream bin_out;
    std::stringstream res_out;
    std::string test_string(40, 'a');

    in << test_string;

    HuffmanArchiver hcompress(in, bin_out);
    HuffmanStat stat = hcompress.compress();

    CHECK(stat.input_size == 40);
    CHECK(stat.output_size == 5);
    CHECK(stat.table_size == t_size);

    HuffmanArchiver hextract(bin_out, res_out);
    stat = hextract.extract();

    CHECK(stat.input_size == 5);
    CHECK(stat.output_size == 40);
    CHECK(stat.table_size == t_size);

    CHECK(res_out.str() == test_string);
}

TEST_CASE("Test random text without testing size") {
    std::stringstream in;
    std::stringstream bin_out;
    std::stringstream res_out;
    std::string test_string = "sdjfsjfbndskfjNJSDHJDS sdjfdsnf,sASDgdfgfdhkkFDSf  sdf sr SER Er C XCCC sdfsd hfghlk dfjksdfsdfds fdnfsdf sdf sdfsd for (int i = 0; i < sdfsdfndjfnds; ++i)";

    in << test_string;

    HuffmanArchiver hcompress(in, bin_out);
    HuffmanStat stat = hcompress.compress();

    HuffmanArchiver hextract(bin_out, res_out);
    stat = hextract.extract();

    CHECK(res_out.str() == test_string);
}

TEST_CASE("Test random text") {
    std::stringstream in;
    std::stringstream tmp_out;
    std::stringstream res_out;
    std::string test_string = " mdsnfmndkfdkgnasd sdfds";

    in << test_string;

    HuffmanArchiver hcompress(in, tmp_out);
    HuffmanStat stat = hcompress.compress();
    
    CHECK(stat.input_size == 24);
    CHECK(stat.output_size == 9);
    CHECK(stat.table_size == t_size);

    HuffmanArchiver hextract(tmp_out, res_out);
    stat = hextract.extract();

    CHECK(stat.input_size == 9);
    CHECK(stat.output_size == 24);
    CHECK(stat.table_size == t_size);

    CHECK(res_out.str() == test_string);
}


//----TESTBIT--------------------------
TEST_CASE("Test bitwriter") {
    std::stringstream out;
    BitWriter h(out);
    h.write_bit(0);
    h.write_bit(1);
    h.write_bit(1);
    h.write_bit(0);
    h.write_bit(1);
    h.write_bit(0);
    h.write_bit(1);
    CHECK(out.str() == "");
    CHECK(h.get_written_text_size() == 0);
    h.write_bit(1);
    CHECK(h.get_written_text_size() == 1);
    std::string res_out = " ";
    res_out[0] = static_cast<char>(107);
    CHECK(out.str() == res_out); 
}

TEST_CASE("Test bitwriter write_byte") {
    std::stringstream out;
    BitWriter h(out);
    h.write_bit(1);
    h.write_bit(0);
    h.write_bit(0);
    h.write_bit(1);
    CHECK(out.str() == "");
    CHECK(h.get_written_text_size() == 0);
    h.write_byte();
    CHECK(h.get_written_text_size() == 1);
    std::string res_out = " ";
    res_out[0] = static_cast<char>(159);
    CHECK(out.str() == res_out); 
}


TEST_CASE("Test bitreader") {
    std::stringstream in;
    BitReader h(in);
    in << "o";
    CHECK(h.get_read_text_size() == 0);
    std::vector<bool> bits;
    for (int i = 0; i < 8; i++) {
        bits.push_back(h.read_bit());
    }
    CHECK(bits == std::vector<bool> {0, 1, 1, 0, 1, 1, 1,1});
    CHECK(h.get_read_text_size() == 1);
}

