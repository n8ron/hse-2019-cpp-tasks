#ifndef MY_ARRAY_IMPL_H_
#define MY_ARRAY_IMPL_H_

#include "my_array.h"
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <assert.h>

namespace lab_13 {

template<typename T, size_t N>
constexpr T& my_array<T, N>::at(size_t index) {
    if (index >= N) {
        throw std::out_of_range ("Incorrect index");
    } 
    return data_[index];
}

template<typename T, size_t N>
constexpr const T& my_array<T, N>::at(size_t index) const {
    if (index >= N) {
        throw std::out_of_range ("Incorrect index");
    } 
    return data_[index];
}

template<typename T, size_t N>
constexpr T& my_array<T, N>::operator[](size_t index) {
    assert(index < N);
    return data_[index];
}

template<typename T, size_t N>
constexpr const T& my_array<T, N>::operator[](size_t index) const {
    assert(index < N);
    return data_[index];
}

template<typename T, size_t N>
constexpr bool my_array<T, N>::empty() const noexcept {
    return N == 0;
}

template<typename T, size_t N>
constexpr size_t my_array<T, N>::size() const noexcept {
    return N;
}

template<typename T, size_t N>
constexpr void my_array<T, N>::fill(const T& val) {
    for (size_t i = 0; i < N; i++) {
        data_[i] = val;
    }
}

//---------BOOL-----------------
template<size_t N>
constexpr auto my_array<bool, N>::at(size_t index) -> my_array::array_bool_proxy {
    if (index >= N) {
        throw std::out_of_range ("Incorrect index");
    } 
    return (*this)[index];
}

template<size_t N>
constexpr bool my_array<bool, N>::at(size_t index) const {
    if (index >= N) {
        throw std::out_of_range ("Incorrect index");
    } 
    return (*this)[index];
}

template<size_t N>
constexpr bool my_array<bool, N>::empty() const noexcept {
    return N == 0;
}

template<size_t N>
constexpr size_t my_array<bool, N>::size() const noexcept {
    return N;
}

template<size_t N>
constexpr bool my_array<bool, N>::operator[] (size_t index) const noexcept {
    assert(index < N);
    return data_[index / 7] & (1 << index);
} 

template<size_t N>
constexpr void my_array<bool, N>::fill(bool val) noexcept {
    memset(data_, 255 * val, N / 8 + ((N % 8 == 0) ? 0 : 1));
}

template<size_t N>
constexpr auto my_array<bool, N>::operator[] (size_t index) noexcept -> my_array::array_bool_proxy {
    assert(index < N);
    return array_bool_proxy(&data_[index / 7], index % 7);
}
//--------------PROXY--------------------------
template<size_t N>
constexpr auto my_array<bool, N>::array_bool_proxy::operator= (bool x) noexcept -> my_array::array_bool_proxy& {
    *data_ &= ~(1u << bit_);
    *data_ |= x << bit_;
    return *this;
}  

template<size_t N>
constexpr auto my_array<bool, N>::array_bool_proxy::operator= (const array_bool_proxy& x) noexcept -> my_array::array_bool_proxy& {
    *this = (*(x.data_) & (1u << x.bit_)) != 0;
    return *this;
}

template<size_t N>
constexpr auto my_array<bool, N>::array_bool_proxy::operator= (array_bool_proxy&& x) noexcept -> my_array::array_bool_proxy& {
    *this = (*(x.data_) & (1u << x.bit_)) != 0;
    return *this;
}

template<size_t N>
constexpr my_array<bool, N>::array_bool_proxy::operator bool() const {
    return *data_ & (1u << bit_);
}

}
#endif