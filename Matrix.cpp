#include<bits/stdc++.h>
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
     for (size_t j = 0; j < a[0].size() ; j++) {
         Sum+=a[i][j];
     }
     
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

Matrix operator+(const Matrix& a , const Matrix& b){
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
}
Matrix operator-(const Matrix& a , const Matrix& b){
  if(a.empty()||b.empty()||a.size()!=b.size()||a[0].size()!=b[0].size()){
    //throw ereur "invalid shape";
    throw invalid_argument("Matrix dimensions don't match");

    
  } 
    Matrix C(a.size(),vec(a[0].size()));
    for (size_t i = 0; i < a.size(); i++) {
      for (size_t j = 0; j < a[0].size(); j++) {
         C[i][j]=a[i][j]-b[i][j];
      }
    }

  return C;
}
// useless function let use it to calc matmul

/*Matrix operator*(const Matrix& a , const Matrix& b){
  if(a.empty()||b.empty()||a.size()!=b.size()||a[0].size()!=b[0].size()){
    //throw ereur "invalid shape";
    throw invalid_argument("Matrix dimensions don't match");
    
  } 
    Matrix C(a.size(),vec(a[0].size()));
    for (size_t i = 0; i < a.size(); i++) {
      for (size_t j = 0; j < a[0].size(); j++) {
         C[i][j]=a[i][j]*b[i][j];
      }
    }

  return C;
}*/

Matrix operator*(const Matrix& A, const Matrix& B) {
    if (A.empty() || B.empty()) {
        throw invalid_argument("Cannot multiply empty matrices");
    }

    if (A[0].size() != B.size()) {
        throw invalid_argument("Invalid matrix dimensions for multiplication");
    }

    Matrix C(A.size(), vec(B[0].size(), 0.0f));

    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < B[0].size(); ++j) {
            for (size_t k = 0; k < B.size(); ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}



Matrix operator/(const Matrix& a , const Matrix& b){
  if(a.empty()||b.empty()||a.size()!=b.size()||a[0].size()!=b[0].size()){
    //throw ereur "invalid shape";
    throw invalid_argument("Matrix dimensions don't match");

    
  } 
    Matrix C(a.size(),vec(a[0].size()));
    for (size_t i = 0; i < a.size(); i++) {
      for (size_t j = 0; j < a[0].size(); j++) {
         C[i][j]=(a[i][j])/(b[i][j]);
      }
    }
  return C;
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
    if(a.empty()||b.empty()||a.size()!=b.size()||a[0].size()!=b[0].size()){
    //throw ereur "invalid shape";
    throw invalid_argument("Matrix dimensions don't match");
    } 
    Matrix C(a.size(),vec(a[0].size()));
    for (size_t i = 0; i < a.size(); i++) {
      for (size_t j = 0; j < a[0].size(); j++) {
         C[i][j]=(a[i][j])*(b[i][j]);
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
Matrix pow_of(const Matrix& a , float n){
    Matrix C(a.size(),vec(a[0].size()));
    for (size_t i = 0; i < a.size(); i++) {
      for (size_t j = 0; j < a[0].size(); j++) {
         C[i][j]=pow(a[i][j],n);
      }
    }

  return C;
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
