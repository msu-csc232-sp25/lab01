/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2025
 *
 * @file    demo.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Entry-point of the demo target.
 * @version 1.0.0
 * @date    01/01/2025
 *
 * @copyright Copyright (c) 2025 James R. Daehn
 */

#include "csc232.h"
#include "DynamicArray.h"

int main() {
#if TEST_TASK1
    const csc232::DynamicArray<int> dynamic_array;
    cout << "dynamic_array.size() = " << dynamic_array.size() << endl;
    cout << "dynamic_array.capacity() = " << dynamic_array.capacity() << endl;
    cout << "dynamic_array = " << dynamic_array << endl;
#endif

#if TEST_TASK2
    // Work with copy constructor
    int data[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    size_t size = std::size(data);
    size_t capacity = std::size(data);

    const csc232::DynamicArray src{data, size, capacity};
    const csc232::DynamicArray dst{src};
    cout << "src.size() = " << src.size() << endl;
    cout << "src.capacity() = " << src.capacity() << endl;
    cout << "dst.size() = " << dst.size() << endl;
    cout << "dst.capacity() = " << dst.capacity() << endl;
    cout << "src = " << src << endl;
    cout << "dst = " << dst << endl;
#endif

#if TEST_TASK3
    // Work wih + operator
    auto sum = src + dst;
#endif

    return EXIT_SUCCESS;
}
