#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>
#include <iosfwd>

namespace my_vector {

    template<typename T>
    class my_vector final {
    public:
        my_vector() noexcept; 
        explicit my_vector(std::size_t n); 
        my_vector(const my_vector & other); 
        my_vector(my_vector && other) noexcept; 
        my_vector& operator=(const my_vector& other); 
        my_vector& operator=(my_vector && other) noexcept; 
        ~my_vector(); 

        std::size_t size() const noexcept; 
        std::size_t capacity() const noexcept; 
        bool empty() const noexcept; 

        void resize(std::size_t n); 
        void reserve(std::size_t n); 

        const T& operator[](std::size_t index) const noexcept; 
        T& operator[](std::size_t index) noexcept; 

        void push_back(T t); 
        void pop_back() noexcept; 
        void clear() noexcept; 
        std::ostream& operator>> (std::ostream& os) const;

    private:
        size_t next_pow2(size_t capacity) const noexcept;
        class my_vector_holder final {
        public:
            my_vector_holder(size_t cap = 0);
            ~my_vector_holder();
            my_vector_holder(const my_vector_holder &) = delete;
            my_vector_holder & operator= (const my_vector_holder &) = delete;
            void swap(my_vector_holder &) noexcept;

            T* array_;
            size_t capacity_;
            size_t size_;
        };
        my_vector_holder vector_impl_;
        constexpr static int MAX_CAPACITY = 1073741824;
    };

    template <typename T>
    std::ostream& operator<< (std::ostream& os, const my_vector<T> & v);

}

#include "my_vector_impl.h"

#endif  // MY_VECTOR_H_