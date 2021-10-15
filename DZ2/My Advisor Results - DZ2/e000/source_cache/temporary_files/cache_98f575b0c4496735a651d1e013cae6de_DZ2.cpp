#include <iostream>
#include <chrono>
#include <thread>
#include "advisor-annotate.h"

using namespace std;

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

void leftRectanglesMethodThreaded(double a, double b, double h, double& area)
{
	ANNOTATE_SITE_BEGIN(allWhileLoop2);
	area = h * (8 / (1 + a * a));
	while (a < b)
	{
		ANNOTATE_TASK_BEGIN(eachIteration2);
		area = area + h * (8 / (1 + a * a));
		a = a + h;
		ANNOTATE_TASK_END(eachIteration2);
	}
	ANNOTATE_SITE_END(allWhileLoop2);
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



	cout << "Метод левых прямоугольников на 4-х потоках:" << endl;

	double area1 = 0;
	double area2 = 0;
	double area3 = 0;
	double area4 = 0;
	n = 1000000;
	h = (b - a) / n;
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	std::thread thr51(leftRectanglesMethodThreaded, 0, 0.25, h, std::ref(area1));
	std::thread thr52(leftRectanglesMethodThreaded, 0.25, 0.5, h, std::ref(area2));
	std::thread thr53(leftRectanglesMethodThreaded, 0.5, 0.75, h, std::ref(area3));
	std::thread thr54(leftRectanglesMethodThreaded, 0.75, 1, h, std::ref(area4));
	thr51.join();
	thr52.join();
	thr53.join();
	thr54.join();
	double area = area1 + area2 + area3 + area4;
	cout << "Результат: " << area << endl;

	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationThreaded = (t2 - t1);
	cout << "Время подсчёта методом левых прямоугольников на 4-х потоках: " << durationThreaded.count() << " секунд." << endl << endl;



	cout << "Метод левых прямоугольников без распараллеливания:" << endl;
	chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();
	cout << "Результат: " << leftRectanglesMethod(a, b, h) << endl;
	chrono::high_resolution_clock::time_point t4 = chrono::high_resolution_clock::now();
	chrono::duration <double> duration = (t4 - t3);
	cout << "Время подсчёта методом правых прямоугольников с шагом: " << n << ": " << duration.count() << " секунд." << endl << endl;







	


	return 0;
}