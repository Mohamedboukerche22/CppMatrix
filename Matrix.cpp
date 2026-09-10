#include<bits/stdc++.h>
#include <immintrin.h>
// compile g++ neural_net.cpp -O3 -mavx2 main.cpp -o net && ./net

using namespace std;
using Matrix=vector<vector<float>>;
using vec=vector<float>;

void print(Matrix a){
  //printf("[");
    for (size_t i = 0; i < a.size(); i++) {
     for (size_t j = 0; j < a[0].size() ; j++) {
         printf("%.4f ",a[i][j]);
     }
     printf("\n");
     
   }
   //printf("]\n");
}

float sum(Matrix a){
  float Sum=0.0;
   for (size_t i = 0; i < a.size(); i++) {
     size_t j=0;
     __m256 acc = _mm256_setzero_ps();
     for (; j + 8 <= a[0].size(); j += 8){
       __m256 va = _mm256_loadu_ps(&a[i][j]);
       acc = _mm256_add_ps(acc, va);
     }
     __m128 lo = _mm256_castps256_ps128(acc);
     __m128 hi = _mm256_extractf128_ps(acc, 1);
     lo = _mm_add_ps(lo, hi);
     lo = _mm_hadd_ps(lo, lo);
     lo = _mm_hadd_ps(lo, lo);
     Sum += _mm_cvtss_f32(lo);
     for (; j < a[0].size(); j++) Sum += a[i][j];
   }
   return Sum;
}

Matrix zeros(size_t r, size_t c) {
    return Matrix(r, vec(c, 0.0f));
}

Matrix ones(size_t r, size_t c) {
    return Matrix(r, vec(c, 1.0f));
}

Matrix fill_matrix(size_t r, size_t c, float v) {
    return Matrix(r, vec(c,v));
}

/*Matrix operator+(const Matrix& a , const Matrix& b){
  if(a.empty()||b.empty()||a.size()!=b.size()||a[0].size()!=b[0].size()){
    //throw ereur "invalid shape";
    throw invalid_argument("Matrix dimensions don't match");

    
  } 
    Matrix C(a.size(),vec(a[0].size())); 
   for (size_t i = 0; i < a.size(); i++) {
      for (size_t j = 0; j < a[0].size(); j++) {
         C[i][j]=a[i][j]+b[i][j];
      }
    }

  return C;
}*/

// -------------------- boost operator -------------------------------------------//
Matrix operator-(const Matrix& a , const Matrix& b){
    Matrix C(a.size(), vec(a[0].size()));
    for (size_t i = 0; i < a.size(); i++){
        size_t j = 0;
        for (; j + 8 <= a[0].size(); j += 8){
            __m256 va = _mm256_loadu_ps(&a[i][j]);
            __m256 vb = _mm256_loadu_ps(&b[i][j]);
            _mm256_storeu_ps(&C[i][j], _mm256_sub_ps(va, vb));
        }
        for (; j < a[0].size(); j++) C[i][j] = a[i][j] - b[i][j];
    }
    return C;
}

Matrix operator/(const Matrix& a , const Matrix& b){
    Matrix C(a.size(), vec(a[0].size()));
    for (size_t i = 0; i < a.size(); i++){
        size_t j = 0;
        for (; j + 8 <= a[0].size(); j += 8){
            __m256 va = _mm256_loadu_ps(&a[i][j]);
            __m256 vb = _mm256_loadu_ps(&b[i][j]);
            _mm256_storeu_ps(&C[i][j], _mm256_div_ps(va, vb));
        }
        for (; j < a[0].size(); j++) C[i][j] = a[i][j] / b[i][j];
    }
    return C;
}

Matrix operator+(const Matrix& a, const Matrix& b){
    Matrix C(a.size(), vec(a[0].size()));
    for (size_t i = 0; i < a.size(); i++){
        size_t j = 0;
        for (; j + 8 <= a[0].size(); j += 8){
            __m256 va = _mm256_loadu_ps(&a[i][j]);
            __m256 vb = _mm256_loadu_ps(&b[i][j]);
            __m256 vsum = _mm256_add_ps(va, vb);
            _mm256_storeu_ps(&C[i][j], vsum);
        }
        for (; j < a[0].size(); j++) C[i][j] = a[i][j] + b[i][j];
    }
    return C;
}

Matrix operator*(const Matrix& A, const Matrix& B) {
    if (A.empty() || B.empty()) {
        throw invalid_argument("Cannot multiply empty matrices");
    }

    if (A[0].size() != B.size()) {
        throw invalid_argument("Invalid matrix dimensions for multiplication");
    }

    Matrix C(A.size(), vec(B[0].size(), 0.0f));

    for (size_t i = 0; i < A.size(); ++i) {
        size_t j = 0;
        for (; j + 8 <= B[0].size(); j += 8) {
            __m256 acc = _mm256_setzero_ps();
            for (size_t k = 0; k < B.size(); ++k) {
                __m256 va = _mm256_set1_ps(A[i][k]);
                __m256 vb = _mm256_loadu_ps(&B[k][j]);
                acc = _mm256_add_ps(acc, _mm256_mul_ps(va, vb));
            }
            _mm256_storeu_ps(&C[i][j], acc);
        }
        for (; j < B[0].size(); ++j) {
            float s = 0.0f;
            for (size_t k = 0; k < B.size(); ++k) {
                s += A[i][k] * B[k][j];
            }
            C[i][j] = s;
        }
    }

    return C;
}

Matrix operator*(const Matrix& A, float scalar){
    Matrix C(A.size(), vec(A[0].size(), 0.0f));
    __m256 vs = _mm256_set1_ps(scalar);
    for (size_t i = 0; i < A.size(); ++i) {
        size_t j = 0;
        for (; j + 8 <= A[0].size(); j += 8){
            __m256 va = _mm256_loadu_ps(&A[i][j]);
            _mm256_storeu_ps(&C[i][j], _mm256_mul_ps(va, vs));
        }
        for (; j < A[0].size(); ++j) C[i][j] = A[i][j] * scalar;
    }
    return C;
}

Matrix operator*(float scalar, const Matrix& A){
    return A * scalar;
}

Matrix transpose(const Matrix &a){
  Matrix T(a[0].size(),vec(a.size()));
  for (size_t i = 0; i < a.size(); i++) {
    for (size_t j = 0; j < a[0].size(); j++) {
        T[j][i]=a[i][j];
    }
  }
  return T;
}

Matrix fill_random(size_t rows, size_t cols, float min, float max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dist(min, max);

    Matrix A(rows, vec(cols));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            A[i][j] = dist(gen);
        }
    }

    return A;
}

Matrix Hadamard(const Matrix &a,const Matrix &b){
    Matrix C(a.size(), vec(a[0].size()));
    for (size_t i = 0; i < a.size(); i++) {
        size_t j = 0;
        for (; j + 8 <= a[0].size(); j += 8){
            __m256 va = _mm256_loadu_ps(&a[i][j]);
            __m256 vb = _mm256_loadu_ps(&b[i][j]);
            _mm256_storeu_ps(&C[i][j], _mm256_mul_ps(va, vb));
        }
        for (; j < a[0].size(); j++) C[i][j] = a[i][j] * b[i][j];
    }
  return C;
}

Matrix pow_of(const Matrix& a , float n){
    Matrix C(a.size(), vec(a[0].size()));

    if (n == 2.0f) { 
        for (size_t i = 0; i < a.size(); i++) {
            size_t j = 0;
            for (; j + 8 <= a[0].size(); j += 8){
                __m256 va = _mm256_loadu_ps(&a[i][j]);
                _mm256_storeu_ps(&C[i][j], _mm256_mul_ps(va, va));
            }
            for (; j < a[0].size(); j++) C[i][j] = a[i][j] * a[i][j];
        }
        return C;
    }

    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a[0].size(); j++) {
            C[i][j] = pow(a[i][j], n);
        }
    }
    return C;
}

Matrix power(const Matrix& a , const Matrix& b){
  if(a.empty()||b.empty()||a.size()!=b.size()||a[0].size()!=b[0].size()){
    //throw ereur "invalid shape";
    throw invalid_argument("Matrix dimensions don't match");

    
  } 
    Matrix C(a.size(),vec(a[0].size()));
    for (size_t i = 0; i < a.size(); i++) {
      for (size_t j = 0; j < a[0].size(); j++) {
         C[i][j] =pow(a[i][j],b[i][j]);
      }
    }

  return C;
}
float avrg(const Matrix& a){
  float Sum = sum(a);
  float r = a.size(),c = a[0].size();
  float shape = r*c;
  return Sum/shape;
}



/*int main(){
      
  Matrix A = fill_random(5,5,0.f,0.5f);
  print(A);
  printf("-----------------\n");

   Matrix B = fill_random(5,5,-1.f,1.f);
      
   print(A*B);
   printf("sum = %.f\n",sum(A*B));
                  
  return 0;
}*/ 
