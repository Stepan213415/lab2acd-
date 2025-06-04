#include <iostream>
#include <fstream>
using namespace std;

void delMemory(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

double calculateY(double x, int n) {
    if (x <= 0) {
        double productResult = 1;
        for (int i = 0; i <= n - 1; i++) {
            productResult *= (pow(i, 2) - x);
        }
        return x + productResult;
    }
    else {
        double sumResult = 0;
        for (int i = 1; i <= n - 1; i++) {
            for (int j = 0; j <= n - 1; j++) {
                sumResult += x / (i + j);
            }
        }
        return sumResult;
    }
}

int main() {
    int rows, cols;

    ifstream inFile("input.txt");
    if (!inFile) {
        cout << "Не вдалося відкрити input.txt" << endl;
        return 1;
    }

    inFile >> rows >> cols;

    int n;
    cout << "Вхідне значення n: ";
    cin >> n;
    if (n <= 0) {
        cerr << "Недійсне значення n" << endl;
        return 1;
    }

    double** result = new double* [rows];
    for (int i = 0; i < rows; i++) {
        result[i] = new double[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double x;
            if (!(inFile >> x)) {
                cerr << "Недостатня кількість значень x у input.txt" << endl;
                return 1;
            }
            result[i][j] = calculateY(x, n);
        }
    }

    inFile.close();

    ofstream outFile("output.txt");
    if (!outFile) {
        cout << "Не вдалося відкрити файл output.txt для запису" << endl;
        delMemory(result, rows);
        return 1;
    }

    cout << "\nВихід другого масиву:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << result[i][j] << " ";
            outFile << result[i][j] << " ";
        }
        cout << "\n";
        outFile << "\n";
    }

    outFile.close();
    delMemory(result, rows);
    return 0;
}

