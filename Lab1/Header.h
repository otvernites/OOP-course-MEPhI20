#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <limits>

namespace Lab1 {

	// структура для задания прямоугольной разреженной матрицы	
	struct matrix { 
		int m, n; // кол-во строк,столбцов
		struct list* line; // указатель на структуру списка
	};

	typedef struct list {
		int j;
		double val;
		struct list* next;
	}list;

	// шаблон функций ввода числа
	template <class T>
	int getNum(T& a) {	
		std::cin >> a;
		while (!std::cin.good()) {
			std::cin.clear();
			std::cout << "Invalid input, try again: \n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
			std::cin >> a;
		}
		return 1;
	}

	inline int isgreater(double a, double b) { //  вызов сортировки по возрастанию
		return a > b;
	}

	inline int isless(double a, double b) { // вызов сортировки по убыванию
		return a < b;
	}

	//прототипы функций
	void input(struct matrix& arr); // ввод матрицы
	struct matrix edit(struct matrix arr); // упорядочивание строк матрицы
	void output(struct matrix arr); // вывод матрицы
	void free_m(struct matrix arr); // освобождение занятой памяти 
}