#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <clocale>


//task_3
// структура для описания матрицы
struct Matrix {
	int m; // размерность
	std::vector <std::vector<long double>> mtx; // матрица
};

// перегрузка оператора вывода для матриц
std::ostream& operator << (std::ostream& out, const Matrix& a) {
	for (int i = 0; i < a.m; ++i) {
		for (int j = 0; j < a.m; ++j) {
			out << std::setw(6) << a.mtx[i][j];
		}
		out << "\n";
	}
	return out;
}


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

// функция для построения матрицы энергий
Matrix create_energy_matrix(const Matrix& mtrx) {
	std::vector <std::vector<long double>> energy_matrix;

	for (int i = 0; i < mtrx.m; ++i) {
		std::vector <long double> line_of_matrix = {};
		for (int j = 0; j < mtrx.m; ++j) {
			double d = mtrx.mtx[i][j];
			if (d == 0)
				line_of_matrix.push_back(0);
			else {
				line_of_matrix.push_back(round((1 / pow(d, 12) - 1 / pow(d, 6)) * 100) / 100);
				// std::cout << 1 / pow(d, 12) - 1 / pow(d, 6) << "\n"; // без округления
			}
		}
		energy_matrix.push_back(line_of_matrix);
	}

	return { mtrx.m, energy_matrix };
}

// функция для вычисления вероятнсти матрицы энергий
double probability_energy(const Matrix& mtrx) {
	double pairs = 0;
	for (int i = 0; i < mtrx.m; ++i) {
		for (int j = i; j < mtrx.m; ++j) {
			if (mtrx.mtx[i][j])
				++pairs;
		}
	}
	// std::cout << pairs << "\n"; // кол-во пар
	return pairs/mtrx.m;
}


int main()
{
	setlocale(LC_CTYPE, "rus");
    std::cout << "Практическая работа №2, команда 2.\n\n";






//task_3	
	// входная матрица
	Matrix m_1 = { 8, { {0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 11.1, 0, 0, 0, 0},
						{0, 0, 0, 0, 11.5, 0, 0, 0},
						{0, 11.1, 0, 0, 0, 0, 0, 0},
						{0, 0, 11.5, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 11.5, 0},
						{0, 0, 0, 0, 0, 11.5, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0} }
	};

	// вывод входной матрицы
	std::cout << "Входная матрица:\n";
	std::cout << m_1 << "\n";

	// создание матрицы энергий
	Matrix m_1_energy = {create_energy_matrix(m_1)};

	// вывод матрицы энергий
	std::cout << "Матрица энергий:\n";
	std::cout << m_1_energy << "\n";

	// вероятность матрицы энергий
	double m_1_probability = probability_energy(m_1);
	std::cout << "Вероятность матрицы энергий:\n";
	std::cout << m_1_probability << "\n";



/*
	//создание двумерного массива
	int m = 8;
	double** matrix_v_2 = new double* [m];
	for (int i = 0; i < m; i++) {
		matrix_v_2[i] = new double[m];
	}

	//	matrix_v_2[m][m] = {{1, 2, 0.5}, {0.6, 0.7, 0.8}, {0.9, 0.65, 0.84}};
	//	1 2 0.5 0.6 0.7 0.8 0.9 0.65 0.84
	//  0 0 0 0 0 0 0 0 0 0 0 11.1 0 0 0 0 0 0 0 0 11.5 0 0 0 0 11.1 0 0 0 0 0 0 0 0 11.5 0 0 0 0 0 0 0 0 0 0 0 11.5 0 0 0 0 0 0 11.5 0 0 0 0 0 0 0 0 0 0
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cin >> matrix_v_2[i][j];
		}
	}
	std::cout << "\n";

	// вывод входной матрицы
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cout << std::setw(6) << matrix_v_2[i][j];
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	double** energy_matrix = create_energy_matrix(matrix_v_2, m);

	//	вывод матрицы энергий
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cout << energy_matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	for (int i = 0; i < m; i++) delete[] matrix_v_2[i];
	delete[] matrix_v_2;

	for (int i = 0; i < m; i++) delete[] energy_matrix[i];
	delete[] energy_matrix;
*/ 

	//task 2
	using namespace std;
	const int R = 5;
	int sum[R] = { 0 };// Массив Суммы
	//созадание двухмерного массива
	int** a = new int* [R];
	for (int i = 0; i < R; i++)
		a[i] = new int[R];
	//Нахождение валентности и связи узлов
	for (int i = 0; i < R; i++)
		for (int j = 0; j < R; j++)
		{
			if (a[i][j] = 1) a[i][j] = -1;
			sum[i] += abs(a[i][j]);
		}
	for (int i = 0; i < R; i++)
		for (int j = 0; j < R; j++)
			if (i == j) a[i][j] = sum[i]-1;
	//вывод матрицы Киргофа
	cout << "Матрица Киргофа:";
	cout << "\n";
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < R; ++j) {
			cout << setw(6) << a[i][j];
		}
		cout << "\n";
	}


//вычисление вероятности валентности узлов 
	double P[R];
	for (int i = 0; i < R; i++)
	{
		P[i] = static_cast<double>(4) / R;
	}
	cout << "Вероятности валентности:";
	for (int i = 0; i < R; i++)
		cout << P[i] << " ";

 


	return 0;
}
