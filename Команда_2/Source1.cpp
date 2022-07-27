#include<iostream>
#include<cmath>
#include<algorithm>
#include <set>
#include<string>
#include<fstream>
#include <stdio.h>
#include <dirent.h>
#include<clocale>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;

//����� ��� ������ ������
class Read {
private:
	double cir;
	double a;
	double roun;
	double soli;
	double are;
	double x;
	int numbe;
	double y;

public:
	Read(int num = 0, double ar = 0, double xm1 = 0, double ym1 = 0, double ci = 0, double ar1 = 0, double rou = 0, double sol = 0) :
		numbe{ num }, are{ ar }, x{ xm1 }, y{ ym1 }, cir{ ci }, a{ ar1 }, roun{ rou }, soli{ sol } {}
	int number() const { return numbe; }
	double area() const { return are; }
	double xm() const { return x; }
	double ym() const { return y; }
	double circ() const { return cir; }
	double ar() const { return a; }
	double round() const { return roun; }
	double solid() const { return soli; }
};
//���������� ������
ostream& operator << (ostream& out, const Read& a)
{
	out << a.number() << "\t" << a.area() << "\t " << a.xm() << "\t" << a.ym() << "\t " << a.circ() << "\t " << a.ar() << "\t " << a.round() << "\t " << a.solid();
	return out;
}
//���������� �����
istream& operator >> (istream& in, Read& a)
{
	double ar;
	double round;
	double solid;
	double area;
	double xm;
	int number;
	double ym;
	double circ;
	in >> number >> area >> xm >> ym >> circ >> ar >> round >> solid;
	a = { number, area, xm, ym, circ, ar, round,solid };
	return in;
}
//������ ������ ���� ������ �� ��������� �����
vector<string> Filename()
{
	setlocale(LC_CTYPE, "rus");
	vector<string> name;
	DIR* mydir = opendir("C:\Users\baish\source\repos\team_2\�������_2"); // ������ ����� �����, � ������� �������� �����(������ �����)
	//��� �� ��� ��� ����� ������ ���������� � ����� ����� � ������ .���(������ ����� ��� �����)
	if (mydir == NULL) {
		perror("opendir");
	}
	struct dirent* entry;

	while (entry = readdir(mydir)) {
		name.push_back(entry->d_name);
	}
	closedir(mydir);
	return name;
}
int main()
{
	//������� ����� ������ ��������� � ��� �� �����, ��� � ���� .��� + ������ ���� ������� ��� ���� ����� � ����� �������(������ � ����� �� ����� � ������� ����)
		//� ����� ������ � ����� �����������
	vector<string> name;
	name = Filename();
	name.erase(name.begin());
	name.erase(name.begin());
	double dmin;
	double dmax;
	cout << "Enter Dmax:";
	cin >> dmax;
	cout << "Enter Dmin:";
	cin >> dmin;
	for (int i = 0; i < name.size(); i++)
	{
		ifstream fin{ name[i] };
		if (!fin) { cout << "FILE ERROR"; return 0; }
		vector<Read> a;//������ ������ � ������� ����� ��������� ������ ����
		string line;
		getline(fin, line);//�������� ��������� ����
		for (Read x; fin >> x; ) a.push_back(x);
		int n = 5; //����������� �������� � �������
		double** array = new double* [a.size()]; //�������� ���������� �������, ����� ����� = ������� �������
		for (int i = 0; i < a.size(); i++) array[i] = new double[n];
		for (int i = 0; i < a.size(); i++)//�������� � ��������� ������ ����������� ������� �� �������
		{
			array[i][0] = a[i].number();
			array[i][1] = a[i].area();
			array[i][2] = a[i].xm();
			array[i][3] = a[i].ym();
			array[i][4] = a[i].ar();

		}
		//����� ����������� ������� �� �����
		/*
		for(int i=0; i<a.size(); i++)
		{
			for(int j=0; j<n; j++) cout  << array[i][j];
			cout << "\n";
		}
		*/

		//����� �
		double use = (((dmax + dmin) / 2) * ((dmax + dmin) / 2)) / 8;
		//�������� � ���������� �������������� ������� � ������� �� ������� 1.�
		vector<vector<double>> prom_array;
		vector<double> tmp;
		for (int i = 0; i < a.size(); i++)
		{
			if (array[i][1] < use)
				if (array[i][4] < 2)
				{
					for (int j = 0; j < n; j++)
						tmp.push_back(array[i][j]);
					prom_array.push_back(tmp);
					tmp.clear();
				}
		}
		//����� �������������� �������
		/*
		for(int i=0; i<prom_array.size(); i++)
		{
			for(int j=0; j<n; j++)
			{
				cout<<prom_array[i][j]<<"\t";
			}
			cout<<"\n";
		}
		//
		cout <<prom_array.size()<<"\n";
		*/

		//����� �
	//������� ������� ������
		double** array_var1_sample = new double* [prom_array.size()];
		for (int i = 0; i < prom_array.size(); i++) array_var1_sample[i] = new double[prom_array.size()];
		for (int i = 0; i < prom_array.size(); i++)
		{
			for (int j = 0; j < prom_array.size(); j++)
				array_var1_sample[i][j] = sqrt((prom_array[j][2] - prom_array[i][2]) * (prom_array[j][2] - prom_array[i][2]) + (prom_array[j][3] - prom_array[i][3]) * (prom_array[j][3] - prom_array[i][3]));
		}
		cout << "The matrix of distances for first 10 points:\n ";
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				cout << array_var1_sample[i][j] << "\t";
			}
			cout << "\n";
		}
		//������� ������� 1
		int count = 0;
		double** array_var1 = new double* [prom_array.size()];
		for (int i = 0; i < prom_array.size(); i++) array_var1[i] = new double[prom_array.size()];
		for (int i = 0; i < prom_array.size(); i++)
		{
			for (int j = 0; j < prom_array.size(); j++)
			{
				if ((dmin <= array_var1_sample[i][j]) && (array_var1_sample[i][j] <= dmax))
				{
					// cout <<array_var1_sample[i][j]<<"\t";
					array_var1[i][j] = 1;
				}
				else array_var1[i][j] = 0;
			}
		}
		cout << "The number of 1 in matrix 1:";
		for (int i = 0; i < prom_array.size(); i++)
		{
			for (int j = 0; j < prom_array.size(); j++)
			{
				if (array_var1[i][j] == 1)
					count++;
				//	cout<<array_var1[i][j]<<"\t";
			}
			//cout<<"\n";
		}
		cout << count << "\n";
		/*
		cout << "The matrix of points:\n";
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j <15; j++)
			{
				cout << array_var1[i][j] << "\t";
			}
			cout << "\n";
		}
	*/
	//������� ������� 2
		double** array_var2 = new double* [prom_array.size()];
		for (int i = 0; i < prom_array.size(); i++) array_var2[i] = new double[prom_array.size()];
		for (int i = 0; i < prom_array.size(); i++)
		{
			for (int j = 0; j < prom_array.size(); j++)
			{
				if ((array_var1_sample[i][j] >= dmin) && (array_var1_sample[i][j] <= dmax))
				{
					array_var2[i][j] = array_var1_sample[i][j];
					//  cout<<array_var1_sample[i][j]<<"\t";
				}
				else array_var2[i][j] = 0;
			}
		}
		int k = 0;
		cout << "The number of distances in matrix 2:";
		for (int i = 0; i < prom_array.size(); i++)
		{
			for (int j = 0; j < prom_array.size(); j++)
			{
				if (array_var2[i][j] != 0)
					k++;
				//cout<<array_var1[i][j]<<"\t";
			}
			//cout<<"\n";
		}
		cout << k << "\n";
		/*
		cout << "The matrix distances of  points:\n";
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				cout << array_var2[i][j] << "\t";
			}
			cout << "\n";
		}
		*/
	}
}