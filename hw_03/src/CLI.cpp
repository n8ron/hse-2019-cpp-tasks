#include "CLI.h"
#include <cstring>
#include <iostream>

namespace cli {

const std::string& CLI::get_input_file() const noexcept {
    return input_;
}
const std::string& CLI::get_output_file() const noexcept {
    return output_;
}

Mode CLI::get_mode() const noexcept {
    return mode_;
}

CLI::CLI(std::vector<std::string> command) {
    bool have_input_file = false;
    bool have_output_file = false;
    bool have_mode = false;
    for (size_t i = 1; i < command.size(); i++) {
        if (command[i] == "--file" || command[i] == "-f") {
            i++;
            have_input_file = true;
            if (i == command.size()) {
                throw ArgParseException("Do not have name of input file");
            }
            input_ = command[i];
        }
        else if (command[i] == "--output" || command[i] ==  "-o") {
            i++;
            have_output_file = true;
            if (i == command.size()) {
                throw ArgParseException("Do not have name of input file");
            }
            output_ = command[i];
        } 
        else if (command[i] ==  "-c") {
            if (have_mode) {
                throw ArgParseException("Mode is specified several times");
            }
            have_mode = true;
            mode_ =  Mode::compress;
        } 
        else if (command[i] ==  "-u") {
            if (have_mode) {
                throw ArgParseException("Mode is specified several times");
            }
            have_mode = true;
            mode_ =  Mode::extract;
        }
        else {
            throw ArgParseException("Incorrect command");
        }
    }
    if (!have_input_file) {
        throw ArgParseException("Do not have input file");
    }
    if (!have_output_file) {
        throw ArgParseException("Do not have output file");
    }
}

}