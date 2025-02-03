/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2025
 *
 * @file    DynamicArray.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   DynamicArray implementation.
 * @version 1.0.0
 * @date    01/01/2025
 *
 * @copyright Copyright (c) 2025 James R. Daehn
 */

#include "DynamicArray.h"

namespace csc232 {

    template<typename T>
    DynamicArray<T>::DynamicArray(const T data[], const size_t size, const size_t capacity) : data_{new T[capacity]}, size_{size},
        capacity_{capacity} {
        for (size_t i = 0; i < size; i++) {
            data_[i] = data[i];
        }
    }

    // TODO: Task 1a - Implement me accordingly
    template<typename T>
    DynamicArray<T>::DynamicArray() {

    }

    // TODO: Task 1b - Free resources accordingly
    template<typename T>
    DynamicArray<T>::~DynamicArray() {

    }

    // TODO: Task 1c - Implement me accordingly
    template<typename T>
    DynamicArray<T>::DynamicArray(const DynamicArray &src) {

    }

// TODO: Task 2 - Implement me accordingly
template<typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray &rhs) {
  return *this;
}

template<typename T>
const T &DynamicArray<T>::operator[](int index) const {
    return data_[index];
}

template<typename T>
T &DynamicArray<T>::operator[](int index) {
  return data_[index];
}

template<typename T>
size_t DynamicArray<T>::size() const {
    return size_;
}

template<typename T>
size_t DynamicArray<T>::capacity() const {
    return capacity_;
}
} // csc232
