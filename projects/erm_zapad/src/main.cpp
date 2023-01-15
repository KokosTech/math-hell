#include <fstream>
#include <iostream>

#include "Matrix/Matrix.hpp"

double SERVICE_PRICES[4] = {0.129, 1.461, 85.07, 0.132};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <matrix_file>" << std::endl;
        return 1;
    }

    Matrix company_data(4, 4);
    Matrix bill_data(1, 4);

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    file >> company_data;
    if (file.eof()) {
        std::cout << "Error: Could not read company data" << std::endl;
        return 1;
    }

    file >> bill_data;
    if (file.eof()) {
        std::cout << "Error: Could not read bill data" << std::endl;
        return 1;
    }

    file.close();

    std::cout << "Company data:" << std::endl;
    company_data.print();
    std::cout << "Bill data:" << std::endl;
    bill_data.print();

    Matrix company_data_gauss(4, 5);
    double **data = new double *[4];
    for (int i = 0; i < 4; i++) {
        data[i] = new double[5];
        for (int j = 0; j < 4; j++) {
            data[i][j] = company_data.get(i, j);
        }
        data[i][4] = bill_data.get(0, i);
    }
    company_data_gauss.setData(data);

    double *realPrices = gaussJordanElimination(company_data_gauss);
    std::cout << "Real prices:" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << realPrices[i] << " ";
    }

    double **ussage_diff_data = new double *[4];
    for (int i = 0; i < 4; i++) {
        ussage_diff_data[i] = new double[4];
        for (int j = 0; j < 4; j++) {
            ussage_diff_data[i][j] = (company_data.get(i, j) * realPrices[j] / SERVICE_PRICES[j]) - company_data.get(i, j);
        }
    }

    Matrix ussage_diff(4, 4, ussage_diff_data);
    std::cout << "Ussage diff:" << std::endl;
    ussage_diff.print();

    return 0;
}