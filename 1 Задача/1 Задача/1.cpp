#include<iostream>
#include<cmath>
#include<algorithm>
#include<set>
#include<string>
#include<fstream>
#include<stdio.h>
#include<dirent.h>
#include<clocale>
#include<iomanip>
#include<cmath>
#include<vector>
using namespace std;

//класс для чтения файлов
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
ostream& operator << (ostream& out, const Read& a)
{
	out << a.number() << "\t" << a.area() << "\t " << a.xm() << "\t" << a.ym() << "\t " << a.circ() << "\t " << a.ar() << "\t " << a.round() << "\t " << a.solid();
	return out;
}
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
//создем вектор имен файлов из указанной папки
vector<string> Filename()
{
	setlocale(LC_CTYPE, "rus");
	vector<string> name;
	DIR* dir = opendir("C:\Users\baish\Desktop\Новая папка\1 Задача\1 Задача");
	if (dir == NULL) {
		perror("opendir");
	}
	struct dirent* entry;

	while (entry = readdir(dir)) {
		name.push_back(entry->d_name);
	}
	closedir(dir);
	return name;
}
int main()
{
	cout << "Hello world!";
}
