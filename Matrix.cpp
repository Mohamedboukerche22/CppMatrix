#include<bits/stdc++.h>
using namespace std;
using Matrix=vector<vector<float>>;
using vec=vector<float>;

void print(Matrix a){
  //printf("[");
    for (size_t i = 0; i < a.size(); i++) {
     for (size_t j = 0; j < a[0].size() ; j++) {
         printf("%.f ",a[i][j]);
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

Matrix zeros(Matrix a){
   for (size_t i = 0; i < a.size(); i++) {
     for (size_t j = 0; j < a[0].size() ; j++) {
         a[i][j]=0;
     }
   }
   return a;
}

Matrix ones(Matrix a){
   for (size_t i = 0; i < a.size(); i++) {
     for (size_t j = 0; j < a[0].size() ; j++) {
         a[i][j]=1;
     }
   }
   return a;
}

Matrix fill(Matrix a, int n){
   for (size_t i = 0; i < a.size(); i++) {
     for (size_t j = 0; j < a[0].size() ; j++) {
         a[i][j]=n;
     }
   }
   return a;
}

Matrix operator+(const Matrix& a , const Matrix& b){
  if(a.empty()||b.empty()||a.size()!=b.size()||a[0].size()!=b[0].size()){
    //throw ereur "invalid shape";
    Matrix h(1,vec(1)); 
    return fill(h,-1);
    
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
    Matrix h(1,vec(1)); 
    return fill(h,-1);
    
  } 
    Matrix C(a.size(),vec(a[0].size()));
    for (size_t i = 0; i < a.size(); i++) {
      for (size_t j = 0; j < a[0].size(); j++) {
         C[i][j]=a[i][j]-b[i][j];
      }
    }

  return C;
}
Matrix operator*(const Matrix& a , const Matrix& b){
  if(a.empty()||b.empty()||a.size()!=b.size()||a[0].size()!=b[0].size()){
    //throw ereur "invalid shape";
    Matrix h(1,vec(1)); 
    return fill(h,-1);
    
  } 
    Matrix C(a.size(),vec(a[0].size()));
    for (size_t i = 0; i < a.size(); i++) {
      for (size_t j = 0; j < a[0].size(); j++) {
         C[i][j]=a[i][j]*b[i][j];
      }
    }

  return C;
}
Matrix operator/(const Matrix& a , const Matrix& b){
  if(a.empty()||b.empty()||a.size()!=b.size()||a[0].size()!=b[0].size()){
    //throw ereur "invalid shape";
    Matrix h(1,vec(1)); 
    return fill(h,-1);
    
  } 
    Matrix C(a.size(),vec(a[0].size()));
    for (size_t i = 0; i < a.size(); i++) {
      for (size_t j = 0; j < a[0].size(); j++) {
         C[i][j]=(a[i][j])/(b[i][j]);
      }
    }
  return C;
}
Matrix power(const Matrix& a , const Matrix& b){
  if(a.empty()||b.empty()||a.size()!=b.size()||a[0].size()!=b[0].size()){
    //throw ereur "invalid shape";
    Matrix h(1,vec(1)); 
    return fill(h,-1);
    
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
int main(){
      Matrix a(5,vec(5));
      a=fill(a,1);
      print(a);
      Matrix b(5,vec(5));
      b=fill(b,4);
      print(b);
      Matrix X = a/b;
      print(X);
      print(pow_of(X,299));
      printf("sum = %.f\n",sum(X));
                  
  return 0;
}
