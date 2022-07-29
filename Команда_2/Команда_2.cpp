#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <clocale>
#include <map>
#include <fstream>
#include <list>
#include <string>
#include <math.h>

//task_3
// структура для описания матрицы
struct Matrix {
	int m; // размерность
	std::vector <std::vector<double>> mtx; // матрица
};

// тестовая входная матрица
Matrix m_1 = { 8, { {0, 20, 0, 0, 0, 0, 0, 0},
					{20, 0, 0, 11.1, 0, 0, 0, 0},
					{0, 0, 0, 0, 11.5, 0, 0, 0},
					{0, 11.1, 0, 0, 0, 0, 0, 0},
					{0, 0, 11.5, 0, 0, 0, 0, 0},
					{0, 0, 0, 0, 0, 0, 11.5, 0},
					{0, 0, 0, 0, 0, 11.5, 0, 20},
					{0, 0, 0, 0, 0, 0, 20, 0} }
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

// функция поиска минимума и максимума матрицы
// .first - минимум, .second - максимум
std::pair <double, double> min_max(const Matrix& a) {
	double min = a.mtx[0][0];
	double max = min;
	for (int i = 0; i < a.m; ++i) {
		for (int j = 0; j < a.m; ++j) {
			if (min > a.mtx[i][j]) {
				min = a.mtx[i][j];
			}
			if (max < a.mtx[i][j]) {
				max = a.mtx[i][j];
			}
		}
	}

	return std::make_pair(min, max);
}

// функция для построения матрицы энергий
Matrix create_energy_matrix(const Matrix& mtrx) {
	std::vector <std::vector<double>> energy_matrix; // результирующая матрица энергий
	auto mtx_min_max = min_max(mtrx);
	for (int i = 0; i < mtrx.m; ++i) {
		std::vector <double> line_of_matrix = {};
		for (int j = 0; j < mtrx.m; ++j) {
			double d = mtrx.mtx[i][j] / ((mtx_min_max.first + mtx_min_max.second) / 2);
			if (mtrx.mtx[i][j] == 0)
				line_of_matrix.push_back(0);
			else {
				line_of_matrix.push_back(round((1 / pow(d, 12) - 1 / pow(d, 6)) * 100) / 100);
			}
		}
		energy_matrix.push_back(line_of_matrix);
	}

	return { mtrx.m, energy_matrix };
}

// функция для вычисления вероятнсти матрицы энергий
std::map <double, double> probability_energy(const Matrix& mtrx) {
	// итоговый словарь {значение : вероятность}
	std::map <double, double> prob;

	// словарь для подсчета элементов {значение : кол-во}
	std::map <double, double> tmp_mtrx;

	// создание словаря для подсчета элементов
	for (int i = 0; i < mtrx.m; ++i) {
		for (int j = i; j < mtrx.m; ++j) {
			if (!mtrx.mtx[i][j]) { 
				if (i == j) 
					++tmp_mtrx[0]; // на диагонали
				else {
					++tmp_mtrx[0]; // пары 0
					++tmp_mtrx[0];
				}
			}
			else {
				++tmp_mtrx[mtrx.mtx[i][j]]; // != 0
				++tmp_mtrx[mtrx.mtx[i][j]];
			}
		}
	}

	// создание итогового словаря вероятностей
	for (auto x : tmp_mtrx) prob[x.first] = x.second / (mtrx.m * mtrx.m);
	
	return prob;
}


int main()
{
	setlocale(LC_CTYPE, "rus");
    std::cout << "Практическая работа №2, команда 2.\n\n";
/*
	for (int i = 12; i < 303; i += 12) { //10+2
		ifstream fin("data- (" + to_string(i) + ").txt");
		ofstream fout("out" + to_string(i) + ".XML");

		if (fin.fail())
			cout << "File " + to_string(i) + " doesn't exist";

		string trash;
		getline(fin, trash);
		trash = "";

		list <vector<double>> dataset;
		while (!fin.eof()) {
			vector <double> data;
			for (int i = 0; i < 8; ++i) {
				double x = 0;
				fin >> x;
				if (i == 4 || i > 5)
					continue;
				else {
					data.push_back(x);
				}
				x = 0;
			}
			dataset.push_back(data);
		}
		dataset.pop_back();
		cout << "File " + to_string(i) + " read" << "\n";

		double Dmax = 0;
		cout << "Dmax=";
		cin >> Dmax;

		double Dmin = 0;
		cout << "Dmin=: ";
		cin >> Dmin;
/*




//task_3
	std::cout << "-----------------------------------task_3-----------------------------------------\n";
	// получение матрицы и преобразование по шаблону структуры
	/*
	Matrix array_var2 = {prom_array.size(), };
	for (int i = 0; i < prom_array.size(); ++i) {
		for (int j = 0; j < prom_array.size(); ++j) {
			array_var2.mtx[i].push_back(array_var2[i][j]);
		}
	}
	*/

	// вывод входной матрицы
	std::cout << "Входная матрица:\n";
	std::cout << m_1 << "\n";
	
	// создание матрицы энергий
	Matrix m_1_energy = {create_energy_matrix(m_1)};

	// вывод матрицы энергий
	std::cout << "Матрица энергий:\n";
	std::cout << m_1_energy << "\n";

	// создание вероятность матрицы энергий
	std::map <double, double> energy_probability = probability_energy(m_1_energy);
	// вывод вероятности матрицы энергий
	std::cout << "Вероятность матрицы энергий:\n";
	for (auto const x : energy_probability) std::cout << std::setw(6) << x.first << "	" << x.second << "\n";
	

	// создание матрицы энергий для следующего пункта
	int size = 8;
	double** energy_mtrx = new double* [size]; // исправить размер!!!!!!!!
	for (int i = 0; i < size; i++) {
		energy_mtrx[i] = new double[size];
	}

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			energy_mtrx[i][j] = m_1_energy.mtx[i][j];
		}
	}

	// на выходе матрица: energy_mtrx - двумерный дин. массив, вероятности: energy_probability - словарь
	std::cout << "--------------------------------end of task_3-------------------------------------\n";



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

 







	for (int i = 0; i < size; i++) delete[] energy_mtrx[i];
	delete[] energy_mtrx;
// Вывод в xml
/*
	int count = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j)
			if (a[i][j] == 1) 
			{
				++count;
				a[i][j] = -1;
			}
		a[i][i] = count;
		count = 0;
	}

	fout << "Матрица Киргофа" << "\n";
	for (int i = 0; i < size; ++i) 
	{
		for (int j = 0; j < size; ++j)
			fout << a[i][j] << " ";
		fout << "\n";
	}

	cout << "Конец матрицы Киргофа" << "\n";

	map <int, int> P;
	count = 0;
	for (int i = 0; i < size; ++i) 
	{
		for (int j = 0; j < size; ++j) 
		{
			if (a[j][i] == a[j][j])
				++count;
		}
		P[a[i][i]] = count;
	}

	fout << "Вероятность валентности узлов" << "\n";
	for (auto it_m = P.begin(); it_m != P.end(); ++it_m) 
	{
		double c = it_m->second;
		fout << it_m->first << " " << a / size << "\n";
	}
	fout << "\n";

	cout << "Конец вероятности валентности узлов" << "\n";

	fout << "Матрица энергий" << "\n";
	double** m_1_energy = new double* [size];
	for (int i = 0; i < size; ++i)
		m_1_energy[i] = new double[size];

	for (int i = 0; i < size; ++i) 
	{
		for (int j = 0; j < size; ++j) 
		{
			double d = energy_mtrx[i][j] / ((Dmax + Dmin) / 2);
			if (energy_mtrx[i][j])
				m_1_energy[i][j] = ((1 / pow(d, 12)) - ((1 / pow(d, 6))));
			else
				m_1_energy[i][j] = 0;
		}
	}

	//cout << size << "\n";
	for (int i = 0; i < size; ++i) 
	{
		for (int j = 0; j < size; ++j)
			fout << fixed << setprecision(2) << m_1_energy[i][j] << " ";
		fout << "\n";
	}

	cout << "Конец матрицы энергий" << "\n";

	fout << "Распределение вероятностей энергии" << "\n";
	map <double, double> m_en;
	count = 0;
	for (int i = 0; i < size; ++i) 
	{
		for (int j = 0; j < size; ++j) 
		{
			++m_en[m_1_energy[i][j]];
		}
	}

	for (auto it_m = m_en.begin(); it_m != m_en.end(); ++it_m) 
	{
		double c = it_m->second;
		fout << it_m->first << " " << a / size << "\n";
	}
	cout << "Конец распределения вероятностей энергии" << "\n";

	cout << "File " + to_string(i) << " completed" << "\n";
	cout << "\n";

	dataset.clear();
	m_en.clear();
	P.clear();
	for (int i = 0; i < size; ++i) 
	{
		delete[] energy_mtrx[i];
		delete[] a[i];
		delete[] m_1_energy[i];
	}
	delete[] energy_mtrx;
	delete[] a;
	delete[] m_1_energy;
	fin.close();
	fout.close();
	}
	*/
	cout << "End";
	return 0;
}
