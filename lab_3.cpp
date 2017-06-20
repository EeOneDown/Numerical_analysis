#include <iostream>
#include <cmath>


using namespace std;


int main(){
	double a[4][4], b[4], x[4], x_old[4];
	double eps = 0.001;

	a[0][0] = 0.19; a[0][1] = -0.07; a[0][2] = 0.38; a[0][3] = -0.21;
	a[1][0] = -0.22; a[1][1] = 0.08; a[1][2] = 0.11; a[1][3] = 0.33;
	a[2][0] = 0.51; a[2][1] = -0.07; a[2][2] = 0.09; a[2][3] = -0.11;
	a[3][0] = 0.33; a[3][1] = -0.41; a[3][2] = 0; a[3][3] = 0;

	b[0] = -0.81; b[1] = -0.64; b[2] = 1.71; b[3] = -1.21;


	x_old[0] = 0; x_old[1] = -1; x_old[2] = 2; x_old[3] = -1;

	x[0] = 0; x[1] = 0; x[2] = 0; x[3] = 0;
	bool trigger = false;
	double norm = 0;
	int n = 0;
	while (!trigger){
		n++;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				x[i] += a[i][j] * x_old[j];
			x[i] += b[i];
		}
		for (int i = 0; i < 4; i++) 
			norm += pow(x[i] - x_old[i], 2);
		norm = sqrt(norm);
		if (norm < eps) 
			trigger = true;
		else
			norm = 0;
		for (int i = 0; i < 4; i++) {
			x_old[i] = x[i];
			x[i] = 0;
		}
	}
	
	cout << "x = (";
	for (int i = 0; i < 3; i++)
		cout << x_old[i] << ", ";
	cout << x_old[3] << ")T" << endl;
	cout << n << " steps" << endl;
	
	system("pause");
	return 0;
}
