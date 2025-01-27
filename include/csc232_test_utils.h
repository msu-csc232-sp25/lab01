/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2025
 *
 * @file    csc232_test_utils.h
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Base test fixture specification used in csc232 unit tests.
 * @version 1.0.0
 * @date    01/01/2025
 *
 * @copyright Copyright (c) 2025 James R. Daehn
 */

#ifndef CSC232_TEST_UTILS_H
#define CSC232_TEST_UTILS_H

#include <gtest/gtest.h>
#include <regex>
#include "csc232.h"

namespace csc232 {
    class CSC232BaseTestFixture : public ::testing::Test {
    public:
        CSC232BaseTestFixture() : buffer{std::stringstream{}}, sbuf{nullptr}, earnedPoints{0}, possiblePoints{0} {
            // Intentionally empty; attributes initialized above.
        }

    protected:
        void SetUp() override {
            ::testing::FLAGS_gtest_death_test_style = "threadsafe";
            // Redirect cout to our stringstream buffer or any other ostream
            sbuf = std::cout.rdbuf();
            std::cout.rdbuf(buffer.rdbuf());

            AdditionalSetup();

            if (const ::testing::TestInfo *test_info = ::testing::UnitTest::GetInstance()->current_test_info()) {
                const char *test_name = test_info->name();
                // Ignore tests in this base fixture
                if (strcmp(test_info->test_suite_name(), "CSC232BaseTestFixture") != 0) {
                    // Only accumulate points for their work
                    if (const auto bootstrap = "Bootstrap"; strcmp(test_name, bootstrap) != 0) {
                        possiblePoints += 1;
                    }
                }
            }
        }

        void TearDown() override {
            // When done redirect cout to its old self
            std::cout.rdbuf(sbuf);
            sbuf = nullptr;

            AdditionalTearDown();

            if (!HasFailure()) {
                if (const ::testing::TestInfo *test_info = ::testing::UnitTest::GetInstance()->current_test_info()) {
                    const char *test_name = test_info->name();
                    // Ignore tests in this base fixture
                    if (strcmp(test_info->test_suite_name(), "CSC232BaseTestFixture") != 0) {
                        // Only accumulate points for their work
                        if (const auto bootstrap = "Bootstrap"; strcmp(test_name, bootstrap) != 0) {
                            earnedPoints += 1;
                        }
                    }
                }
            }
        }

        virtual void AdditionalSetup() {
            /* template method for any customized additional setup */
        }

        virtual void AdditionalTearDown() {
            /* template method for any customized additional setup */
        }

        virtual bool isClassDeclared(const std::string &filePath, const std::string &className) {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                std::cerr << "Unable to open file\n";
                return false;
            }

            std::string line;
            std::regex classPattern("\\bclass\\s+" + className + "\\b");
            while (std::getline(file, line)) {
                if (std::regex_search(line, classPattern)) {
                    return true;
                }
            }
            return false;
        }

        virtual bool isClassInNamespaceDeclared(const std::string &filePath, const std::string &namespaceName,
                                                const std::string &className) {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                std::cerr << "Unable to open file\n";
                return false;
            }

            std::string line;
            std::regex namespacePattern("\\bnamespace\\s+" + namespaceName + "\\b");
            std::regex classPattern("\\bclass\\s+" + className + "\\b");
            bool inNamespace = false;

            while (std::getline(file, line)) {
                if (std::regex_search(line, namespacePattern)) {
                    inNamespace = true;
                }
                if (inNamespace && std::regex_search(line, classPattern)) {
                    return true;
                }
            }
            return false;
        }

        virtual bool isClassDerivedFromBase(const std::string &filePath, const std::string &namespaceName,
                                            const std::string &className, const std::string &baseClassName) {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                std::cerr << "Unable to open file\n";
                return false;
            }

            std::string line;
            std::regex namespacePattern("\\bnamespace\\s+" + namespaceName + "\\b");
            std::regex classPattern("\\bclass\\s+" + className + "\\s*:\\s*public\\s+" + baseClassName + "\\b");
            bool inNamespace = false;

            while (std::getline(file, line)) {
                if (std::regex_search(line, namespacePattern)) {
                    inNamespace = true;
                }
                if (inNamespace && std::regex_search(line, classPattern)) {
                    return true;
                }
            }
            return false;
        }

        virtual bool isMethodDeclaredInClass(const std::string& filePath, const std::string& namespaceName, const std::string& className, const std::string& methodName) {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                std::cerr << "Unable to open file\n";
                return false;
            }

            std::string line;
            std::regex namespacePattern("\\bnamespace\\s+" + namespaceName + "\\b");
            std::regex classPattern("\\bclass\\s+" + className + "\\b");
            std::regex methodPattern("\\b" + methodName + "\\s*\\(");
            bool inNamespace = false;
            bool inClass = false;

            while (std::getline(file, line)) {
                if (std::regex_search(line, namespacePattern)) {
                    inNamespace = true;
                }
                if (inNamespace && std::regex_search(line, classPattern)) {
                    inClass = true;
                }
                if (inClass && std::regex_search(line, methodPattern)) {
                    return true;
                }
            }
            return false;
        }

        // Reusable objects for each unit test in this test fixture and any of its children
        std::stringstream buffer;
        std::streambuf *sbuf;
        /*
         * With the above in place, you can now have tests on output statements
         * like this:
         *
         * <some function call or executable that inserts info into output stream...>
         * const std::string expected{ "1/1/1902\n" }; // what you expect to have been inserted
         * const std::string actual{ buffer.str( ) };  // what was actually inserted
         * EXPECT_EQ( expected, actual );
         */
        double earnedPoints;
        double possiblePoints;
    };
}

#endif // CSC232_TEST_UTILS_H
