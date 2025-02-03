/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2025
 *
 * @file    task1_test.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Task 1 test fixture.
 * @details Task 1 - Creating and destroying instances of the DynamicArray class
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
    static constexpr size_t INITIAL_ARRAY_SIZE{std::size(initial_data)};
    static constexpr size_t INITIAL_ARRAY_CAPACITY{std::size(initial_data)};

    class Task1TestFixture : public CSC232BaseTestFixture {
    public:
        Task1TestFixture() : default_dynamic_array_{csc232::DynamicArray<int>{}},
                             populated_dynamic_array_{
                                 csc232::DynamicArray<int>{initial_data, INITIAL_ARRAY_SIZE, INITIAL_ARRAY_CAPACITY}
                             } {
            // intentionally empty
        }

        ~Task1TestFixture() override = default;

    protected:
        // Reusable objects for each unit test in this test fixture
        DynamicArray<int> default_dynamic_array_;
        DynamicArray<int> populated_dynamic_array_;
    };


#if !TEST_TASK1
    TEST_F(Task1TestFixture, Bootstrap) {
        std::cerr << "Task 1 is not ready for evaluation; please toggle the TEST_TASK1 macro to TRUE\n";
        SUCCEED(); // Just to keep spirits up out of the box ;-)
    }

#else

    TEST_F(Task1TestFixture, DefaultDynamicArraySetsDefaultCapacity) {
        EXPECT_EQ(default_dynamic_array_.capacity(), csc232::DEFAULT_CAPACITY);
    }

    TEST_F(Task1TestFixture, DefaultDynamicArraySetsEmptySize) {
        EXPECT_EQ(default_dynamic_array_.size(), 0);
        DynamicArray<std::string> empty_dynamic_array;
        EXPECT_EQ(empty_dynamic_array.size(), 0);
    }

    TEST_F(Task1TestFixture, CopyConstructorSetsItemsWithIndependentExistence) {
        DynamicArray dest{populated_dynamic_array_};
        for (size_t i = 0; i < populated_dynamic_array_.size(); ++i) {
            EXPECT_EQ(dest[i], populated_dynamic_array_[i]);
            EXPECT_NE(&dest[i], &populated_dynamic_array_[i]);
        }
    }

    TEST_F(Task1TestFixture, CopyConstructorSetsCapacity) {
        const DynamicArray dest{populated_dynamic_array_};
        EXPECT_EQ(dest.capacity(), populated_dynamic_array_.capacity());
    }

    TEST_F(Task1TestFixture, CopyConstructorSetsSize) {
        const DynamicArray dest{populated_dynamic_array_};
        EXPECT_EQ(dest.size(), populated_dynamic_array_.size());
    }

    TEST_F(Task1TestFixture, ItDoesntLeakMemory) {
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
