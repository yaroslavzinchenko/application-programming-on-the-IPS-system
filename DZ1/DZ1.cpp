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

double leftRectanglesMethodNoVector(double a, double b, double h)
{
	double area = h * (8 / (1 + a * a));
	#pragma loop(no_vector)
	while (a < b)
	{
		area = area + h * (8 / (1 + a * a));
		a = a + h;
	}

	return area;
}

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

void leftRectanglesMethodThreaded(double a, double b, double h, double &area)
{
	area = h * (8 / (1 + a * a));
	while (a < b)
	{
		area = area + h * (8 / (1 + a * a));
		a = a + h;
	}
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

double rightRectanglesMethodNoVector(double a, double b, double h)
{
	double area = h * (8 / (1 + b * b));
	#pragma loop(no_vector)
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

	n = 1000;
	h = (b - a) / n;
	cout << leftRectanglesMethod(a, b, h) << endl;

	n = 10000;
	h = (b - a) / n;
	cout << leftRectanglesMethod(a, b, h) << endl;

	n = 1000000;
	h = (b - a) / n;
	cout << leftRectanglesMethod(a, b, h) << endl;

	n = 1000000;
	h = (b - a) / n;
	cout << leftRectanglesMethod(a, b, h) << endl;

	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationLeftRectangles = (t2 - t1);
	cout << "����� �������� ������� ����� ���������������: " << durationLeftRectangles.count() << " ������." << endl << endl;


	chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();

	cout << "����� ������ ���������������:" << endl;
	n = 100;
	h = (b - a) / n;
	cout << rightRectanglesMethod(a, b, h) << endl;

	n = 1000;
	h = (b - a) / n;
	cout << rightRectanglesMethod(a, b, h) << endl;

	n = 10000;
	h = (b - a) / n;
	cout << rightRectanglesMethod(a, b, h) << endl;

	n = 100000;
	h = (b - a) / n;
	cout << rightRectanglesMethod(a, b, h) << endl;

	n = 1000000;
	h = (b - a) / n;
	cout << rightRectanglesMethod(a, b, h) << endl;

	chrono::high_resolution_clock::time_point t4 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationRightRectangles = (t4 - t3);
	cout << "����� �������� ������� ������ ���������������: " << durationRightRectangles.count() << " ������." << endl << endl;


	cout << "������������� �������: " << endl;

	chrono::high_resolution_clock::time_point t5 = chrono::high_resolution_clock::now();
	cout << analyticalSolution(a, b) << endl;
	chrono::high_resolution_clock::time_point t6 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationAnalyticalSolution = (t6 - t5);
	cout << "����� �������� ������������� �������: " << durationAnalyticalSolution.count() << " ������." << endl << endl;

	



	cout << "� ����������� �������������: " << endl;
	t1 = chrono::high_resolution_clock::now();

	n = 100;
	h = (b - a) / n;

	cout << "����� ����� ���������������:" << endl;
	cout << leftRectanglesMethodNoVector(a, b, h) << endl;

	n = 1000;
	h = (b - a) / n;
	cout << leftRectanglesMethodNoVector(a, b, h) << endl;

	n = 10000;
	h = (b - a) / n;
	cout << leftRectanglesMethodNoVector(a, b, h) << endl;

	n = 100000;
	h = (b - a) / n;
	cout << leftRectanglesMethodNoVector(a, b, h) << endl;

	n = 1000000;
	h = (b - a) / n;
	cout << leftRectanglesMethodNoVector(a, b, h) << endl;

	t2 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationLeftRectanglesNoVector = (t2 - t1);
	cout << "����� �������� ������� ����� ��������������� � ����������� �������������: " << durationLeftRectanglesNoVector.count() << " ������." << endl << endl;


	t1 = chrono::high_resolution_clock::now();

	cout << "����� ������ ��������������� � ����������� �������������:" << endl;
	n = 100;
	h = (b - a) / n;
	cout << rightRectanglesMethodNoVector(a, b, h) << endl;

	n = 1000;
	h = (b - a) / n;
	cout << rightRectanglesMethodNoVector(a, b, h) << endl;

	n = 10000;
	h = (b - a) / n;
	cout << rightRectanglesMethodNoVector(a, b, h) << endl;

	n = 100000;
	h = (b - a) / n;
	cout << rightRectanglesMethodNoVector(a, b, h) << endl;

	n = 1000000;
	h = (b - a) / n;
	cout << rightRectanglesMethodNoVector(a, b, h) << endl;

	t2 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationRightRectanglesNoVector = (t2 - t1);
	cout << "����� �������� ������� ������ ��������������� � ����������� �������������: " << durationRightRectanglesNoVector.count() << " ������." << endl << endl;





	

	cout << "� ��������������� �� 2-� �������: " << endl;
	t1 = chrono::high_resolution_clock::now();

	n = 100;
	h = (b - a) / n;

	cout << "����� ����� ��������������� � ��������������� �� 2-� �������:" << endl;
	cout << leftRectanglesMethodQPar(a, b, h) << endl;

	n = 1000;
	h = (b - a) / n;
	cout << leftRectanglesMethodQPar(a, b, h) << endl;

	n = 10000;
	h = (b - a) / n;
	cout << leftRectanglesMethodQPar(a, b, h) << endl;

	n = 100000;
	h = (b - a) / n;
	cout << leftRectanglesMethodQPar(a, b, h) << endl;

	n = 1000000;
	h = (b - a) / n;
	cout << leftRectanglesMethodQPar(a, b, h) << endl;

	t2 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationLeftRectanglesQPar = (t2 - t1);
	cout << "����� �������� ������� ����� ��������������� � ��������������� �� 2-� �������: " << durationLeftRectanglesQPar.count() << " ������." << endl << endl;


	


	




	cout << "����� ����� ��������������� �� 4-� �������:" << endl;

	double area1 = 0;
	double area2 = 0;
	double area3 = 0;
	double area4 = 0;
	n = 1000000;
	h = (b - a) / n;
	t1 = chrono::high_resolution_clock::now();
	std::thread thr51(leftRectanglesMethodThreaded, 0, 0.25, h, std::ref(area1));
	std::thread thr52(leftRectanglesMethodThreaded, 0.25, 0.5, h, std::ref(area2));
	std::thread thr53(leftRectanglesMethodThreaded, 0.5, 0.75, h, std::ref(area3));
	std::thread thr54(leftRectanglesMethodThreaded, 0.75, 1, h, std::ref(area4));
	thr51.join();
	thr52.join();
	thr53.join();
	thr54.join();
	double area = area1 + area2 + area3 + area4;
	cout << area << endl;

	t2 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationLeftRectanglesThreaded = (t2 - t1);
	cout << "����� �������� ������� ����� ��������������� �� 4-� �������: " << durationLeftRectanglesThreaded.count() << " ������." << endl << endl;



	return 0;
}