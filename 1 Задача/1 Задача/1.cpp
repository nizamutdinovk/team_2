#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <windows.h>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

struct Point {
    int number;
    int area;
    double XM;
    double YM;
    double circ;
    double AR;
    double round;
    double solidity;
};
//Перегрузка ввода
istream& operator>>(istream& in, Point& p) {
    in >> p.number >> p.area >> p.XM >> p.YM >> p.circ >> p.AR >> p.round >> p.solidity;
    return in;
}
//Перегрузка вывода
ostream& operator<<(ostream& out, const Point& p) {
    out << fixed << setprecision(3)
        << p.number
        << " " << p.area
        << " " << p.XM
        << " " << p.YM
        << " " << p.circ
        << " " << p.AR
        << " " << p.round
        << " " << p.solidity;
    return out;
}
//Отбор Б1
vector<Point> SelectionByArea(const vector<Point>& points, const double& Dmin, const double& Dmax) {
    vector<Point> result_points;
    for (const Point& p : points) {
        if (p.area < ((pow(Dmax - Dmin, 2)) / 2)) {
            result_points.push_back(p);
        }
    }
    return result_points;
}
//Отбор Б2
vector<Point> SelectionByAR(const vector<Point>& points) {
    vector<Point> result_points;
    for (const Point& p : points) {
        if (p.AR < 2) {
            result_points.push_back(p);
        }
    }
    return result_points;
}
//
double CalcDist(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.XM - p2.XM, 2) + pow(p1.YM - p2.YM, 2));
}
//Функция создания матрицы связей
vector<vector<int>> CreateLinkMatrix(const vector<Point>& points, const double& Dmin, const double& Dmax) {
    vector<vector<int>> link_matrix(points.size(), vector<int>(points.size()));
    for (int i = 0; i < points.size(); ++i) {
        for (int j = i + 1; j < points.size(); ++j) {
            if ((Dmin < CalcDist(points[i], points[j])) && (CalcDist(points[i], points[j]) < Dmax)) {
                link_matrix[i][j] = 1;
                link_matrix[j][i] = 1;
            }
            else {
                link_matrix[i][j] = 0;
                link_matrix[j][i] = 0;
            };
        }
        link_matrix[i][i] = 1;
    }
    return link_matrix;
}
//Функция создания матрицы расстояний
vector<vector<int>> CreateDistanceMatrix(const vector<Point>& points, const double& Dmin, const double& Dmax) {
    vector<vector<int>> distance_matrix(points.size(), vector<int>(points.size()));
    for (int i = 0; i < points.size(); ++i) {
        for (int j = i + 1; j < points.size(); ++j) {
            distance_matrix[i][j] = CalcDist(points[i], points[j]);
            distance_matrix[j][i] = CalcDist(points[i], points[j]);
        }
        distance_matrix[i][i] = 0;
    }
    return distance_matrix;
}
//Вывод матрицы
void PrintMatrix(const vector<vector<int>>& matrix) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << setw(2);
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    bool FlagFile = true;
    double DMIN;
    cout << "Dmin: = ";
    cin >> DMIN;
    double DMAX;
    cout << "Dmax: = ";
    cin >> DMAX;
    int i = 12;
    int ip = 12;
    //Пункт А
    while(FlagFile) {
        vector<Point> points;
        ifstream fin("data- ("+ to_string(i) +").txt");
        if (fin.is_open()) {
            string line;
            getline(fin, line);
            while (getline(fin, line)) {
                Point p;
                istringstream iss(line);
                iss >> p;
                points.push_back(p);
            }
            // Пункт Б
            points = SelectionByArea(points, DMIN, DMAX);
            points = SelectionByAR(points);
            // Пункт С
            vector<vector<int>> link_matrix = CreateLinkMatrix(points, DMIN, DMAX);
            vector<vector<int>> distance_matrix = CreateDistanceMatrix(points, DMIN, DMAX);
            // Пункт Д
            PrintMatrix(link_matrix);
            cout << endl;
            PrintMatrix(distance_matrix);
            cout << endl;
            i += ip;
        }
        else {
            cout << "Файлы не открыты!" << endl;
            FlagFile = false;
        }
    }
    return 0;
}
