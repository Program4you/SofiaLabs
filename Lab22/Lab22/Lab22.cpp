#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

/*
	алгоритм:
	Открываем файл на чтение, если не смогли, то сообщаем об этом
	Считываем из файла предложения в массив строк
	Проходимся по массиву, ища максимальную длину строки и запоминая её индекс
	Выводим предложение по найденному индексу

	Считывание из файла предложений:
		заводим массив строк
		считываем предложение
		если нужно, расширяем память
		читаем пока файл не кончится

	Считывание предложения:
		заводим массив символов
		пропускаем символы, пока не началось предложение
		запоминаем символы
		если нужно, расширяем массив
		сохраняем и возвращаем результат
*/

// чтение предложения из файла f
char *readWord(FILE *f) {
	int word_size = 0; // текущий индекс (и число символов в предложении)
	int word_capacity = 1; // максимальный рамзер массива

	char *word = new char[word_capacity]; // заводится массив из 1 символа
	char c;

	// пока символ, не относящийся к предложению и не конец файла читаем дальше
	do {
		c = fgetc(f);
	} while (!feof(f) && (c == '\n' || c == '.' || c == '!' || c == '?' || c == ' '));

	// пока не конец файла и символ предложения
	while (!feof(f) && c != '.' && c != '!' && c != '?') {
		word[word_size++] = c; // запоминаем символ в массив

		// если нужно расширить (см. задание 1 лабы 2), то расширяем
		if (word_size >= word_capacity) {
			char *tmpWord = new char[word_capacity * 2];

			for (int i = 0; i < word_size; i++)
				tmpWord[i] = word[i];

			delete[] word;

			word_capacity *= 2;
			word = tmpWord;
		}

		do {
			c = fgetc(f);
		} while (c == '\n'); // переносы строки убираем, как ненужные :)
	}

	word[word_size] = '\0'; // ставим символ конца строки

	return word; // возвращаем предложение
}

int main() {
	FILE *f = fopen("text.txt", "r");

	if (!f)
		cout << "Error during opening file" << endl;
	else {
		int length = 0;
		int capacity = 1;
		char **words = new char *[capacity]; // заводим массив строк для предложений

		// пока не коне файла читаем предложения
		while (!feof(f)) {
			words[length++] = readWord(f);

			// если нужно, то расширяемся
			if (length >= capacity) {
				char **tmp_words = new char*[capacity * 2];
				for (int i = 0; i < length; i++)
					tmp_words[i] = words[i];

				delete[] words;

				capacity *= 2;
				words = tmp_words;
			}

		}

		fclose(f); // закрываем файл

		int max = 0;
		int max_i = 0;

		// ищем максимальную длину строки
		for (int i = 0; i < length; i++) {
			cout << words[i] << endl;

			int len = strlen(words[i]);

			if (len > max) {
				max = len;
				max_i = i;
			}
		}

		// выводим предложение с максимальной длиной
		cout << endl << "The longest is: " << words[max_i] << endl;
	}

	system("pause");
    return 0;
}

