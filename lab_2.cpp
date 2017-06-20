#include <iostream>
#include <cmath>


using namespace std;


double eps = 0.001;


double F(int i, double x) {
	if (i == 1)
		return (2 - x) * exp(x) - 0.5;
	else
		return pow(x, 3) + 3 * pow(x, 2) + 12 * x + 3;
}

void Fixed_point_iteration(int num_of_func, double(*func) (int, double), double x, double L) {
	int n = 0;
	double x_old;
	do{
		n++;
		x_old = x;
		x = x_old - L * func(num_of_func, x_old);
	} while (abs(x - x_old) >= eps);
	cout << x << endl;
	cout << n << " steps at all\n" << endl;
}

int main(){
	const int count_of_roots[] = { 2, 1 };
	double X_0 = 0, L = 0.01;
	for (int num_of_func = 1; num_of_func < 3; num_of_func++) {
		cout << "\tFunction" << num_of_func << ":\t\n";
		for (int i = 1; i <= count_of_roots[num_of_func - 1]; i++) {
			cout << "Root " << i << " is ";
			if (i == 1 && num_of_func == 1) {
				X_0 = -2;
				L = 0.3;
			}
			else if (i == 2 && num_of_func == 1){
				X_0 = 1.5;
				L = -0.1;
			}
			else {
				X_0 = 0;
				L = 0.1;
			}
			Fixed_point_iteration(num_of_func, F, X_0, L);
		}
		cout << "\n";
	}
	
	system("pause");
	return 0;
}
