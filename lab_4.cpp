#include <iostream>
#include <cmath>


using namespace std;


const int N = 3;

int main(){
	double x[N], a[N][N], aT[N][N], b[N], A[N][N], d[N];
	double epsilon = 0.001;

	a[0][0] = 3.6; a[0][1] = 1.8; a[0][2] = -4.7;
	a[1][0] = 2.7; a[1][1] = -3.6; a[1][2] = 1.9;
	a[2][0] = 1.5; a[2][1] = 4.5; a[2][2] = 3.3;

	b[0] = 3.8; b[1] = 0.4; b[2] = -1.6;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			A[i][j] = 0;
		d[i] = 0;
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			aT[i][j] = a[j][i];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++)
				A[i][j] += aT[i][k] * a[k][j];
			d[i] += aT[i][j] * b[j];
		}


	x[0] = 0; x[1] = 0; x[2] = 0;

	double temp[N];
	bool trigger = false;
	int n1, n2, steps = 0;
	while (!trigger) {
		steps += 1;
		for (int i = 0; i < N; i++) {
			temp[i] = x[i]; 

			if (i == 0) { n1 = 1; n2 = 2; }
			else if (i == 1) { n1 = 0; n2 = 2; }
			else { n1 = 0; n2 = 1; }

			x[i] = d[i] / A[i][i] - (A[i][n1] / A[i][i])*x[n1] - (A[i][n2] / A[i][i])*x[n2];
		}

		double norm = 0;
		for (int i = 0; i < N; i++) 
			norm += pow(x[i] - temp[i], 2);

		if (sqrt(norm) < epsilon)
			trigger = true;
	}

	cout << "x = (";
	for (int i = 0; i < N - 1; i++)
		cout << x[i] << ", ";
	cout << x[N - 1] << ")T" << endl;
	cout << steps << " steps" << endl;

	system("pause");
	return 0;
}
