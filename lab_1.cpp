#include <iostream>
#include <cmath>


using namespace std;


const int N = 4;
double eps = 0.01;


double F(int i, double x) {
	if (i == 1)
		return pow(3, x - 1) - 2 - x;
	else if (i == 2)
		return 3 * pow(x, 4) + 8 * pow(x, 3) + 6 * pow(x, 2) - 10;
	else if (i == 3)
		return pow(x - 4, 2) * log(x - 3) / log(0.5) + 1;
	else if (i == 4)
		return 5 * sin(x) - x; 
	else {
		i = rand() % 4 + 1;
		return F(i, x);
	}
};


double der_1_F(int i, double x) {
	if (i == 1)
		return pow(3, x - 1) * log(3) - 1;
	else if (i == 2)
		return 12 * x * pow(x + 1, 2);
	else if (i == 3)
		return 1 / log(0.5) * (2 * (x - 4) * log(x - 3) + pow(x - 4, 2) / (x - 3));
	else if (i == 4)
		return 5 * cos(x) - 1;
	else {
		i = rand() % 4 + 1;
		return der_1_F(i, x);
	}
};


double der_2_F(int i, double x) {
	if (i == 1)
		return pow(3, x - 1) * pow(log(3), 2);
	else if (i == 2)
		return 12 * (3 * pow(x, 2) + 4 * x + 1);
	else if (i == 3)
		return 1 / log(0.5) * (3 * pow(x, 2) - 20 * x + 2 * pow(x - 3, 2) * log(x - 3) + 32) / pow(x - 3, 2);
	else if (i == 4)
		return -5 * sin(x);
	else {
		i = rand() % 4 + 1;
		return der_2_F(i, x);
	}
};


void Dichotomy(int num_of_func, double(*func) (int, double), double a[], double b[], int count_of_roots) {
	cout << "Dichotomy\n";
	int n = 0; 
	double ksi; 
	for (int i = 0; i < count_of_roots; i++) {
		while (abs(b[i] - a[i]) >= eps) {
			n++;
			ksi = (a[i] + b[i]) / 2;
			if (func(num_of_func, a[i]) * func(num_of_func, ksi) < 0)
				b[i] = ksi;
			else
				a[i] = ksi;
		}
		ksi = (a[i] + b[i]) / 2;
		cout << "Root "<< i + 1 << " is " << ksi << endl;
	}
	cout << n << " steps" << endl << "\n" << endl;
};


void Method_of_chords(int num_of_func, double(*func) (int, double), double a[], double b[], int count_of_roots){
	cout << "Method of chords\n";
	int n = 0;
	double ksi;
	for (int i = 0; i < count_of_roots; i++){
		bool trigger = false;
		ksi = a[i] - func(num_of_func, a[i])*(b[i] - a[i]) / (func(num_of_func, b[i]) - func(num_of_func, a[i]));
		if (func(num_of_func, a[i]) * func(num_of_func, ksi) > 0){
			while (!trigger){
				n++;
				a[i] = ksi;
				ksi = a[i] - func(num_of_func, a[i])*(b[i] - a[i]) / (func(num_of_func, b[i]) - func(num_of_func, a[i]));
				if (abs((ksi - a[i])) < eps)
					trigger = true;
			}
		}
		else{
			while (!trigger){
				n++;
				b[i] = ksi;
				ksi = a[i] - func(num_of_func, a[i])*(b[i] - a[i]) / (func(num_of_func, b[i]) - func(num_of_func, a[i]));
				if (abs((ksi - b[i])) < eps)
					trigger = true;
			}
		}
		cout << "Root " << i + 1 << " is " << ksi << endl;
	}
	cout << n << " steps" << endl << "\n" << endl;
};


void Newton(int num_of_func, double(*func) (int, double), double a[], double b[], int count_of_roots){
	cout << "Newton\n";
	int n = 0;
	double ksi, delta;
	for (int i = 0; i < count_of_roots; i++){
		bool trigger = false;
		if (func(num_of_func, a[i]) * der_2_F(num_of_func, a[i]) > 0)
			ksi = a[i];
		else
			ksi = b[i];
		while (!trigger){
			n++;
			delta = func(num_of_func, ksi) / der_1_F(num_of_func, ksi);
			ksi = ksi - delta;
			if (abs(delta) < eps)
				trigger = true;
		}
		cout << "Root " << i + 1 << " is " << ksi << endl;
	}
	cout << n << " steps" << endl << "\n" << endl;
};


void Newton_plus_chords(int num_of_func, double(*func) (int, double), double a[], double b[], int count_of_roots){
	cout << "Newton_plus_chords\n";
	int n = 0;
	for (int i = 0; i < count_of_roots; i++){
		bool trigger = false;
		while (!trigger){
			n++;
			if (func(num_of_func, a[i]) * der_2_F(num_of_func, a[i]) < 0){
				a[i] = a[i] - func(num_of_func, a[i])*(a[i] - b[i]) / (func(num_of_func, a[i]) - func(num_of_func, b[i]));
			}
			else{
				a[i] = a[i] - func(num_of_func, a[i]) / der_1_F(num_of_func, a[i]);
			}
			if (func(num_of_func, b[i]) * der_2_F(num_of_func, b[i]) < 0){
				b[i] = b[i] - func(num_of_func, b[i])*(b[i] - a[i]) / (func(num_of_func, b[i]) - func(num_of_func, a[i]));
			}
			else{
				b[i] = b[i] - func(num_of_func, b[i]) / der_1_F(num_of_func, b[i]);
			}

			if (abs(a[i] - b[i]) < 2 * eps)
				trigger = true;
		}
		cout << "Root " << i + 1 << " is " << (a[i] + b[i]) / 2 << endl;
	}
	cout << n << " steps" << endl << "\n" << endl;
};


int main(){
	const int count_of_roots[] = { 2, 2, 1, 3 };
	double a[N], b[N];
	for (int num_of_func = 1; num_of_func < 5; num_of_func++) {
		if (num_of_func == 1){
			a[0] = -2.1; a[1] = 2;
			b[0] = -1.5; b[1] = 2.5;
		}
		else if (num_of_func == 2) {
			a[0] = -2.5; a[1] = 0.5;
			b[0] = -1.5; b[1] = 1;
		}
		else if (num_of_func == 3) {
			a[0] = 4.8;
			b[0] = 5.2;
		}
		else {
			a[0] = -3; a[1] = -0.1; a[2] = 2.5;
			b[0] = -2.5; b[1] = 0.1; b[2] = 3;
		}
		cout << "\tFunction" << num_of_func << ":\t\n";
		Dichotomy(num_of_func, F, a, b, count_of_roots[num_of_func - 1]);
		Method_of_chords(num_of_func, F, a, b, count_of_roots[num_of_func - 1]);
		Newton(num_of_func, F, a, b, count_of_roots[num_of_func - 1]);
		Newton_plus_chords(num_of_func, F, a, b, count_of_roots[num_of_func - 1]);
	}
	
	system("pause");
    return 0;
}
