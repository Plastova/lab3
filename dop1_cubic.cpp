#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int N=11, indefcount=0;
const unsigned int str = 177;
const unsigned int stolb = 14;
double *h, *l, *delta, *lambda, *c, *d, *b;
double* x = new double[N+1];
double* z = new double[N+1];

//void readdata() - читает в двумерный массив данные из таблицы
void readdata(double **y_arr){
	fstream fin;
	fin.open("data.csv", ios::in);
	string line, word;
	getline(fin, line);
	for (int count_row = 0; count_row < str; count_row++) {
		getline(fin, line);
		stringstream s(line);
		for (int count_column = 0; count_column < stolb; count_column++) {
			getline(s, word, ',');
			y_arr[count_row][count_column] = stof(word);
		}
	}
}
//int counter() - считает количество элементов >900
int counter(double **y_arr){
	int c;
	cout << "Выберите столбец" << endl;
	cin >> c;
	for (int i = 0; i < str; i++) {
		if (y_arr[i][c] > 900)
			indefcount++;		
	}	 
		return c;
}

//void selectdata() - отбирает из двумерного массива значения <999.9 и пишет в одномерный массив, задает значения х в узлах (1,2,...,N)
void selectdata(double **y_arr,double *newy,double*x, int stl){	    
	int p = 0;
	for (int i = 0; i < str; i++) {
		if (y_arr[i][stl] < 999.9) {
			newy[p] = y_arr[i][stl];
			p++;
		}	
	}	
	for(int i=0; i<N+1; i++){
      x[i]=i; 
   }	
}

void allocmatrix(){
   h = new double [N+1];
   l = new double [N+1];
   delta = new double [N+1];
   lambda = new double [N+1];
   c = new double [N+1];
   d = new double [N+1];
   b = new double [N+1];
}
void delmatrix(){ 
   delete [] z;
   delete [] x;
   delete [] h;
   delete [] l;
   delete [] delta;
   delete [] lambda;
   delete [] c;
   delete [] d;
   delete [] b;
}

void printresult(double *z){
   int k=0;
   cout<<"\nA[k]       B[k]       C[k]       D[k]\n";
   for(k=1; k<=N; k++){
       cout<<z[k]<<"     "<<b[k]<<"     "<<c[k]<<"     "<<d[k]<<endl;
   }
   cout<<endl;
}
void countpoints(double *x, double *y, double*b, double*c,double*d){
	int k;
	ofstream fout;
	fout.open("cubic.txt");
	for(double s = 0; s<=N; s+= 0.1){
       for(k=1; k<=N; k++){
		   if(s>=x[k-1] && s<=x[k]){	    
			   break;
		   }
		}   
		
       double F = y[k] + b[k]*(s-x[k]) + c[k]*pow(s-x[k], 2) + d[k]*pow(s-x[k], 3);
       cout<<s<<" "<<F<<endl; 
       fout<<s<<" "<<F<<endl;  
      }
   fout.close();
}


int main(){
	double** y_arr = new double* [str];
	for (int count = 0; count < str; count++)
		y_arr[count] = new double[stolb];
		
	readdata(y_arr);
	int stl;
	stl=counter(y_arr);

	double* newy = new double[str - indefcount];
	selectdata(y_arr,newy,x,stl);
	
	cout<<"Выберите начальный элемент от 0 до "<< str - indefcount-12<<endl;
	int start;
	cin>>start;
	
	//из всех подходящих игреков выбираем нужное нам кол-во, начиная с выбранного элемента и пишем в z[]
	for (int i=0; i<=N; i++){
		z[i]=newy[start+i];
		}
	allocmatrix();//выделяем память под массивы коэффициентов
	
	//считаем коэффициенты
	int k=0;
	for(k=1; k<=N; k++){
       h[k] = x[k] - x[k-1];
       l[k] = (z[k] - z[k-1])/h[k];
	}
   delta[1] = - h[2]/(2*(h[1]+h[2]));
   lambda[1] = 1.5*(l[2] - l[1])/(h[1]+h[2]);
   for(k=3; k<=N; k++){
      delta[k-1] = - h[k]/(2*h[k-1] + 2*h[k] + h[k-1]*delta[k-2]);
      lambda[k-1] = (3*l[k] - 3*l[k-1] - h[k-1]*lambda[k-2])/(2*h[k-1] + 2*h[k] + h[k-1]*delta[k-2]);
   }
   c[0] = 0;
   c[N] = 0;
   for(k=N; k>=2; k--){
      c[k-1] = delta[k-1]*c[k] + lambda[k-1];
   }
   for(k=1; k<=N; k++){
      d[k] = (c[k] - c[k-1])/(3*h[k]);
      b[k] = l[k] + (2*c[k]*h[k] + h[k]*c[k-1])/3;
   }
   
   printresult(z);
   countpoints(x,z,b,c,d);
 
	  //пишем узлы в отдельный файл, чтоб нарисовать их точками на графике
   ofstream fout1;
	fout1.open("uzly.txt");
	for(int p=0;p<=N;p++){
		fout1 << x[p] << " " << z[p] << endl;
	}
	cout<<"Файл создан. Для построения графика запустите grafcub.py"<<endl;
	delmatrix();
	for (int count = 0; count < str; count++)
        delete []y_arr[count];

	return 0;
}
