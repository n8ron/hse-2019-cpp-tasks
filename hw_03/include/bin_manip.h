#ifndef BIN_MANIP_H_
#define BIN_MANIP_H_
#include <cstdio>
#include <fstream>

namespace bin_manip {

class write_le_int32 final {
public:
    explicit write_le_int32(const int32_t& n); 
    friend std::ostream& operator<<(std::ostream& ofs, const write_le_int32& wlei32);
private:
    int32_t _n;
};

class read_le_int32 final {
public:
    explicit read_le_int32(int32_t& n); 
    friend std::istream& operator>>(std::istream& ifs, const read_le_int32& rlei32);
private:
    int32_t & _n;
};

}
#endif