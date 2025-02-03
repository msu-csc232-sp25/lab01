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

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>

namespace csc232 {
    static constexpr int DEFAULT_CAPACITY{10};

    /**
     * A simple wrapper around a dynamic array.
     * @tparam T the type of item stored in the contained dynamic area.
     */
    template<typename T>
    class DynamicArray {
    public:
        /**
         * Default constructor.
         */
        DynamicArray();

        /**
         * Initializing constructor.
         * @param data the initial data to place in this wrapper.
         * @param size the number of data elements found in data.
         * @param capacity the initial total capacity of this wrapper.
         */
        DynamicArray(const T data[], size_t size, size_t capacity);

        /**
         * Destructor.
         */
        ~DynamicArray();

        /**
         * Copy constructor.
         * @param src the DynamicArray to use as a source of initial data.
         */
        DynamicArray(const DynamicArray &src);

        /**
         * Copy assignment operator.
         * @param rhs the DynamicArray
         * @return a new DynamicArray that contains the same data as rhs
         */
        DynamicArray &operator=(const DynamicArray &rhs);

        /**
         * Array access (read-only) operator.
         * @param index the index into the data contained in this wrapper.
         * @return the value located at the given index
         */
        const T &operator[](int index) const;

        /**
         * Array access (read and write) operator.
         * @param index the index into the data contained in this wrapper.
         * @return the value read from (or written to) the given index.
         */
        T &operator[](int index);

        /**
         * The number of elements currently stored in this array wrapper.
         * @return the number of elements currently stored in this array wrapper.
         */
        [[nodiscard]] size_t size() const;

        /**
         * The capacity of this array wrapper.
         * @return the total possible values that can currently be stored in this array wrapper.
         */
        [[nodiscard]] size_t capacity() const;

    private:
        T *data_;
        size_t size_;
        size_t capacity_;
    };


    /**
     * Addition operator for DynamicArray objects.
     * @tparam T the type of data stored in the DynamicArray objects.
     * @param lhs the left-hand side operand of the + operator.
     * @param rhs the right-hand side operand of the + operator.
     * @return a new DynamicArray that contains data from both arguments.
     */
    template<typename T>
    DynamicArray<T> operator+(const DynamicArray<T> &lhs, const DynamicArray<T> &rhs) {
        // TODO: Task 3 - Implement me accordingly
        return DynamicArray<T>{};
    }

    /**
     * Stream insertion overload for DynamicArray objects.
     * @tparam T the type of data contained in the given DynamicArray.
     * @param os a reference to an output stream in which to insert data about this wrapper.
     * @param arr a constant reference to the DynamicArray object we are inserting into the given output stream.
     * @return a reference to the updated output stream.
     */
    template<typename T>
    std::ostream &operator<<(std::ostream &os, const DynamicArray<T> &arr) {
        os << "{\n\tdata_: [\n";
        for (size_t i = 0; i < arr.size(); i++) {
            os << "\t\t" << arr[i] << (i < arr.size() - 1 ? "," : "") << "\n";
        }
        return os << "\t],\n" << "\tsize_: " << arr.size() << ",\n\tcapacity_: " << arr.capacity() << "\n}\n";
    }
} // csc232

#endif // DYNAMIC_ARRAY_H
