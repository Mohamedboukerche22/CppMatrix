#include<bits/stdc++.h>
using namespace std;               
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
class Activation {
  public :
    static double sigmoid(double x){
      return (1.0/(1.0 + exp(-x)));
    }
    static double sigmoidDerivative(double x){
      double s = sigmoid(x); return (s)*(1.0-s);
    }
    static double tanh(double x){
      return (exp(x)-exp(-x))/(exp(x)+exp(-x));
    }
    static double tanhDerivative(double x){
      double t=tanh(x);return (1.0- t*t);
    }
    static double relu(double x){
      return max(0.0,x);
    }
    static double reluDerivative(double x){
      return (x > 0.0)? 1.0:0.0;
    }
    static double leakyRelu(double x,double alpha=0.01){
      return (x > 0.0)? x : alpha*x;
    }
    static double leakyReluDerivative(double x,double alpha=0.01){
      return (x > 0.0)? 1.0 : alpha;
    }
      //def my_tanh(x):
     //  return (math.exp(x)-math.exp(-x))/(math.exp(x)+math.exp(-x))

    static vector<double>softmax(vector<double>&input){int n=input.size();vector<double>output(n);
      double max_val=*max_element(input.begin(),input.end());double sum=0.0;
      for(size_t i=0;i<n;i++){output[i]=exp(input[i]-max_val);sum+=output[i];}
      for(size_t i=0;i<n;i++){output[i] /= sum;}
      return output;
    }
    static double elu(double x,double alpha=1.0){
      return (x>0.0)? x:alpha*(exp(x)-1.0);
    }
    static double eluDerivative(double x,double alpha=1.0){
      return (x>0.0)? 1.0:alpha*exp(x);
    }
};
class VectorActivation{
  public:
  static vector<double>applySigmoid(const vector<double>& input){
    int n=input.size();vector<double>output(n);
    for (size_t i=0;i<n;i++) {output[i]=Activation::sigmoid(input[i]);}
    return output;
  }
  static vector<double>applyRELU(const vector<double>& input){
    int n=input.size();vector<double>output(n);
    for (size_t i=0;i<n;i++) {output[i]=Activation::relu(input[i]);}
    return output;
  }
  static vector<double>applyTanh(const vector<double>& input){
    int n=input.size();vector<double>output(n);
    for (size_t i=0;i<n;i++) {output[i]=Activation::tanh(input[i]);}
    return output;
  }

};

int main(){
  double x=2.0;
  vector<double> input = {2.0,3.0,5.5,6.6,12.2,19.5,11.0};
  for (double v : input)cout<<v<<" ";
  cout <<"\n";
  vector<double> softmax_result = Activation::softmax(input);
  for (double v : softmax_result)cout<<v<<" ";
  cout<<"\n";
  vector<double> sigmoid_result = VectorActivation::applySigmoid(input);
  cout << "Sigmoid vector: ";
    for (double v : sigmoid_result) cout<<v<<" ";
    cout<<"\n";
 vector<double> relu_result = VectorActivation::applyRELU(input);
  cout << "relu vector: ";
    for (double v : relu_result) cout<<v<<" ";
    cout<<"\n";

 vector<double> tanh_result= VectorActivation::applyTanh(input);
  cout << "tanh vector: ";
    for (double v : tanh_result) cout<<v<<" ";
    cout<<"\n";

  }
