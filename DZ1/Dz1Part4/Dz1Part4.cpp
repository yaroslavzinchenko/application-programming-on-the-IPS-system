#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void leftRectanglesMethodThreaded(double a, double b, double h, double& area)
{
	area = h * (8 / (1 + a * a));
	while (a < b)
	{
		area = area + h * (8 / (1 + a * a));
		a = a + h;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	// Границы интегрирования.
	double a = 0;
	double b = 1;

	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

	// Количество интервалов.
	double n = 100;

	// Вычислим шаг разбиения (длину каждого промежуточного отрезка):
	double h = (b - a) / n;


	cout << "Метод левых прямоугольников на 4-х потоках:" << endl;

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

	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationLeftRectanglesThreaded = (t2 - t1);
	cout << "Время подсчёта методом левых прямоугольников на 4-х потоках: " << durationLeftRectanglesThreaded.count() << " секунд." << endl << endl;



	return 0;
}