#pragma once

#include "../Matrix/Matrix.hpp"

#include <string>

#define ELECTRICITY_PRICE 0.129 // Cez (ERM Zapad) kWh
#define WATER_PRICE 1.461 // Veolia - m3
#define HEATING_PRICE 85.07 // Toplo.bg - MW/h
#define PHONE_PRICE 0.132 // Vivacom - Minutes

#define SERVICE_COUNT 4
#define COMPANY_COUNT 4

class Checker {
private:
    double const SERVICE_PRICES[SERVICE_COUNT] = {ELECTRICITY_PRICE, WATER_PRICE, HEATING_PRICE, PHONE_PRICE};
    std::string inputFileName = "input.txt"; // default name
    std::string outputFileName = "output.txt"; // default name

    Matrix billData;
    Matrix usageData;

    Matrix billDiff;
    Matrix usageDiff;

    void loadBillData();

    void loadUsageData();

    void writeBillDiff();

    void writeUsageDiff();

    double *getRealPrices();

    void printBillDiff();

    void printUsageDiff();

public:
    Checker();

    Checker(std::string inputFileName, std::string outputFileName);

    Checker &operator=(const Checker &other);

    Matrix &calculateBillDiff();

    Matrix &calculateUsageDiff();

    void print();

    void saveToFile();

    ~Checker();
};
