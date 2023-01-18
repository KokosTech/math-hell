#include "Checker.hpp"

#include <fstream>
#include <iostream>
#include <limits>
#include <string>

#include "../Matrix/Matrix.hpp"

Checker::Checker() {
    loadUsageData();
    loadBillData();
}

Checker::Checker(std::string inputFileName, std::string outputFileName) {
    if (inputFileName.empty())
        throw std::invalid_argument("No input file specified");

    if (outputFileName.empty())
        throw std::invalid_argument("No output file specified");

    this->inputFileName = inputFileName;
    this->outputFileName = outputFileName;

    loadUsageData();
    loadBillData();
}

Checker &Checker::operator=(const Checker &other) {
    if (this != &other) {
        this->inputFileName = other.inputFileName;
        this->outputFileName = other.outputFileName;
        this->billData = other.billData;
        this->usageData = other.usageData;
        this->billDiff = other.billDiff;
        this->usageDiff = other.usageDiff;
    }

    return *this;
}

void Checker::loadBillData() {
    billData = Matrix(1, COMPANY_COUNT);

    std::ifstream file(inputFileName);
    if (!file.is_open())
        throw std::runtime_error("Could not open file " + inputFileName);

    // skip first 4 lines
    for (int i = 0; i < COMPANY_COUNT; i++) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (!file.good())
            throw std::runtime_error("Error: Could not skip line");
    }

    file >> billData;
    if (!file.good())
        throw std::runtime_error("Error: Could not read bill data");

    file.close();
}

void Checker::loadUsageData() {
    usageData = Matrix(COMPANY_COUNT, SERVICE_COUNT);

    std::ifstream file(inputFileName);
    if (!file.is_open())
        throw std::runtime_error("Could not open file " + inputFileName);

    file >> usageData;
    if (!file.good())
        throw std::runtime_error("Error: Could not read usage data");

    file.close();
}

void Checker::writeBillDiff() {
    std::ofstream file(outputFileName);
    if (!file.is_open())
        throw std::runtime_error("Could not open file " + outputFileName);

    file << billDiff;
    if (!file.good())
        throw std::runtime_error("Error: Could not write bill diff");

    file.close();
}

void Checker::writeUsageDiff() {
    std::ofstream file(outputFileName, std::ios::app);
    if (!file.is_open())
        throw std::runtime_error("Could not open file " + outputFileName);

    file << usageDiff;
    if (!file.good())
        throw std::runtime_error("Error: Could not write usage diff");

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
    billDiff = Matrix(1, COMPANY_COUNT);

    for (int i = 0; i < COMPANY_COUNT; i++) {
        double sum = 0;

        for (int j = 0; j < SERVICE_COUNT; j++)
            sum += usageData.get(i, j) * SERVICE_PRICES[j];

        billDiff.set(0, i, billData.get(0, i) - sum);
    }

    // if we want to play with the matrix outside the class (damn, clion is
    // fixing my awful grammar)
    return billDiff;
}

double *Checker::getRealPrices() {
    Matrix usageDataGauss(COMPANY_COUNT, SERVICE_COUNT + 1);

    for (int i = 0; i < COMPANY_COUNT; i++) {
        for (int j = 0; j < SERVICE_COUNT; j++) {
            usageDataGauss.set(i, j, usageData.get(i, j));
        }
        usageDataGauss.set(i, SERVICE_COUNT, billData.get(0, i));
    }

    double *realPrices = gaussJordanElimination(usageDataGauss);
    if (!realPrices)
        throw std::runtime_error("Error: Could not calculate real prices");

    return realPrices;
}

Matrix &Checker::calculateUsageDiff() {
    double *realPrices = getRealPrices();
    if (!realPrices)
        throw std::runtime_error("Error: Could not calculate real prices");

    this->usageDiff = Matrix(COMPANY_COUNT, SERVICE_COUNT);

    for (int i = 0; i < COMPANY_COUNT; i++) {
        for (int j = 0; j < SERVICE_COUNT; j++) {
            double usageDiff =
                (usageData.get(i, j) * realPrices[j] / SERVICE_PRICES[j]) -
                usageData.get(i, j);

            this->usageDiff.set(i, j, usageDiff);
        }
    }

    delete[] realPrices;

    // same thing as billDiff - if we want to play with the matrix outside
    // the class
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
    // delete &billData;
    // delete &usageData;
    // delete &billDiff;
    // delete &usageDiff;
}
