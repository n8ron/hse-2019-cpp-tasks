#ifndef MY_VECTOR_IMPL_H_
#define MY_VECTOR_IMPL_H_

#include <iostream>
#include "my_vector.h"

namespace my_vector {

//-------VectorImpl----------------------------------------------------------------
    template <typename T>
    my_vector<T>::my_vector_holder::my_vector_holder(size_t cap) 
        : array_((cap != 0) ? reinterpret_cast<T*>(new char[sizeof(T) * cap]) : nullptr)
        , capacity_(cap)
        , size_(0) {}

    template <typename T>
    my_vector<T>::my_vector_holder::~my_vector_holder() {
        for (; size_ > 0; size_--) {
            array_[size_ - 1].~T();
        }
        delete [] reinterpret_cast<char*> (array_);
    }

    template <typename T>
    void my_vector<T>::my_vector_holder::swap(my_vector_holder & other) noexcept { 
        std::swap(array_, other.array_);
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_); 
    }
//--------------------------------------------------------------------------------

    template <typename T>
    my_vector<T>::my_vector() noexcept : vector_impl_(my_vector_holder(0)) {}

    template <typename T>
    my_vector<T>::my_vector(std::size_t n) : vector_impl_(my_vector_holder(next_pow2(n))) {
        for (; vector_impl_.size_ < n; vector_impl_.size_++) {
            new (vector_impl_.array_ + vector_impl_.size_) T();
        }
    }
    
    template <typename T>
    my_vector<T>::my_vector(const my_vector & other) : vector_impl_(next_pow2(other.vector_impl_.size_)) {
        for (; vector_impl_.size_ < other.vector_impl_.size_; vector_impl_.size_++) {
            new (vector_impl_.array_ + vector_impl_.size_) T(other.vector_impl_.array_[vector_impl_.size_]);
        }
    }

    template <typename T>
    my_vector<T>::my_vector(my_vector && other) noexcept {
        vector_impl_.swap(other.vector_impl_);
    }
    
    template <typename T>
    my_vector<T>::~my_vector() {}
//-------------------------------------------------------------------------------
    template <typename T>
    std::size_t my_vector<T>::next_pow2(size_t capacity) const noexcept {
        size_t deg = 1;
        if (capacity > MAX_CAPACITY) {
            return MAX_CAPACITY;
        }
        while (deg < capacity) {
            deg *= 2;
        }
        return deg;
    }

    template <typename T>
    std::size_t my_vector<T>::size() const noexcept {
        return vector_impl_.size_;
    }

    template <typename T>
    std::size_t my_vector<T>::capacity() const noexcept {
        return vector_impl_.capacity_;
    }
    
    template <typename T>
    bool my_vector<T>::empty() const noexcept {
        return vector_impl_.size_ == 0;
    }
    
    template <typename T>
    my_vector<T>& my_vector<T>::operator= (const my_vector& other) {
        if (this != & other) {
            my_vector<T> tmp(other);
            vector_impl_.swap(tmp.vector_impl_);
        }
        return *this;
    }

    template <typename T>
    my_vector<T>& my_vector<T>::operator= (my_vector && other) noexcept {
        vector_impl_.swap(other.vector_impl_);
        return *this;
    }  

    template <typename T>
    void my_vector<T>::reserve(std::size_t newcap) { 
        if (newcap <= vector_impl_.capacity_) {
            return;
        }
        my_vector_holder tmp_vec(next_pow2(newcap));
        for (; tmp_vec.size_ < vector_impl_.size_; tmp_vec.size_++) {
            new (tmp_vec.array_ + tmp_vec.size_) T(std::move(vector_impl_.array_[tmp_vec.size_]));
        }
        vector_impl_.swap(tmp_vec);
    }

    template <typename T>
    void my_vector<T>::resize(std::size_t newsize) {
        while (vector_impl_.size_ > newsize) {
            pop_back();
        }
        if (vector_impl_.size_ == newsize) {
            return;
        }
        if (newsize > vector_impl_.capacity_) {
            my_vector_holder tmp_vec(next_pow2(newsize));
            for (; tmp_vec.size_ < newsize; tmp_vec.size_++) {
                new (tmp_vec.array_ + tmp_vec.size_) T();
            }
            for (; tmp_vec.size_ < vector_impl_.size_; tmp_vec.size_++) {
                new (tmp_vec.array_ + tmp_vec.size_) T(std::move(vector_impl_.array_[tmp_vec.size_]));
            }
            vector_impl_.swap(tmp_vec);
        }
        else {
            for (; vector_impl_.size_ < newsize; vector_impl_.size_++) {
                new (vector_impl_.array_ + vector_impl_.size_) T();
            }
        }
        
    }

    template <typename T>
    const T& my_vector<T>::operator[](std::size_t index) const noexcept {
        assert(index < vector_impl_.size_);
        return vector_impl_.array_[index];
    }

    template <typename T>
    T& my_vector<T>::operator[](std::size_t index) noexcept {
        assert(index < vector_impl_.size_);
        return vector_impl_.array_[index];
    }

    template <typename T>
    void my_vector<T>::push_back(T t) {
        reserve(vector_impl_.size_ + 1);
        new (vector_impl_.array_ + vector_impl_.size_) T(std::move(t));
        vector_impl_.size_++;
    }

    template <typename T>
    void my_vector<T>::pop_back() noexcept {
        assert(!empty());
        vector_impl_.array_[--vector_impl_.size_].~T();
    }

    template <typename T>
    void my_vector<T>::clear() noexcept {
        while (vector_impl_.size_ > 0) {
            pop_back();
        }
    }
//----------------------------------------------------------
    template <typename T>
    std::ostream& operator<< (std::ostream& os, const my_vector<T> & v) {
        return v >> os;
    }

    template <typename T>
    std::ostream& my_vector<T>::operator>> (std::ostream& os) const {
        for (size_t i = 0; i < vector_impl_.size_ - 1; i++) {
            os << vector_impl_.array_[i] << ' ';
        }
        os << vector_impl_.array_[vector_impl_.size_ - 1];
        return os;
    }
    
}

#endif