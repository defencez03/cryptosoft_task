#include "Resource.h"


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
					ptr->next = cell->next;
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

pqueue::Cell* pqueue::min() { return this->last; }

int pqueue::size() {
	Cell* cell = first;
	int num = 0;

	while (cell != NULL) {
		num += 1;
		cell = cell->next;
	}

	return num;
}

void pqueue::delCell(Cell* search_cell) {
	Cell* cell = first;
	while (cell != NULL) {
		if (cell == search_cell) {
			if (cell->prev != NULL || cell->next != NULL) {
				if (cell->prev != NULL) {
					cell->prev->next = cell->next;
				}
				else first = cell->next;

				if (cell->next != NULL) {
					cell->next->prev = cell->prev;
				}
				else last = cell->prev;

				delete cell;
			}
			else {
				delete cell;
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

void pqueue::clear() {
	Cell* cell = first, * sw = NULL;

	while (cell != NULL) {
		sw = cell;
		cell = cell->next;
		delete sw;
	}
}

pqueue::Cell::~Cell() { delete this->data; }