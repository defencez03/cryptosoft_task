#include "Resource.h"


// Добавление элемента в очередь
void pqueue::push(double time, int val) {
	Cell* ptr = new Cell;
	ptr->data->time = time;
	ptr->data->val = val;

	if (first == NULL) {
		first = ptr;
		last = ptr;
	}
	else {
		Cell* cell = last;
		while (cell != NULL) {
			if (ptr->data->time < cell->data->time) {
				ptr->prev = cell;
				if (cell != last) {
					ptr->next = cell->next;					// Сортировка элементов очереди по времени (элементы с наименьшим временем в конец очереди)
					ptr->next->prev = ptr;
				}
				cell->next = ptr;
				if (cell == last) last = ptr;
				break;
			}
			cell = cell->prev;
			if (cell == NULL) {
				ptr->next = first;
				first->prev = ptr;
				first = ptr;
			}
		}
	}
}

// Удаление последнего элемента из очереди
void pqueue::pop() {
	Cell* sw;

	sw = last;
	if (first == last) {
		first = NULL;
		last = NULL;
	}
	else {
		last = last->prev;
		last->next = NULL;
	}
	delete sw;
}

pqueue::Cell* pqueue::getNext(Cell* cell) { return cell->next; }

pqueue::Cell* pqueue::getFirst() { return this->first; }

// Получение эелемента с наименьшим временем
pqueue::Cell* pqueue::min() { return this->last; }

// Определение размера очереди
int pqueue::size() {
	Cell* cell = first;
	int num = 0;

	while (cell != NULL) {
		num += 1;
		cell = cell->next;
	}

	return num;
}

// Удаление ячейки
void pqueue::delCell(Cell* search_cell) {
	Cell* cell = first;
	while (cell != NULL) {
		if (cell == search_cell) {
			if (cell->prev != NULL || cell->next != NULL) {
				if (cell->prev != NULL) {
					cell->prev->next = cell->next;			
				}
				else first = cell->next;					// Определение позиции ячейки
												// Если ячейка является поледней, то указателю last = предыдущая ячейка
				if (cell->next != NULL) {					// Если ячейка является первой, то указателю first = следующая ячейка
					cell->next->prev = cell->prev;
				}
				else last = cell->prev;

				delete cell;
			}
			else {
				delete cell;							// Если элемент один в очреди, то first И last обнуляются
				first = last = NULL;
			}
			break;
		}
		cell = cell->next;
	}
}

pqueue::~pqueue() {
	clear();
}

pqueue::Cell::Cell() { data = new Node; }

//Очитска очереди
void pqueue::clear() {
	Cell* cell = first, * sw = NULL;

	while (cell != NULL) {
		sw = cell;
		cell = cell->next;
		delete sw;
	}
}

pqueue::Cell::~Cell() { delete this->data; }
