#include "Checker.hpp"
#include "../Matrix/Matrix.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Checker::Checker() {
    loadUsageData();
    loadBillData();
}

Checker::Checker(std::string inputFileName, std::string outputFileName) {
    if (inputFileName.empty()) {
        std::cout << "Error: No input file specified" << std::endl;
        return;
    }

    if (outputFileName.empty()) {
        std::cout << "Error: No output file specified" << std::endl;
        return;
    }

    this->inputFileName = inputFileName;
    this->outputFileName = outputFileName;

    loadUsageData();
    loadBillData();
}

void Checker::loadBillData() {
    std::ifstream file(inputFileName);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + inputFileName);
    }

    file >> billData;
    if (!file.good()) {
        throw std::runtime_error("Error: Could not read bill data");
    }

    file.close();
}

void Checker::loadUsageData() {
    std::ifstream file(inputFileName);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + inputFileName);
    }

    file >> usageData;
    if (!file.good()) {
        throw std::runtime_error("Error: Could not read usage data");
    }

    file.close();
}

void Checker::writeBillDiff() {
    std::ofstream file(outputFileName);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + outputFileName);
    }

    file << billDiff;
    if (!file.good()) {
        throw std::runtime_error("Error: Could not write bill diff");
    }

    file.close();
}

void Checker::writeUsageDiff() {
    std::ofstream file(outputFileName);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + outputFileName);
    }

    file << usageDiff;
    if (!file.good()) {
        throw std::runtime_error("Error: Could not write usage diff");
    }

    file.close();
}

void Checker::printBillDiff() {
    std::cout << "Bill diff:" << std::endl;
    billDiff.print();
}

void Checker::printUsageDiff() {
    std::cout << "Usage diff:" << std::endl;
    usageDiff.print();
}

Matrix &Checker::calculateBillDiff() {
    billDiff = Matrix(1, 4);
    for (int i = 0; i < 4; i++) {
        double sum = 0;
        for (int j = 0; j < 4; j++) {
            sum += usageData.get(i, j) * SERVICE_PRICES[j];
        }
        billDiff.set(0, i, billData.get(0, i) - sum);
    }

    // if we want to play with the matrix outside the class (damn, clion is fixing my awful grammar)
    return billDiff;
}

Matrix &Checker::calculateUsageDiff() {
    Matrix usageDataGauss(COMPANY_COUNT, SERVICE_COUNT + 1);
    double **data = new double *[4];
    for (int i = 0; i < 4; i++) {
        data[i] = new double[5];
        for (int j = 0; j < 4; j++) {
            data[i][j] = usageData.get(i, j);
        }
        data[i][4] = billData.get(0, i);
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            usageDataGauss.set(i, j, data[i][j]);
        }
    }

    double *realPrices = gaussJordanElimination(usageDataGauss);

    usageDiff = Matrix(4, 4);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            usageDiff.set(i, j, (usageData.get(i, j) * realPrices[j] / SERVICE_PRICES[j]) -
                    usageData.get(i, j));
        }
    }

    delete[] realPrices;

    // same thing as billDiff - if we want to play with the matrix outside the class
    return usageDiff;
}

void Checker::print() {
    printBillDiff();
    printUsageDiff();
}

void Checker::saveToFile() {
    writeBillDiff();
    writeUsageDiff();
}

Checker::~Checker() {
    // free memory
}
