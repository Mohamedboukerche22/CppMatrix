#include<bits/stdc++.h>
using namespace std;
//using matrix = vector<vector<double>>;
//using vec = vector<double>;
const int N = 100;
class Matrix {
  private:
    int rows,cols;
    vector<vector<double>> data;

  public:
    Matrix(int r, int c) {
      rows = r;cols = c;
      data = vector<vector<double>>(r,vector<double>(c,0));
    }
    vector<double>& operator[](int i){
      return data[i];
    }
    void rand(double minValue = 0, double maxValue = 10) {
        random_device rd;mt19937 gen(rd());uniform_real_distribution<double> dist(minValue, maxValue);
        for (int i=0;i<rows;i++){for(int j=0;j<cols;j++) {
            data[i][j] = dist(gen);
            }
        }
    }
    Matrix operator+(const Matrix& b) const {
      if(rows!=b.rows||cols!=b.cols){
        throw invalid_argument("matrices must have same dimensions");
      }
      Matrix res(rows,cols);
      for(int i=0;i<rows;i++){for(int j=0;j<cols;j++){
        res.data[i][j]=data[i][j]+b.data[i][j];
      }}
      return res;
    }
    Matrix operator-(const Matrix& b) const {
      if(rows!=b.rows||cols!=b.cols){
        throw invalid_argument("matrices must have same dimensions");
      }
      Matrix res(rows,cols);
      for(int i=0;i<rows;i++){for(int j=0;j<cols;j++){
        res.data[i][j]=data[i][j]-b.data[i][j];
      }}
      return res;
    }
    Matrix operator*(const Matrix& b) const {
      if(rows!=b.rows||cols!=b.cols){
        throw invalid_argument("matrices must have same dimensions");
      }
      Matrix res(rows,cols);
      for(int i=0;i<rows;i++){for(int j=0;j<cols;j++){
        res.data[i][j]=data[i][j]*b.data[i][j];
      }}
      return res;
    }
    Matrix operator/(const Matrix& b) const {
      if(rows!=b.rows||cols!=b.cols){
        throw invalid_argument("matrices must have same dimensions");
      }
      Matrix res(rows,cols);
      for(int i=0;i<rows;i++){for(int j=0;j<cols;j++){
        res.data[i][j]=data[i][j]/b.data[i][j];
      }}
      return res;
    }
       
    void print()const{
      for(int i=0;i<rows;i++){for(int j=0;j<cols;j++){cout<<data[i][j]<<' ';}cout<<"\n";}
    }
};





int main(){
  Matrix A(4,4);
  Matrix B(4,4);
  A.rand(0,10);
  B.rand(0,5);
  cout <<"Addition operation results :\n";
  Matrix C = A+B;
  cout <<"A -- Matrix\n";
  A.print();
  cout <<"B -- Matrix\n";
  B.print();
  cout<<"C -- Matrix\n";
  C.print();
  cout <<"-\n";
  C = A-B;
  C.print();
  C = A*B;
  C.print();
  C = A/B;
  C.print();

}
