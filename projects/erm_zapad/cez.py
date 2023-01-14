import sys

# prices for the services
service_prices = [0.129, 1.461, 85.07, 0.132]


def gauss_jordan_elimination(matrix):
    for i in range(len(matrix)):
        # find the row with the largest coefficient
        max_row = i
        for j in range(i+1, len(matrix)):
            if abs(matrix[j][i]) > abs(matrix[max_row][i]):
                max_row = j

        # swap rows
        matrix[i], matrix[max_row] = matrix[max_row], matrix[i]

        # divide row by the coefficient
        matrix[i] = [x/matrix[i][i] for x in matrix[i]]

        # subtract row from other rows
        for j in range(len(matrix)):
            if j != i:
                matrix[j] = [matrix[j][k] - matrix[j][i]*matrix[i][k]
                             for k in range(len(matrix[i]))]

    return [matrix[i][-1] for i in range(len(matrix))]


# read input file
input_file = sys.argv[1]
with open(input_file, 'r') as f:
    data = f.readlines()

# get usage and bill data for each company
company_data = [[float(x) for x in line.strip().split()] for line in data[:4]]

bill_data = [float(x) for x in data[4].strip().split()]

# calculate total usage and bill for each company
total_usage = [sum(usage) for usage in company_data]
total_bill = [service_prices[j]*company_data[i][j]
              for j in range(4) for i in range(4)]

# calculate difference between bill and usage data - using Gauss-Jordan elimination
bill_diff = [bill_data[i] - total_bill[i] for i in range(4)]

for i in range(4):
    company_data[i].append(bill_data[i])

real_price = gauss_jordan_elimination(company_data.copy())

# company_data[i][j] - (company_data[i][j] * service_prices[j] / real_price[j])
usage_diff = [[company_data[i][j] - (company_data[i][j] * service_prices[j] / real_price[j])
               for j in range(4)] for i in range(4)]

# print results
print("Differences between bill data and calculations:")
for diff in bill_diff:
    print("%.3f" % diff, end='\t')
print("\nDifferences between usage data and billing:")
for company in usage_diff:
    for diff in company:
        print("%.3f" % diff, end='\t')
    print()

with open('output.txt', 'w') as f:
    for diff in bill_diff:
        f.write("%.3f " % diff)
        f.write("\t")
    f.write("\n")
    for company in usage_diff:
        for diff in company:
            f.write("%.3f " % diff)
            f.write("\t")
        f.write("\n")
