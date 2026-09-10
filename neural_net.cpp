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
Matrix operator*(const Matrix& a, float scalar);


Matrix fill_matrix(size_t r, size_t c, float v);
Matrix power(const Matrix& a , const Matrix& b);
Matrix pow_of(const Matrix& a , float n);
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
  for(size_t epoch=0;epoch<500;epoch++){
    Matrix y_pred = X * W + b;
    Matrix diff = y_pred - y;
    if(epoch % 100 == 0){
      printf("epoch %d | loss: %.6f\n", epoch, sum(pow_of(diff,2.0f))/25);
    }
    Matrix dW = (transpose(X) * (y_pred-y)) * (2.f/n_sample);
    Matrix db = (y_pred-y) * (2.f/n_sample);
    W = W - dW * lr;
    b = b - db * lr;
  }

  //printf("w ==>");print(W);
  //printf("b ==>");print(b);
  printf("ans = %.4f (expected %.4f)\n", (X*W+b)[0][0], X[0][0]+5);

  
}
