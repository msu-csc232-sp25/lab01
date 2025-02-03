/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2025
 *
 * @file    main.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Entry-point of the main target.
 * @version 1.0.0
 * @date    01/01/2025
 *
 * @copyright Copyright (c) 2025 James R. Daehn
 */

#include "csc232.h"

int main(const int argc, char *argv[]) {
    std::cout << "Hello, Main Target!" << std::endl;
    // we subtract one from argc because it includes the name of the executable itself
    std::cout << "This program was launched with " << (argc - 1) << " command line arguments." << std::endl;
    if (argc > 1) {
        std::cout << "The program arguments are: ";
        // we skip argv[0] because that's the name of the executable itself
        for (int i = 1; i < argc; ++i) {
            std::cout << argv[i] << " ";
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}
