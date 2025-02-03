/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2025
 *
 * @file    task3_test.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Task 3 test fixture.
 * @details Task 3 - Implement `operator+=` for the `DynamicArray` class
 * @version 1.0.0
 * @date    01/01/2025
 *
 * @copyright Copyright (c) 2025 James R. Daehn
 */

#include <gtest/gtest.h>
#include "csc232_test_utils.h"
#include "DynamicArray.h"

namespace csc232 {
    int small_data[] = {1, 2, 3, 4, 5};
    int initial_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int large_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    static constexpr size_t SMALL_ARRAY_SIZE{std::size(small_data)};
    static constexpr size_t SMALL_ARRAY_CAPACITY{std::size(small_data)};
    static constexpr size_t INITIAL_ARRAY_SIZE{std::size(initial_data)};
    static constexpr size_t INITIAL_ARRAY_CAPACITY{std::size(initial_data)};
    static constexpr size_t LARGE_ARRAY_SIZE{std::size(large_data)};
    static constexpr size_t LARGE_ARRAY_CAPACITY{std::size(large_data)};

    class Task3TestFixture : public CSC232BaseTestFixture {
    public:
        Task3TestFixture() : default_dynamic_array_{csc232::DynamicArray<int>{}},
                             populated_dynamic_array_{
                                 DynamicArray{initial_data, INITIAL_ARRAY_SIZE, INITIAL_ARRAY_CAPACITY}
                             },
                             large_dynamic_array_{DynamicArray{large_data, LARGE_ARRAY_SIZE, LARGE_ARRAY_CAPACITY}} {
        }

        ~Task3TestFixture() override = default;

    protected:
        // Reusable objects for each unit test in this test fixture
        DynamicArray<int> default_dynamic_array_;
        DynamicArray<int> populated_dynamic_array_;
        DynamicArray<int> large_dynamic_array_;
    };

#if !TEST_TASK3
    TEST_F(Task3TestFixture, Bootstrap) {
        std::cerr << "Task 3 is not ready for evaluation; please toggle the TEST_TASK3 macro to TRUE\n";
        SUCCEED();
    }

#else
    TEST_F(Task3TestFixture, AddSetsItemsWithIndependentExistence) {
        const DynamicArray lhs{small_data, SMALL_ARRAY_SIZE, SMALL_ARRAY_CAPACITY};
        const DynamicArray rhs{small_data, SMALL_ARRAY_SIZE, SMALL_ARRAY_CAPACITY};

        DynamicArray<int> independent_dynamic_array = lhs + rhs;
        for (size_t i = 0; i < SMALL_ARRAY_CAPACITY; i++) {
            EXPECT_EQ(independent_dynamic_array[i], small_data[i]);
            EXPECT_NE(&independent_dynamic_array[i], &small_data[i]);
        }
        for (size_t i = SMALL_ARRAY_CAPACITY; i < 2 * SMALL_ARRAY_CAPACITY; i++) {
            EXPECT_EQ(independent_dynamic_array[i], small_data[i - SMALL_ARRAY_CAPACITY]);
            EXPECT_NE(&independent_dynamic_array[i], &small_data[i - SMALL_ARRAY_CAPACITY]);
        }
    }

    TEST_F(Task3TestFixture, AddSetsSize) {
        const DynamicArray lhs{small_data, SMALL_ARRAY_SIZE, SMALL_ARRAY_CAPACITY};
        const DynamicArray rhs{small_data, SMALL_ARRAY_SIZE, SMALL_ARRAY_CAPACITY};

        DynamicArray<int> independent_dynamic_array = lhs + rhs;
        EXPECT_EQ(independent_dynamic_array.size(), lhs.size() + rhs.size());
    }

    TEST_F(Task3TestFixture, AddSetsCapacity) {
        const DynamicArray lhs{small_data, SMALL_ARRAY_SIZE, SMALL_ARRAY_CAPACITY};
        const DynamicArray rhs{small_data, SMALL_ARRAY_SIZE, SMALL_ARRAY_CAPACITY};

        DynamicArray<int> independent_dynamic_array = lhs + rhs;
        EXPECT_EQ(independent_dynamic_array.capacity(), lhs.capacity() + rhs.capacity());
    }

    TEST_F(Task3TestFixture, AddDoesntLeakMemory) {
        std::ifstream target{"./demo"};
        EXPECT_TRUE(target.good());
        if (target.good()) {
            std::string command{"valgrind --leak-check=full --error-exitcode=1 ./demo"};
            int result{system(command.c_str())};
            std::cerr << "result = " << result << "\n";
            EXPECT_EQ(result, 0);
        } else {
            FAIL();
        }
    }

#endif
} // end namespace csc232
