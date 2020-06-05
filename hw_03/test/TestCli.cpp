#include "doctest.h"
#include "CLI.h"
#include <sstream>
#include <string>

using namespace cli;


TEST_CASE("Test normal input") {
    std::vector<std::string> s = {"./hw_03", "-c", "-f", "myfile.txt", "-o", "result.bin"};
    try {
        CLI h{s};
    }
    catch (const cli::ArgParseException& e){
        CHECK(false);
    }
    CLI h{s};
    CHECK(h.get_input_file() == "myfile.txt");
    CHECK(h.get_output_file() == "result.bin");
    CHECK(h.get_mode() == Mode::compress);
}

TEST_CASE("Test other normal input") {
    std::vector<std::string> s = {"./hw_03", "-c", "--file", "myfile.txt", "--output", "result.bin"};
    try {
        CLI h{s};
    }
    catch (const cli::ArgParseException& e){
        CHECK(false);
    }
    CLI h{s};
    CHECK(h.get_input_file() == "myfile.txt");
    CHECK(h.get_output_file() == "result.bin");
    CHECK(h.get_mode() == Mode::compress);
}

TEST_CASE("Test reverse input") {
    std::vector<std::string> s = {"./hw_03", "-u", "-o", "result.bin", "-f", "myfile.txt"};
    try {
        CLI h{s};
    }
    catch (const cli::ArgParseException& e){
        CHECK(false);
    }
    CLI h{s};
    CHECK(h.get_input_file() == "myfile.txt");
    CHECK(h.get_output_file() == "result.bin");
    CHECK(h.get_mode() == Mode::extract);
}

TEST_CASE("Test have not output") {
    std::vector<std::string> s = {"./hw_03", "-c", "-f", "result.bin", "-f", "myfile.txt"};
    try {
        CLI h{s};
    }
    catch (const cli::ArgParseException& e){
        std::string message = e.what();
        CHECK(message == "Do not have output file");
    }
}

TEST_CASE("Test have not input") {
    std::vector<std::string> s = {"./hw_03", "-c", "-o", "result.bin", "-o", "myfile.txt"};
    try {
        CLI h{s};
    }
    catch (const cli::ArgParseException& e){
        std::string message = e.what();
        CHECK(message == "Do not have input file");
    }
}

TEST_CASE("Test have not name") {
    std::vector<std::string> s = {"./hw_03", "-c", "-f", "result.bin", "-o"};
    try {
        CLI h{s};
    }
    catch (const cli::ArgParseException& e){
        std::string message = e.what();
        CHECK(message == "Do not have name of input file");
    }
}

TEST_CASE("Test incorrect command") {
    std::vector<std::string> s = {"./hw_03", "-csdfsd", "-f", "result.bin", "-o"};
    try {
        CLI h{s};
    }
    catch (const cli::ArgParseException& e){
        std::string message = e.what();
        CHECK(message == "Incorrect command");
    }
}

