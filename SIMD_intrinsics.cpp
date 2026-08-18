// compile g++ -O3 -mavx2 SIMD_intrinsics.cpp  -o SIMD_intrinsics && ./SIMD_intrinsics

#include <bits/stdc++.h>
#include <immintrin.h>

using namespace std;

class Matrix {
private:
    int rows, cols;
    vector<vector<double>> data;

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data = vector<vector<double>>(r, vector<double>(c, 0));
    }

    vector<double>& operator[](int i) {
        return data[i];
    }

    const vector<double>& operator[](int i) const {
        return data[i];
    }

    void rand(double minValue = 0, double maxValue = 10) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<double> dist(minValue, maxValue);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = dist(gen);
            }
        }
    }

    Matrix operator+(const Matrix& b) const {
        if (rows != b.rows || cols != b.cols) {
            throw invalid_argument("matrices must have same dimensions");
        }
        Matrix res(rows, cols);
        for (int i = 0; i < rows; i++) {
            int j = 0;
            for (; j + 3 < cols; j += 4) {
                __m256d a = _mm256_loadu_pd(&data[i][j]);
                __m256d bb = _mm256_loadu_pd(&b.data[i][j]);
                __m256d c = _mm256_add_pd(a, bb);
                _mm256_storeu_pd(&res.data[i][j], c);
            }

            for (; j < cols; j++) {
                res.data[i][j] = data[i][j] + b.data[i][j];
            }
        }

        return res;
    }

    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << ' ';
            }
            cout << '\n';
        }
    }
};

int main() {

    Matrix A(1000, 1000);
    Matrix B(1000, 1000);

    A.rand(0, 1000);
    B.rand(0, 525);

    Matrix C = A + B;


     C.print();
}
