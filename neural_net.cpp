#include <bits/stdc++.h>
using namespace std; 
using Matrix=vector<vector<float>>;

// define all function from "Matrix.cpp"
Matrix fill_random(size_t rows, size_t cols, float min, float max);
void print(Matrix a);
float sum(Matrix a);
Matrix zeros(size_t r, size_t c);

Matrix operator+(const Matrix& a , const Matrix& b);
Matrix operator-(const Matrix& a , const Matrix& b);
Matrix operator*(const Matrix& a , const Matrix& b);
Matrix operator/(const Matrix& a , const Matrix& b);

Matrix fill_matrix(size_t r, size_t c, float v);
Matrix power(const Matrix& a , const Matrix& b);
Matrix transpose(const Matrix &a);



pair<Matrix,Matrix> generate_data(){
  Matrix X=fill_random(5,5,0.0f,1.0f);
  Matrix y = X + fill_matrix(5,5,5.f);
  return {X,y};
}


int main(){
   auto [X,y] = generate_data();
  //print(X);print(y);
  Matrix W=fill_random(5,5,-1.f,1.f);
  Matrix b=zeros(5,5);
  float lr=0.01f,n_sample = 5.f;
  for(size_t epoch=0;epoch<7000;epoch++){
    Matrix y_pred = X * W + b;
    Matrix loss = power(y_pred-y,fill_matrix(y.size(),y[0].size(),2.f));
    print(loss);
    printf(" = epoche %d=\n",epoch);
    Matrix dW = fill_matrix(y.size(),y[0].size(),(2/n_sample)) * (transpose(X) * (y_pred-y));
    float db = (2/n_sample) * (sum(y_pred-y));
    W = W - fill_matrix(5,5,lr)*dW;
    b = b - fill_matrix(5,5,lr*db);
  }

  //printf("w ==>");print(W);
  //printf("b ==>");print(b);
  printf("ans = %.4f (expected %.4f)\n", X[0][0]*sum(W)/(5*5)+sum(b)/(5*5), X[0][0]+5);


  
  
}

