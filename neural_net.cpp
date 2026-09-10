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
Matrix operator*(const Matrix& a, float scalar);
Matrix operator*(float scalar, const Matrix& a);

Matrix fill_matrix(size_t r, size_t c, float v);
Matrix pow_of(const Matrix& a , float n);
Matrix Hadamard(const Matrix& a, const Matrix& b);
float avrg(const Matrix& a);


pair<Matrix,Matrix> generate_data(){
  Matrix X=fill_random(5,5,0.0f,1.0f);
  Matrix y = X + fill_matrix(5,5,12.f);
  return {X,y};
}


int main(){
  auto [X,y] = generate_data();
  float W=0.5f,b=0.0f;              
  float lr=0.01f,N=25.0f; 

  for(size_t epoch=0; epoch<2000; epoch++){
    Matrix y_pred = X * W + fill_matrix(5,5,b);
    Matrix diff = y_pred - y;
    if(epoch % 200 == 0){
      printf("epoch %zu | loss: %.6f\n", epoch, sum(pow_of(diff,2.0f))/N);
    }
    float dW = (2.f/N) * sum(Hadamard(diff, X));
    float db = (2.f/N) * sum(diff);
    W = W - lr * dW;
    b = b - lr * db;
  }

  printf("W = %.4f | b = %.4f\n", W, b);
  printf("Y = %.4f * X + %.4f\n",std::round(W),std::round(b));
  /*
   * -------------- " output example" run almost perfect 
epoch 0 | loss: 150.191849
epoch 200 | loss: 1.109317
epoch 400 | loss: 0.645405
epoch 600 | loss: 0.377108
epoch 800 | loss: 0.220342
epoch 1000 | loss: 0.128745
epoch 1200 | loss: 0.075225
epoch 1400 | loss: 0.043954
epoch 1600 | loss: 0.025682
epoch 1800 | loss: 0.015006
W = 1.3173 | b = 11.8269
Y = 1.0000 * X + 12.0000

   * */

 // printf("f(x) = W*X + b (predicted) ==>");print(X * W + fill_matrix(5,5,b));
 // printf("y (actual) ==>");print(y);
 // printf("ans = %.4f (expected %.4f)\n", W*X[0][0] + b, y[0][0]);
}
