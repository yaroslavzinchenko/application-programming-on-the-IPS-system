#include <iostream>
#include <chrono>
#include <thread>
#include "advisor-annotate.h"

using namespace std;

double analyticalSolution(double a, double b)
{
	double area = 8 * atan(b) - 8 * atan(a);
	return area;
}

double leftRectanglesMethod(double a, double b, double h)
{
	double area = h * (8 / (1 + a * a));
	ANNOTATE_SITE_BEGIN(allWhileLoop);
	while (a < b)
	{
		ANNOTATE_TASK_BEGIN(eachIteration);
		area = area + h * (8 / (1 + a * a));
		a = a + h;
		ANNOTATE_TASK_END(eachIteration);
	}
	ANNOTATE_SITE_END(allWhileLoop);

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

double leftRectanglesMethodThreaded(double a, double b, double h)
{
	double area = h * (8 / (1 + a * a));
	while (a < b)
	{
		area = area + h * (8 / (1 + a * a));
		a = a + h;
	}

	return area;
}

// В отличие от метода левых прямоугольников, идём справа налево, а не слева направо.
double rightRectanglesMethod(double a, double b, double h)
{
	double area = h * (8 / (1 + b * b));
	ANNOTATE_SITE_BEGIN(allWhileLoopRightRectanglesMethod);
	while (b > a)
	{
		ANNOTATE_TASK_BEGIN(eachIterationRightRectanglesMethod);
		area = area + h * (8 / (1 + b * b));
		b = b - h;
		ANNOTATE_TASK_END(eachIterationRightRectanglesMethod);
	}
	ANNOTATE_SITE_END(allWhileLoopRightRectanglesMethod);

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

	// Границы интегрирования.
	double a = 0;
	double b = 1;

	cout << "Запускаем последовательную программу: " << endl;
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

	// Количество интервалов.
	double n = 100;

	// Вычислим шаг разбиения (длину каждого промежуточного отрезка):
	double h = (b - a) / n;

	cout << "Метод левых прямоугольников:" << endl;
	cout << leftRectanglesMethod(a, b, h) << endl;

	n = 1000;
	h = (b - a) / n;
	cout << leftRectanglesMethod(a, b, h) << endl;

	n = 10000;
	h = (b - a) / n;
	cout << leftRectanglesMethod(a, b, h) << endl;

	n = 100000;
	h = (b - a) / n;
	cout << leftRectanglesMethod(a, b, h) << endl;

	n = 1000000;
	h = (b - a) / n;
	cout << leftRectanglesMethod(a, b, h) << endl;

	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationLeftRectangles = (t2 - t1);
	cout << "Время подсчёта методом левых прямоугольников: " << durationLeftRectangles.count() << " секунд." << endl << endl;


	chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();

	cout << "Метод правых прямоугольников:" << endl;
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
	cout << "Время подсчёта методом левых прямоугольников: " << durationRightRectangles.count() << " секунд." << endl << endl;


	cout << "Аналитическое решение: " << endl;

	chrono::high_resolution_clock::time_point t5 = chrono::high_resolution_clock::now();
	cout << analyticalSolution(a, b) << endl;
	chrono::high_resolution_clock::time_point t6 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationAnalyticalSolution = (t6 - t5);
	cout << "Время подсчёта аналитическим методом: " << durationAnalyticalSolution.count() << " секунд." << endl << endl;





	cout << "С отключённой векторизацией: " << endl;
	t1 = chrono::high_resolution_clock::now();

	n = 100;
	h = (b - a) / n;

	cout << "Метод левых прямоугольников:" << endl;
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
	cout << "Время подсчёта методом левых прямоугольников: " << durationLeftRectanglesNoVector.count() << " секунд." << endl << endl;


	t1 = chrono::high_resolution_clock::now();

	cout << "Метод правых прямоугольников:" << endl;
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
	cout << "Время подсчёта методом левых прямоугольников: " << durationRightRectanglesNoVector.count() << " секунд." << endl << endl;







	cout << "С параллелизацией на 4-х потоках: " << endl;
	t1 = chrono::high_resolution_clock::now();

	n = 100;
	h = (b - a) / n;

	cout << "Метод левых прямоугольников:" << endl;
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
	cout << "Время подсчёта методом левых прямоугольников с параллелизацией: " << durationLeftRectanglesQPar.count() << " секунд." << endl << endl;









	cout << "Считаем на одном потоке: " << endl;
	t1 = chrono::high_resolution_clock::now();

	n = 100;
	h = (b - a) / n;

	cout << "Метод левых прямоугольников на одном потоке:" << endl;
	std::thread thr(leftRectanglesMethodThreaded, a, b, h);
	thr.join();

	n = 1000;
	h = (b - a) / n;
	std::thread thr2(leftRectanglesMethodThreaded, a, b, h);
	thr2.join();

	n = 10000;
	h = (b - a) / n;
	std::thread thr3(leftRectanglesMethodThreaded, a, b, h);
	thr3.join();

	n = 100000;
	h = (b - a) / n;
	std::thread thr4(leftRectanglesMethodThreaded, a, b, h);
	thr4.join();

	n = 1000000;
	h = (b - a) / n;
	std::thread thr5(leftRectanglesMethodThreaded, a, b, h);
	thr5.join();

	t2 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationLeftRectanglesThreaded = (t2 - t1);
	cout << "Время подсчёта методом левых прямоугольников на одном потоке: " << durationLeftRectanglesThreaded.count() << " секунд." << endl << endl;



	return 0;
}