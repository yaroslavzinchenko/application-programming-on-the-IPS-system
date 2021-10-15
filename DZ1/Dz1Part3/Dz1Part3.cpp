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

	// √раницы интегрировани€.
	double a = 0;
	double b = 1;

	//  оличество интервалов.
	double n = 100;

	// ¬ычислим шаг разбиени€ (длину каждого промежуточного отрезка):
	double h = (b - a) / n;

	n = 100;
	h = (b - a) / n;

	cout << "ћетод левых пр€моугольников с параллелизацией на 4-х потоках с автоматическим параллелизатором:" << endl;
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	cout << leftRectanglesMethodQPar(a, b, h) << endl;
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationLeftRectanglesQPar = (t2 - t1);
	cout << "¬рем€ подсчЄта методом левых пр€моугольников с параллелизацией на 4-х потоках с автоматическим параллелизатором с шагом " << n << ": " << durationLeftRectanglesQPar.count() << " секунд." << endl << endl;


	t1 = chrono::high_resolution_clock::now();
	n = 1000;
	h = (b - a) / n;
	cout << leftRectanglesMethodQPar(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationLeftRectanglesQPar = (t2 - t1);
	cout << "¬рем€ подсчЄта методом левых пр€моугольников с параллелизацией на 4-х потоках с автоматическим параллелизатором с шагом " << n << ": " << durationLeftRectanglesQPar.count() << " секунд." << endl << endl;


	t1 = chrono::high_resolution_clock::now();
	n = 10000;
	h = (b - a) / n;
	cout << leftRectanglesMethodQPar(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationLeftRectanglesQPar = (t2 - t1);
	cout << "¬рем€ подсчЄта методом левых пр€моугольников с параллелизацией на 4-х потоках с автоматическим параллелизатором с шагом " << n << ": " << durationLeftRectanglesQPar.count() << " секунд." << endl << endl;


	t1 = chrono::high_resolution_clock::now();
	n = 100000;
	h = (b - a) / n;
	cout << leftRectanglesMethodQPar(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationLeftRectanglesQPar = (t2 - t1);
	cout << "¬рем€ подсчЄта методом левых пр€моугольников с параллелизацией на 4-х потоках с автоматическим параллелизатором с шагом " << n << ": " << durationLeftRectanglesQPar.count() << " секунд." << endl << endl;


	t1 = chrono::high_resolution_clock::now();
	n = 1000000;
	h = (b - a) / n;
	cout << leftRectanglesMethodQPar(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationLeftRectanglesQPar = (t2 - t1);
	cout << "¬рем€ подсчЄта методом левых пр€моугольников с параллелизацией на 4-х потоках с автоматическим параллелизатором с шагом " << n << ": " << durationLeftRectanglesQPar.count() << " секунд." << endl << endl;

	return 0;
}