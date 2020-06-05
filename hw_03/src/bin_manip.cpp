#include "bin_manip.h"
#include <cstring>
#include <cstdint>

namespace bin_manip {

write_le_int32::write_le_int32(const int32_t& n) : _n(n){}

std::ostream& operator<<(std::ostream& ofs, const write_le_int32& wlei32) {
    for (int i = 0; i < 4; i++) {
        char byte = (wlei32._n >> i * 8) & 255;
        ofs.write(&byte, 1);
    }
    return ofs;
}

read_le_int32::read_le_int32(std::int32_t & n) : _n(n) {}

std::istream& operator>>(std::istream& ifs, const read_le_int32& rlei32) {
    rlei32._n = 0;
    for (int i = 0; i < 4; i++) {
        char byte = 0;  
        ifs.read(&byte, 1);
        rlei32._n |= static_cast<int32_t>((static_cast<unsigned char>(byte))) << i * 8;
    }
    return ifs;
}

}
