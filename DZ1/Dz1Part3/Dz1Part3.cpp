#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

double leftRectanglesMethodQPar(double a, double b, double h)
{
	double area = h * (8 / (1 + a * a));
#pragma loop(hint_parallel(4))
	while (a < b)
	{
		area = area + h * (8 / (1 + a * a));
		a = a + h;
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
	double n = 100;

	// �������� ��� ��������� (����� ������� �������������� �������):
	double h = (b - a) / n;

	n = 100;
	h = (b - a) / n;

	cout << "����� ����� ��������������� � ��������������� �� 4-� ������� � �������������� ����������������:" << endl;
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	cout << leftRectanglesMethodQPar(a, b, h) << endl;
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationLeftRectanglesQPar = (t2 - t1);
	cout << "����� �������� ������� ����� ��������������� � ��������������� �� 4-� ������� � �������������� ���������������� � ����� " << n << ": " << durationLeftRectanglesQPar.count() << " ������." << endl << endl;


	t1 = chrono::high_resolution_clock::now();
	n = 1000;
	h = (b - a) / n;
	cout << leftRectanglesMethodQPar(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationLeftRectanglesQPar = (t2 - t1);
	cout << "����� �������� ������� ����� ��������������� � ��������������� �� 4-� ������� � �������������� ���������������� � ����� " << n << ": " << durationLeftRectanglesQPar.count() << " ������." << endl << endl;


	t1 = chrono::high_resolution_clock::now();
	n = 10000;
	h = (b - a) / n;
	cout << leftRectanglesMethodQPar(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationLeftRectanglesQPar = (t2 - t1);
	cout << "����� �������� ������� ����� ��������������� � ��������������� �� 4-� ������� � �������������� ���������������� � ����� " << n << ": " << durationLeftRectanglesQPar.count() << " ������." << endl << endl;


	t1 = chrono::high_resolution_clock::now();
	n = 100000;
	h = (b - a) / n;
	cout << leftRectanglesMethodQPar(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationLeftRectanglesQPar = (t2 - t1);
	cout << "����� �������� ������� ����� ��������������� � ��������������� �� 4-� ������� � �������������� ���������������� � ����� " << n << ": " << durationLeftRectanglesQPar.count() << " ������." << endl << endl;


	t1 = chrono::high_resolution_clock::now();
	n = 1000000;
	h = (b - a) / n;
	cout << leftRectanglesMethodQPar(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationLeftRectanglesQPar = (t2 - t1);
	cout << "����� �������� ������� ����� ��������������� � ��������������� �� 4-� ������� � �������������� ���������������� � ����� " << n << ": " << durationLeftRectanglesQPar.count() << " ������." << endl << endl;

	return 0;
}