#include <fstream>
#include <iostream>

#include "Matrix/Matrix.hpp"
#include "Checker/Checker.hpp"

double SERVICE_PRICES[4] = {0.129, 1.461, 85.07, 0.132};

// Apparently, 'usage' is with one 's'

int main(int argc, char *argv[]) {
    std::cout << "Welcome to the Matrix Calculator! | " << argc << std::endl;
    if (argc == 1) {
        Checker checker;
        checker.calculateBillDiff();
        checker.calculateUsageDiff();
        checker.print();
        checker.saveToFile();
    } else if (argc == 3) {
        Checker checker(argv[1], argv[2]);
        checker.calculateBillDiff();
        checker.calculateUsageDiff();
        checker.print();
        checker.saveToFile();
    } else {
        std::cout << "Usage: " << argv[0] << " [input_file] [output_file]" << std::endl;
        return 1;
    }

    return 0;
}