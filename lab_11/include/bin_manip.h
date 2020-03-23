#ifndef LAB11_BIN_MANIP_H_INCLUDED
#define LAB11_BIN_MANIP_H_INCLUDED
#include <cstdio>
#include <fstream>

class write_le_int32 final {
public:
    explicit write_le_int32(const int32_t &n); 
    std::basic_ostream<char> & operator()(std::basic_ostream<char> & ofs) const;
private:
    int32_t _n;
};

std::basic_ostream<char> & operator<<(std::basic_ostream<char> & ofs, const write_le_int32 & wlei32);

class read_le_int32 final {
public:
    explicit read_le_int32(int32_t &n); 
    std::basic_istream<char> & operator()(std::basic_istream<char>& ifs) const; 
private:
    int32_t & _n;
};

std::basic_istream<char> & operator>>(std::basic_istream<char>& ifs, const read_le_int32 rlei32);

class read_bool final {
public:
    explicit read_bool(bool & b);
    std::basic_istream<char>& operator()(std::basic_istream<char>& ifs) const; 
private:
    bool & _b;
};

std::basic_istream<char>& operator>>(std::basic_istream<char>& ifs, const read_bool & rb); 

class write_bool final {
public:
    explicit write_bool(const bool & b);
    std::basic_ostream<char> & operator()(std::basic_ostream<char> & ofs) const;
private:
    bool _b;
};

std::basic_ostream<char>& operator<<(std::basic_ostream<char> & ofs, const write_bool & wb);


class read_c_str final {
public:
    explicit read_c_str(char * str, size_t size);
    std::basic_istream<char> & operator()(std::basic_istream<char> & ifs) const;
private:
    char * _str;
    size_t _size;
};

std::basic_istream<char>& operator>>(std::basic_istream<char> & ifs, const read_c_str  & rs);

class write_c_str final {
public:
    explicit write_c_str(char * const str);
    std::basic_ostream<char> & operator()(std::basic_ostream<char> & ofs) const;
private:
    char * _str;
};

std::basic_ostream<char>& operator<<(std::basic_ostream<char> & ofs, const write_c_str  & ws);

#endif