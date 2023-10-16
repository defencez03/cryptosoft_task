#pragma once


struct Node {
	int val = 0;
	double time = 0;
};

// Приоритетная очередь
class pqueue {
public:
	struct Cell {
		Cell* next = NULL, * prev = NULL;
		Node* data;
		Cell();
		~Cell();
	};

private:
	Cell* first = NULL, * last = NULL;

public:
	void push(double time, int val);
	void pop();
	Cell* getNext(Cell* cell);
	Cell* getFirst();
	Cell* min();
	int size();
	void delCell(Cell* search_cell);
	void clear();
	~pqueue();
};
