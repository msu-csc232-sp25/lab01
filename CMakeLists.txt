cmake_minimum_required(VERSION 3.16.3)
set(IS_HW FALSE)
set(CSC232_PROJECT_TYPE "lab")
if(IS_HW)
    set(CSC232_PROJECT_TYPE "hw")
    # TODO: Don't forget to uncomment tasks 4&5 in classroom.yml
    message("TODO: Don't forget to uncomment tasks 4&5 in classroom.yml")
endif()

message("CSC232_PROJECT_TYPE: ${CSC232_PROJECT_TYPE}")
project(${CSC232_PROJECT_TYPE})

if (CMAKE_VERSION GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

# Set compiler flags based on environment
if (MSVC)
    # Force to always compile with W4
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif ()
    message("Compiler: MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /std:c++14")
elseif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Update if necessary
    message("Compiler: gnucc or gnucxx")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -g")
elseif((CMAKE_C_COMPILER_ID MATCHES "Clang") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    message("Compiler: Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -g -std=c++14")
endif ()

# echo CMAKE_CXX_FLAGS
message("CMAKE_CXX_FLAGS =${CMAKE_CXX_FLAGS}")

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)

# Source sets for targets
set(SRC_MAIN_FILES src/main/cpp/main.cpp)
set(SRC_DEMO_FILES src/main/cpp/demo.cpp)
set(SRC_TASK1_TEST_FILES src/test/cpp/task1_test.cpp)
set(SRC_TASK2_TEST_FILES src/test/cpp/task2_test.cpp)
set(SRC_TASK3_TEST_FILES src/test/cpp/task3_test.cpp)

# Setup Google Test
set(GOOGLE_TEST_ARCHIVE "v1.14.0")
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/${GOOGLE_TEST_ARCHIVE}.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(main ${SRC_MAIN_FILES})
add_executable(demo ${SRC_DEMO_FILES})
add_executable(task1_test ${SRC_TASK1_TEST_FILES})
add_executable(task2_test ${SRC_TASK2_TEST_FILES})
add_executable(task3_test ${SRC_TASK3_TEST_FILES})

# Now simply link against gtest or gtest_main as needed.
target_link_libraries(task1_test GTest::gtest_main)
target_link_libraries(task2_test GTest::gtest_main)
target_link_libraries(task3_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(task1_test)
gtest_discover_tests(task2_test)
gtest_discover_tests(task3_test)

target_include_directories(main PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)
target_include_directories(demo PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)
target_include_directories(task1_test PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)
target_include_directories(task2_test PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)
target_include_directories(task3_test PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)

# add custom commands that copy data input files to target working directories
add_custom_command(TARGET main PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/main/resources/main_data.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET demo PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/main/resources/demo_data.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET task1_test PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/task1_test_data.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET task2_test PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/task2_test_data.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET task3_test PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/task3_test_data.txt ${CMAKE_CURRENT_BINARY_DIR})

if (IS_HW)
    set(SRC_TASK4_TEST_FILES src/test/cpp/task4_test.cpp)
    set(SRC_TASK5_TEST_FILES src/test/cpp/task5_test.cpp)
    add_executable(task4_test ${SRC_TASK4_TEST_FILES})
    add_executable(task5_test ${SRC_TASK5_TEST_FILES})
    target_link_libraries(task4_test GTest::gtest_main)
    target_link_libraries(task5_test GTest::gtest_main)
    gtest_discover_tests(task4_test)
    gtest_discover_tests(task5_test)
    target_include_directories(task4_test PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)
    target_include_directories(task5_test PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)
    add_custom_command(TARGET task4_test PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/task4_test_data.txt ${CMAKE_CURRENT_BINARY_DIR})
    add_custom_command(TARGET task5_test PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/task5_test_data.txt ${CMAKE_CURRENT_BINARY_DIR})
endif ()

# first we can indicate the documentation build as an option and set it to OFF by default
option(BUILD_DOC "Build documentation" OFF)
find_package(Doxygen
        OPTIONAL_COMPONENTS dot mscgen dia)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/config/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the config together with the application
    add_custom_target(doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
