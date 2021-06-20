#pragma comment (lib, "Winmm.Lib")

#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

using namespace std;

double leftRectanglesMethod(double a, double b, double h)
{
	double area = h * (8 / (1 + a * a));
	while (a < b)
	{
		area = area + h * (8 / (1 + a * a));
		a = a + h;
	}

	return area;
}

double leftRectanglesMethodOpenMP(double a, double b, double h)
{
	double area = h * (8 / (1 + a * a));

	//omp_set_dynamic(0); // ��������� ���������� openmp ������ ����� ������� �� ����� ����������.
	//omp_set_num_threads(4); // ���������� ����� ������� � 4.
	#pragma omp parallel for shared (area, a, b)
	for (; a < b; a = a + h)
	{
		area = area + h * (8 / (1 + a * a));
	}

	return area;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	// ������� ��������������.
	double a = 0;
	double b = 1;

	// ���������� ����������.
	double n = 1000000;

	// �������� ��� ��������� (����� ������� �������������� �������):
	double h = (b - a) / n;

	cout << "����� ����� ��������������� ��� OpenMP:" << endl;

	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	cout << leftRectanglesMethod(a, b, h) << endl;
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

	chrono::duration <double> durationLeftRectangles = (t2 - t1);
	cout << "����� �������� ������� ����� ��������������� ��� OpenMP: " << durationLeftRectangles.count() << " ������." << endl << endl;





	cout << "����� ����� ��������������� � �������������� OpenMP:" << endl;
	t1 = chrono::high_resolution_clock::now();
	cout << leftRectanglesMethodOpenMP(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();

	chrono::duration <double> durationLeftRectanglesOpenMP = (t2 - t1);
	cout << "����� �������� ������� ����� ��������������� � �������������� OpenMP: " << durationLeftRectanglesOpenMP.count() << " ������." << endl << endl;

	return 0;
}