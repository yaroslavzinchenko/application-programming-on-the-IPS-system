#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

double analyticalSolution(double a, double b)
{
	double area = 8 * atan(b) - 8 * atan(a);
	return area;
}

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

// � ������� �� ������ ����� ���������������, ��� ������ ������, � �� ����� �������.
double rightRectanglesMethod(double a, double b, double h)
{
	double area = h * (8 / (1 + b * b));
	while (b > a)
	{
		area = area + h * (8 / (1 + b * b));
		b = b - h;
	}

	return area;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	// ������� ��������������.
	double a = 0;
	double b = 1;

	cout << "��������� ���������������� ���������: " << endl;
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

	// ���������� ����������.
	double n = 100;

	// �������� ��� ��������� (����� ������� �������������� �������):
	double h = (b - a) / n;

	cout << "����� ����� ���������������:" << endl;
	cout << leftRectanglesMethod(a, b, h) << endl;
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationLeftRectangles = (t2 - t1);
	cout << "����� �������� ������� ����� ��������������� � ����� " << n << ": " << durationLeftRectangles.count() << " ������." << endl << endl;

	n = 1000;
	h = (b - a) / n;
	cout << leftRectanglesMethod(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationLeftRectangles = (t2 - t1);
	cout << "����� �������� ������� ����� ��������������� � ����� " << n << ": "  << durationLeftRectangles.count() << " ������." << endl << endl;

	n = 10000;
	h = (b - a) / n;
	cout << leftRectanglesMethod(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationLeftRectangles = (t2 - t1);
	cout << "����� �������� ������� ����� ��������������� � ����� " << n << ": " << durationLeftRectangles.count() << " ������." << endl << endl;

	n = 100000;
	h = (b - a) / n;
	cout << leftRectanglesMethod(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationLeftRectangles = (t2 - t1);
	cout << "����� �������� ������� ����� ��������������� � ����� " << n << ": " << durationLeftRectangles.count() << " ������." << endl << endl;

	n = 1000000;
	h = (b - a) / n;
	cout << leftRectanglesMethod(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationLeftRectangles = (t2 - t1);
	cout << "����� �������� ������� ����� ��������������� � ����� " << n << ": " << durationLeftRectangles.count() << " ������." << endl << endl;

	t1 = chrono::high_resolution_clock::now();

	cout << "����� ������ ���������������:" << endl;
	n = 100;
	h = (b - a) / n;
	cout << rightRectanglesMethod(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationRightRectangles = (t2 - t1);
	cout << "����� �������� ������� ������ ��������������� � �����: " << n << ": " << durationRightRectangles.count() << " ������." << endl << endl;


	n = 1000;
	h = (b - a) / n;
	cout << rightRectanglesMethod(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationRightRectangles = (t2 - t1);
	cout << "����� �������� ������� ������ ��������������� � �����: " << n << ": " << durationRightRectangles.count() << " ������." << endl << endl;


	n = 10000;
	h = (b - a) / n;
	cout << rightRectanglesMethod(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationRightRectangles = (t2 - t1);
	cout << "����� �������� ������� ������ ��������������� � �����: " << n << ": " << durationRightRectangles.count() << " ������." << endl << endl;

	n = 100000;
	h = (b - a) / n;
	cout << rightRectanglesMethod(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationRightRectangles = (t2 - t1);
	cout << "����� �������� ������� ������ ��������������� � �����: " << n << ": " << durationRightRectangles.count() << " ������." << endl << endl;

	n = 1000000;
	h = (b - a) / n;
	cout << rightRectanglesMethod(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationRightRectangles = (t2 - t1);
	cout << "����� �������� ������� ������ ��������������� � �����: " << n << ": " << durationRightRectangles.count() << " ������." << endl << endl;

	cout << "������������� �������: " << endl;

	t1 = chrono::high_resolution_clock::now();
	cout << analyticalSolution(a, b) << endl;
	t2 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationAnalyticalSolution = (t2 - t1);
	cout << "����� �������� ������������� �������: " << durationAnalyticalSolution.count() << " ������." << endl << endl;

	return 0;
}