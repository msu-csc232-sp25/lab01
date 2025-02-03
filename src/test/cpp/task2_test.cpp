/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2025
 *
 * @file    task2_test.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Task 2 test fixture.
 * @details Task 2 - Implement the copy assignment operator for the `DynamicArray` class
 * @version 1.0.0
 * @date    01/01/2025
 *
 * @copyright Copyright (c) 2025 James R. Daehn
 */

#include <gtest/gtest.h>
#include "csc232_test_utils.h"
#include "DynamicArray.h"

namespace csc232 {
    int initial_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int large_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    static constexpr size_t INITIAL_ARRAY_SIZE{std::size(initial_data)};
    static constexpr size_t INITIAL_ARRAY_CAPACITY{std::size(initial_data)};
    static constexpr size_t LARGE_ARRAY_CAPACITY{std::size(large_data)};
    static constexpr size_t LARGE_ARRAY_SIZE{std::size(large_data)};

    class Task2TestFixture : public CSC232BaseTestFixture {
    public:
        Task2TestFixture() : default_dynamic_array_{csc232::DynamicArray<int>{}},
                             populated_dynamic_array_{
                                 csc232::DynamicArray{initial_data, INITIAL_ARRAY_SIZE, INITIAL_ARRAY_CAPACITY}
                             },
                             large_dynamic_array_{
                                 csc232::DynamicArray{large_data, LARGE_ARRAY_SIZE, LARGE_ARRAY_CAPACITY}
                             } {
        }

        ~Task2TestFixture() override = default;

    protected:
        // Reusable objects for each unit test in this test fixture
        DynamicArray<int> default_dynamic_array_;
        DynamicArray<int> populated_dynamic_array_;
        DynamicArray<int> large_dynamic_array_;
    };

#if !TEST_TASK2
    TEST_F(Task2TestFixture, Bootstrap) {
        std::cerr << "Task 2 is not ready for evaluation; please toggle the TEST_TASK2 macro to TRUE\n";
        SUCCEED(); // Just to keep spirits up out of the box ;-)
    }

#else
    // No resizing tests
    TEST_F(Task2TestFixture, SelfAssignmentDoesntChangeSize) {
        DynamicArray<int> dynamic_array{};
        EXPECT_EQ(dynamic_array.size(), 0);
        dynamic_array = dynamic_array;
        EXPECT_EQ(dynamic_array.size(), 0);
    }

    TEST_F(Task2TestFixture, SelfAssignmentDoesntChangeCapacity) {
        DynamicArray<int> dynamic_array{};
        EXPECT_EQ(dynamic_array.capacity(), DEFAULT_CAPACITY);
        dynamic_array = dynamic_array;
        EXPECT_EQ(dynamic_array.capacity(), DEFAULT_CAPACITY);
    }

    TEST_F(Task2TestFixture, CopyAssignmentSetsItemsWithIndependentExistence) {
        DynamicArray<int> dest;
        dest = populated_dynamic_array_;
        for (size_t i = 0; i < populated_dynamic_array_.size(); ++i) {
            EXPECT_EQ(dest[i], populated_dynamic_array_[i]);
            EXPECT_NE(&dest[i], &populated_dynamic_array_[i]);
        }
    }

    TEST_F(Task2TestFixture, CopyAssignmentSetsCapacity) {
        DynamicArray<int> dest;
        dest = populated_dynamic_array_;
        EXPECT_EQ(dest.capacity(), populated_dynamic_array_.capacity());
    }

    TEST_F(Task2TestFixture, CopyAssignmentSetsSize) {
        DynamicArray<int> dest;
        dest = populated_dynamic_array_;
        EXPECT_EQ(dest.size(), populated_dynamic_array_.size());
    }

    // Resizing tests
    TEST_F(Task2TestFixture, CopyAssignmentResizesWhenBelowCapacityWithIndependentExistence) {
        DynamicArray<int> dest;
        dest = large_dynamic_array_;
        for (size_t i = 0; i < large_dynamic_array_.size(); ++i) {
            EXPECT_EQ(dest[i], large_dynamic_array_[i]);
            EXPECT_NE(&dest[i], &large_dynamic_array_[i]);
        }
    }

    TEST_F(Task2TestFixture, ItDoesntLeakMemory) {
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
