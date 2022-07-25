#include <iostream>
#include <cmath>

//task_3
/*
double** create_energy_matrix(double** matrix_v_2, const int m) {
	double** energy_matrix = new double* [m];
	for (int i = 0; i < m; i++) {
		energy_matrix[i] = new double[m];
	}

	// построение матрицы энергий
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			double d = matrix_v_2[i][j];
			if (d == 0)
				energy_matrix[i][j] = 0;
			else
				energy_matrix[i][j] = round((1 / pow(d, 12) - 1 / pow(d, 6)) * 100) / 100;
		}
	}

	return energy_matrix;
}
*/

int main()
{
    std::cout << "Hello World!\n";







/*
//task_3	
	//создание двумерного массива
	int m = 3;
	double** matrix_v_2 = new double* [m];
	for (int i = 0; i < m; i++) {
		matrix_v_2[i] = new double[m];
	}

	//	matrix_v_2[m][m] = {{1, 2, 0.5}, {0.6, 0.7, 0.8}, {0.9, 0.65, 0.84}};
	//	1 2 0.5 0.6 0.7 0.8 0.9 0.65 0.84
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cin >> matrix_v_2[i][j];
		}
	}

	// вывод входной матрицы
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			std::cout << matrix_v_2[i][j] << " ";
		}
		std::cout << "\n";
	}

	double** energy_matrix = create_energy_matrix(matrix_v_2, m);

	//	вывод матрицы энергий
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			std::cout << energy_matrix[i][j] << " ";
		}
		std::cout << "\n";
	}

	for (int i = 0; i < m; i++) delete[] matrix_v_2[i];
	delete[] matrix_v_2;

	for (int i = 0; i < m; i++) delete[] energy_matrix[i];
	delete[] energy_matrix;
*/
}
