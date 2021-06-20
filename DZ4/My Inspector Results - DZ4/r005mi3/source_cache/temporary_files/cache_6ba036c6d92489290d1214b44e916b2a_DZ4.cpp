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

	//omp_set_dynamic(0); // Запретить библиотеке openmp менять число потоков во время исполнения.
	//omp_set_num_threads(4); // Установить число потоков в 4.
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

	// Границы интегрирования.
	double a = 0;
	double b = 1;

	// Количество интервалов.
	double n = 1000000;

	// Вычислим шаг разбиения (длину каждого промежуточного отрезка):
	double h = (b - a) / n;

	cout << "Метод левых прямоугольников без OpenMP:" << endl;

	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	cout << leftRectanglesMethod(a, b, h) << endl;
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

	chrono::duration <double> durationLeftRectangles = (t2 - t1);
	cout << "Время подсчёта методом левых прямоугольников без OpenMP: " << durationLeftRectangles.count() << " секунд." << endl << endl;





	cout << "Метод левых прямоугольников с использованием OpenMP:" << endl;
	t1 = chrono::high_resolution_clock::now();
	cout << leftRectanglesMethodOpenMP(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();

	chrono::duration <double> durationLeftRectanglesOpenMP = (t2 - t1);
	cout << "Время подсчёта методом левых прямоугольников с использованием OpenMP: " << durationLeftRectanglesOpenMP.count() << " секунд." << endl << endl;

	return 0;
}