#include <iostream>
#include <cmath>


using namespace std;

double eps = 0.001;


double F(int num, double x, double y) {
	if (num == 1)
		return cos(x + 0.5) - y - 2;
	else
		return tan(x * y) - pow(x, 2);
}

double G(int num, double x, double y) {
	if (num == 1)
		return sin(y) - 2 * x - 1;
	else
		return 0.7 * pow(x, 2) + 2 * pow(y, 2) - 1;
}

double der_F_x(int num, double x, double y) {
	if (num == 1)
		return -sin(x + 0.5);
	else
		return y / pow(cos(x * y), 2) - 2 * x;
}

double der_F_y(int num, double x, double y) {
	if (num == 1)
		return -1;
	else
		return x / pow(cos(x * y), 2);
}

double der_G_x(int num, double x, double y) {
	if (num == 1)
		return -2;
	else
		return 1.4 * x;
}
double der_G_y(int num, double x, double y) {
	if (num == 1)
		return cos(y);
	else
		return 4 * y;
}

double determ(int num, double x, double y) {
	return der_F_x(num, x, y) * der_G_y(num, x, y) - der_F_y(num, x, y) * der_G_x(num, x, y);
}
double determ_x(int num, double x, double y) {
	return F(num, x, y) * der_G_y(num, x, y) - der_F_y(num, x, y) * G(num, x, y);
}
double determ_y(int num, double x, double y) {
	return der_F_x(num, x, y) * G(num, x, y) - F(num, x, y) * der_G_x(num, x, y);
}

void Newton(int num, double x, double y) {
	cout << "\tFunction" << num << ":\t\n";
	double a, b;
	int n = 0;
	bool trigger = false;
	while (!trigger) {
		n += 1;

		a = x;
		b = y;

		x = a - determ_x(num, a, b) / determ(num, a, b);
		y = b - determ_y(num, a, b) / determ(num, a, b);

		if (sqrt(pow(x - a, 2) + pow(y - b, 2)) < eps)
			trigger = true;
	}

	cout << "Root is (" << x << ", " << y << ")" << endl;
	cout << n << " steps\n" << endl;
}

int main() {
	double x = 0.5;
	double y = 0.5;

	Newton(1, x, y);
	Newton(2, x, y);
	
	system("pause");
	return 0;
}
