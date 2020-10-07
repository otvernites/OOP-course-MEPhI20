#include "Header.h"

namespace Lab1 {

	// ввод матрицы
	void input(struct matrix& arr) {
		int m = 0, n = 0;
		std::cout << "How many lines will there be in the matrix? \n";
		getNum(m);
		while (m < 0) {
			std::cout << "\tInvalid index. Please try again: \n";
			getNum(m);
		}
		std::cout << "What about the columns? \n";
		getNum(n);
		while (n < 0) {
			std::cout << "\tInvalid index. Please try again: \n";
			getNum(n);
		}

		try {
			arr.line = new list[m]; // выделение памяти под массив строк матрицы
		}
		catch (std::bad_alloc& ba)
		{
			std::cout << "\tException caught: " << ba.what() << std::endl;
			return;
		}

		for (int i = 0; i < m; i++)
		{
			arr.line[i].next = nullptr; // инициализация массива указателей nullptr
			arr.line[i].j = -1; //для корректного вывода "0"
		}

		arr.m = m; // сохранение количества строк
		arr.n = n; //столбцов
		int i, j;
		int flag = 0; // метка для проверки существования элемента
		std::cout << "Enter line number i: \n"; //построчное заполнение матрицы значениями
		std::cout << "\t(message: -1 to stop entering values into the matrix) \n";
		std::cout << "\t(message: numbering from 0) \n";
		getNum(i);

		while (i != -1) {
			while (i >=m || i < 0)
			{
				std::cout << "\tInvalid index. Please enter correct index i: \n";
				getNum(i);
				if (i == -1) {
					return;
				}
			}
			std::cout << "Enter column number j: \n"; //ввод значения в матрицу
			flag = 0;
			getNum(j);
			if (j >= 0 && j < n) {
				list* ptr, * prev;
				prev = arr.line + i;
				ptr = prev->next;
				while (ptr != nullptr) {
					if (j == ptr->j) {
						std::cout << "\tError. An element with this index already exists. \n";
						flag = -1;
						break;
					}
					else if (ptr->j > j) {
						break;
					}
					prev = prev->next;
					ptr = ptr->next;
				}
				if (flag != -1) {
					prev->next = new list;
					prev->next->j = j;
					prev->next->next = ptr;
					std::cout << "Enter value: \n";
					getNum(prev->next->val);
				}
			}
			else {
				std::cout << "\tCell with such index does not exist. \n";
			}

			std::cout << "Enter line number i: \n";
			getNum(i);
		}
		std::cout << "End of input. \n";
		return;
	}
	
	// возвращение эл-та ai1
	double extract(struct matrix arr, int i) {
		double a;
		if (arr.line[i].next != nullptr) {
			struct list* ptr = arr.line[i].next;
			if (ptr->j != 0) {
				a = 0;
			}
			else {
				a = ptr->val;
			}
		}
		else {
			a = 0;
		}
		return a;
	}

	// сортировка строк матрицы
	void sort(struct matrix arr, int (*f)(double, double)) {
		for (int i = 0; i < arr.m; i++) {
			double a = extract(arr, i);
			for (int j = i + 1; j < arr.m; j++) {
				double b = extract(arr, j);
				if (f(a,b)) {
					struct list el, p, tmp;
					el = arr.line[i];
					arr.line[i] = arr.line[j];
					arr.line[j] = el;
					a = b;
				}
			}
		}
	}

	// создание новой матрицы
	struct matrix edit(struct matrix arr) {
		struct matrix reorg;
		reorg.m = arr.m;
		reorg.n = arr.n;
		try {
			reorg.line = new list[arr.m]; // выделение памяти под массив строк матрицы
		}
		catch (std::bad_alloc& ba)
		{
			std::cout << " Exception caught: " << ba.what() << std::endl;
			reorg.m = 0;
			return reorg;
		}

		for (int i = 0; i < arr.m; i++)
		{
			reorg.line[i].next = nullptr; // инициализация массива указателей nullptr
			reorg.line[i].j = -1;
		}

		// заполнение  матрицы значениями
		for (int i = 0; i < arr.m; i++) {
			list* ptr = arr.line + i; // указатель на элементы строки старой матрицы
			ptr = ptr->next;
			list* prev = reorg.line + i;
			list* now = (reorg.line+i)->next; // указатель на элементы строки новой матрицы
			while (ptr != nullptr) { // копирование значений в строку из старой матрицы
				now = new struct list;
				now->j = ptr->j;
				now->next = nullptr;
				now->val = ptr->val;
				prev->next = now;
				prev = now;
				ptr = ptr->next;
			}
		}
		if (extract(arr, 0) > 0) {// сортировка в зависимости от значения  эл-та a11
			sort(reorg, isless);
		}
		else {
			sort(reorg, isgreater);
		}
		return reorg;
	}

	// вывод матрицы
	void output(struct matrix arr) {

		for (int i = 0; i < arr.m; i++) {
			struct list* el = arr.line + i;
			struct list* prev = el;
			el = el->next; 
			
			while (el != nullptr) {
				for  (int j = (prev->j)+1; j < el->j; j++) { //вывод "0" между известными значениями
					std::cout << "0\t";
				}
				std::cout << el->val << "\t";
				prev = el;
				el = el->next;
			}
			for (int j = (prev->j)+1; j < arr.n; j++) { //вывод "0" после последнего известного значения
				std::cout << "0\t";
			}
			std::cout << std::endl; 
		}
		return;
	}

	// очистка памяти
	void free_m(struct matrix arr)
	{
		for (int i = 0; i < arr.m; i++) {
			struct list* el = arr.line + i;
			struct list* prev = el;
			el = el->next;
			while (el != nullptr) {
				prev = el;
				el = el->next;
				delete(prev);
			}
		}
		delete[]arr.line;
		return;
	}
}