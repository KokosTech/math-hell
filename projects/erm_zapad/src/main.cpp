#include <fstream>
#include <iostream>

#include "Checker/Checker.hpp"
#include "Matrix/Matrix.hpp"

double SERVICE_PRICES[4] = {0.129, 1.461, 85.07, 0.132};

// Apparently, 'usage' is with one 's'
// TODO: Rename to 'usage'
// Writing too much JavaScript (and JAVA - OOPs exams) is bad for you - camelCase is not the way to go,
// but I'm way too used to it now, after speedrinning HT website for a week
// Btw, I clould have used vector<<vector<double>> instead of double**, but it's more C like this way

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
        std::cout << "Usage: " << argv[0] << " [input_file] [output_file]"
                  << std::endl;
        return 1;
    }

    return 0;
}