#include "stdafx.h"
#include <iostream>
#include <cstdio>

using namespace std;

/*
	Алгоритм:
	1 часть: спрашиваем у пользователя значения a, b и h
	a, b - границы интервала
	h - шаг изменения аргумента

	Открываем файл на запись
	Проходимся в цикле от a до b, считаем значение функции и записываем значения x и fucntion(x) в файл
	Закрываем файл

	2 часть:
	Открываем файл на чтение, проверяем, что он открылся
	Создаём два массива (x, y), изначально в нём всего 1 элемент
	Считываем из файла до тех пор, пока есть что читать в массивы x и y по индексу index, каждый раз его увеличивая на 1
	Если в какой-то момент текущий индекс стал равен размеру массива, это значит, что больше в массиве нет элементов, писать некуда
	Поэтому создаём копии массива, которые в два раза длиннее, обновляем значение размера массива (size) и продолжаем

	Выводим полученные данные
	Создаём массив (mas) из максимально возможного числа нулей (числа элементов в массива x и y)
	Проходимся по всем значениям функции (массиву y)
	Если где-то значение блищко к нулю (по модулю меньше эпсилон), то запоминаем значение аргумента (массив x)
	
	Выводим значени массива mas	
*/

const double eps = 0.01; // точность для поиска нуля

// анализируемая функция
double function(double x) {
	return cos(x * x) + sin(x);
}

int main() {
	double a, b, h;
	
	// считываем значения интервала и шага
	cout << "Enter a: ";
	cin >> a;
	cout << "Enter b: ";
	cin >> b;
	cout << "Enter h: ";
	cin >> h;

	FILE *f = fopen("results.txt", "w"); // открываем файл на запись

	for (double x = a; x <= b; x += h) // проходимся по всем точкам и записываем аргумент и значеине функции в файл
		fprintf(f, "%lf, %lf\n", x, function(x));

	fclose(f); // закрываем файл

	f = fopen("results.txt", "r"); // открываем файл на чтение

	if (!f) 
		cout << "error during opening file..." << endl;
	else {
		// создаём динамические массивы для результатов из файла
		double *x = new double[1];
		double *y = new double[1];
		int size = 1;
		int index = 0;

		// считываем из файла, пока есть что читать
		while (!feof(f)) {
			fscanf(f, "%lf, %lf", &x[index], &y[index]);

			cout << "f(" << x[index] << ") = " << y[index] << endl; // выводим считанные данные
			index++;

			if (index >= size) {
				// создаём временные новые массивы в два раза большей длины
				double *x0 = new double[size * 2];
				double *y0 = new double[size * 2];

				// копируем в новые массивы значения из массивов
				for (int i = 0; i < index; i++) {
					x0[i] = x[i];
					y0[i] = y[i];
				}

				// освобождаем динамическую память из-под массивов
				delete[] x;
				delete[] y;

				// переприсваиваем массивы
				x = x0;
				y = y0;
				size *= 2; // увеличиваем доступный размер массива в 2 раза
			}
		}

		int length = 0;
		double *mas = new double[index]; // заводим массив для нулей функции

		for (int i = 0; i < index; i++)
			if (fabs(y[i]) < eps)
				mas[length++] = x[i]; // если значение функции меньше эпсилон, то это ноль функции, запоминаем его

		if (length > 0) {
			cout << "Zeros of function: ";

			for (int i = 0; i < length; i++)
				cout << mas[i] << " ";

			cout << endl;
		}
		else
			cout << "no zeroes..." << endl;
	}

	system("pause");
    return 0;
}

