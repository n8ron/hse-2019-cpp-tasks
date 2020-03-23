#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>

namespace lab_13 {

template<typename T, size_t N>
class my_array final {
public:
    constexpr T& at(size_t index);

    constexpr const T& at(size_t index) const;

    constexpr T& operator[](size_t index);

    constexpr const T& operator[](size_t index) const;

    constexpr bool empty() const noexcept;

    constexpr size_t size() const noexcept;

    constexpr void fill(const T& val);

private:
    T data_[N];
};

template<std::size_t N>
class my_array<bool, N> final {
private:
    unsigned char data_[N / 8 + ((N % 8 == 0) ? 0 : 1)];
    struct array_bool_proxy {
        unsigned char* data_;
        unsigned int bit_;
        constexpr array_bool_proxy (unsigned char* _data, size_t _index) noexcept : data_(_data), bit_(_index) {}

        constexpr array_bool_proxy& operator= (bool x) noexcept; 

        constexpr array_bool_proxy& operator= (const array_bool_proxy& x) noexcept;

        constexpr array_bool_proxy& operator= (array_bool_proxy&& x) noexcept;

        constexpr operator bool() const;
    };

public:
    constexpr array_bool_proxy at(size_t index);

    constexpr bool at(size_t index) const;

    constexpr bool empty() const noexcept;

    constexpr size_t size() const noexcept;
    
    constexpr bool operator[] (size_t index) const noexcept;

    constexpr array_bool_proxy operator[] (size_t index) noexcept;

    constexpr void fill(bool val) noexcept;
};
}  // namespace lab_13
#include "my_array_impl.h"

#endif  // MY_ARRAY_H_