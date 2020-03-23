#include <cstdio>
#include <assert.h>
#include <malloc.h>
#include <utility>
#include <algorithm>
#include "matrix.hpp"
#include "shared_ptr.hpp"

shared_ptr::shared_ptr(Matrix* obj){
    if (obj != nullptr) {
        storage_ = new Storage(obj);
    }
    else {
        storage_ = nullptr;
    }
}

shared_ptr::shared_ptr(const shared_ptr& other) {
    if (other.storage_ != nullptr) {
        other.storage_->incr();
    }  
    storage_ = other.storage_;
}

Matrix* shared_ptr::ptr() const {
    if (storage_ != nullptr) {   
        return storage_->getObject();
    }
    else {
        return nullptr;
    }
}

shared_ptr::~shared_ptr() {
    this->remove_ptr();      
}

void shared_ptr::remove_ptr() {
    if (storage_ != nullptr) {
        storage_->decr();
        if (!storage_->getCounter()) {
            delete storage_;
        }
    }     
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {
    std::swap(storage_, other.storage_);
    return *this;
}

bool shared_ptr::isNull() const {
    return storage_ == nullptr;
}

void shared_ptr::reset(Matrix* obj ) {
    this->remove_ptr(); 
    if (obj != nullptr) {
        storage_ = new Storage(obj);
    }
    else {
        storage_ = nullptr;  
    }
}

Matrix* shared_ptr::operator->() const {
    assert (storage_ != nullptr);
    return storage_->getObject();
}

Matrix& shared_ptr::operator*() const{
    assert(storage_ != nullptr);
    return *storage_->getObject();
}

shared_ptr::Storage::Storage(Matrix * mtx) {
    assert(mtx != nullptr);
    data_ = mtx;
    ref_count_ = 1;
}

shared_ptr::Storage::~Storage() {
    if (data_ != nullptr) {
        delete data_;
    }
}

void shared_ptr::Storage::incr() {
    ref_count_++;
}

void shared_ptr::Storage::decr() {
    ref_count_--;
}

int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const {
    return data_;
}
