#include "bin_manip.h"
#include <cstring>

write_le_int32::write_le_int32(const int32_t& n) : _n(n){}

std::basic_ostream<char> & operator<<(std::basic_ostream<char> & ofs, const write_le_int32 & wlei32) {
    return wlei32(ofs);
}

std::basic_ostream<char> & write_le_int32::operator()(std::basic_ostream<char> & ofs) const {
    char byte;
    for (int i = 0; i < 4; i++) {
        byte = (_n >> i * 8) & 255;
        ofs.write(&byte, 1);
    }
    return ofs;
}

read_le_int32::read_le_int32(std::int32_t & n) : _n(n) {}

std::basic_istream<char> & operator>>(std::basic_istream<char> & ifs, const read_le_int32  rlei32) {
    return rlei32(ifs);
}

std::basic_istream<char> & read_le_int32::operator()(std::basic_istream<char>  & ifs) const {
    _n = 0;
    char byte;
    for (int i = 0; i < 4; i++) {
        byte = 0;
        ifs.read(&byte, 1);
        _n |= int32_t((unsigned char)byte) << i * 8;
    }
    return ifs;
}

read_bool::read_bool(bool & b) : _b(b) {}

std::basic_istream<char>  & operator>>(std::basic_istream<char> & ifs, const read_bool & rb) {
    return rb(ifs);
}

std::basic_istream<char> & read_bool::operator()(std::basic_istream<char>  & ifs) const {
    char byte;
    ifs.read(&byte, 1);
    _b = static_cast<bool>(byte);
    return ifs;
}

write_bool::write_bool(const bool & b) : _b(b) {}

std::basic_ostream<char>& operator<<(std::basic_ostream<char> & ofs, const write_bool & wb) {
    return wb(ofs);
}

std::basic_ostream<char> & write_bool::operator()(std::basic_ostream<char> & ofs) const {
    char byte = _b;
    ofs.write(&byte, 1);
    return ofs;
}

write_c_str::write_c_str(char * const str) : _str(str) {}

std::basic_ostream<char>& operator<<(std::basic_ostream<char> & ofs, const write_c_str & wstr) {
    return wstr(ofs);
}

std::basic_ostream<char> & write_c_str::operator()(std::basic_ostream<char> & ofs) const {
    ofs.write(_str, strlen(_str) + 1);
    return ofs;
}

read_c_str::read_c_str(char * str, size_t size) : _str(str), _size(size) {}

std::basic_istream<char>& operator>>(std::basic_istream<char> & ifs, const read_c_str & rs) {
    return rs(ifs);
}

std::basic_istream<char> & read_c_str::operator()(std::basic_istream<char> & ifs) const {
    ifs.getline(_str, _size, 0);
    return ifs;
}