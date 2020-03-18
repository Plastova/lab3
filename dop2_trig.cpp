
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <string>
#include <sstream>

using namespace std;
#define pi 3.1415926
int n,count=0;
double* a,*z,*x,**y_arr, *b;
const unsigned int str = 177;
const unsigned int stolb = 14;

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
//int counter() - считает количество элементов <900 в выбранном столбце
void counter(double **y_arr, int c){
	for (int i = 0; i < str; i++) {
		if (y_arr[i][c] < 900)
			count++;			
	}
}
//void selectdata() - отбирает из двумерного массива значения <999.9 и пишет в одномерный массив, задает значения х в узлах (1,2,...,N)
void selectdata(double **y_arr,double *newy, double*x, int stl,int n){	   
	int p = 0;
	for (int i = 0; i < str; i++) {
		if (y_arr[i][stl] < 999.9) {
			newy[p] = y_arr[i][stl];
			p++;
		}	
	}	
	int j=0;
	for (int i=-n;i<n+1;i++){
      x[j]=2*pi*double(i)/double(2*(n)+1); 
      j++;
	}
}	


double A(int k){
	double sum=0;
	int j=0;
	for (int i=-n;i<n+1;i++)
		{	
		sum=sum+z[j]*cos(2*pi*double(k*i)/(2*n+1));
		j++;
		}
	if (k==0) return 1/double(2*n+1)*sum;
	return 2/double(2*n+1)*sum;
}

double B(int k){
	double sum=0;
	int j=0;
	for (int i=-n;i<n+1;i++)
		{
		sum=sum+z[j]*sin(2*pi*double(k*i)/double(2*n+1));
		j++;
		}
	return 2/double(2*n+1)*sum;
}

double interpolation(double x, double *koefcos, double*koefsin){
	double S=a[0];
	for (int i=1;i<count;i++) 
		{
		S=S+koefcos[i]*cos(double(i)*x)+koefsin[i]*sin(double(i)*x);
		}
	return S;
}


int main(){
	double** y_arr = new double* [str];
	for (int count = 0; count < str; count++)
		y_arr[count] = new double[stolb];
	readdata(y_arr);	
	int c;
	cout << "Выберите столбец 1-12:" << endl;
	cin >> c;
	
	counter(y_arr, c);
	n=(int)((count-1)/2);
	
	cout<<"В выбранном столбце определено "<<count<<" значений(ия) температуры."<<endl;
	z=new double[count];

	x=new double[150];
	selectdata(y_arr,z,x,c,n);
	
	//заполняем массив коэффициентов для косинусов
	a=new double [count];
	for (int k=0; k<n;k++)
	{
	a[k]=A(k);
	}
		
	//заполняем массив коэффициентов для синусов
	b=new double [count];
	for (int k=1; k<n;k++)
	{
	b[k]=B(k);
	}
	
	ofstream fout, foutuz;
	fout.open("tr.txt");
	
	double xx;
	for (double j=0;j<count;j+=0.1) //х изменяется на 0.1 при каждом шаге
		{
			
			xx=-pi+2*pi/count*j;
			fout<<xx<<" "<<interpolation(xx,a,b)<<endl;
		}
	foutuz.open("uzly_tr.txt");
	for (int j=0;j<count;j++)
		{
			foutuz<<x[j]<<" "<<z[j]<<endl;
		}
	cout<<"Файл создан. Для построения графика запустите graftrig.py"<<endl;
	fout.close();
	foutuz.close();	
	
	delete [] a;
	delete [] b;
	delete [] x;
	delete [] z;
	for (int count = 0; count < str; count++)
        delete []y_arr[count];
	return 0;
	}
