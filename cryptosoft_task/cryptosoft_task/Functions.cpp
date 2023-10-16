#include "Resource.h"

// Считывание данных из файла
vector<vector<double>> scanFile(ifstream& fcin) {
	int points;
	vector<double> mas_buff;
	vector<vector<double>> mass;
	int buff;

	fcin >> points;
	for (int i = 0; i < points; i++) {
		for (int j = 0; j < 5; j++) {
			fcin >> buff;
			mas_buff.push_back(buff);
		}
		mass.push_back({ mas_buff[0] * 2, mas_buff[1] * 2,
						 mas_buff[0] + mas_buff[2],
						 mas_buff[1] + mas_buff[3],					
						 mas_buff[4] / 2});						// Увеличение фигуры и запись промежуточных точек
		mass.push_back({ mas_buff[0] + mas_buff[2],							// Уменьшение вренеи прохождения в 2 раза
						 mas_buff[1] + mas_buff[3],					// Пример: до увеличения (11-22), после (22-33, 33-44)
						 mas_buff[2] * 2, mas_buff[3] * 2,
						 mas_buff[4] / 2 });
		mas_buff.clear();
	}
	return mass;
}

// Запись точек в список вершин из списка связей между точками
void totalPoints(vector<vector<double>>& mass, vector<vector<double>>& points) {
	bool p_start = 1, p_end = 1;

	for (int i = 0; i < mass.size(); i++) {
		p_start = 1, p_end = 1;
		if (i == 0) {
			points.push_back({ mass[i][0], mass[i][1] });
			points.push_back({ mass[i][2], mass[i][3] });
			continue;
		}
		for (int j = 0; j < points.size(); j++) {
			if (mass[i][0] == points[j][0] && mass[i][1] == points[j][1]) {			
				p_start = 0;
			}
			if (mass[i][2] == points[j][0] && mass[i][3] == points[j][1]) {				// Проверка наличия точки в списке вершин
				p_end = 0;
			}
			if (p_start == 0 && p_end == 0) break;
		}
		if (p_start == 1) {
			points.push_back({ mass[i][0], mass[i][1] });
		}
		if (p_end == 1) {
			points.push_back({ mass[i][2], mass[i][3] });
		}
	}
}

// Создание графа(матрицы смежности)
double** generateGraph(const vector<vector<double>>& points, const vector<vector<double>>& mass) {
	
	int p_size = points.size();
	int m_size = mass.size();
	int count = 0;
	double** G = new double*[p_size]{0};

	for (int i = 0; i < p_size; i++) {
		G[i] = new double[p_size]{0};
	}

	// Заполнение графа смежности 
	for (int i = 0; i < p_size; i++) {
		for (int j = 0; j < m_size; j++) {
			if (points[i][0] == mass[j][0] && points[i][1] == mass[j][1]) {
				for (int k = 0; k < p_size; k++) {
					if (points[k][0] == mass[j][2] && points[k][1] == mass[j][3]) {		// Сравнение точек из списка со связанными точками и списком точек
						G[i][k] = mass[j][4];						// Добавление времени сгорания спички по индексам из списка точек(вес ребра)
						G[k][i] = mass[j][4];											
					}
				}
			}
			else if (points[i][0] == mass[j][2] && points[i][1] == mass[j][3]) {
				for (int k = 0; k < p_size; k++) {
					if (points[k][0] == mass[j][0] && points[k][1] == mass[j][1]) {
						G[i][k] = mass[j][4];
						G[k][i] = mass[j][4];
					}
				}
			}
		}
	}

	return G;
}

// Очитска выделенной памяти
void clearMemory(double** G, const vector<vector<double>>& points) {
	int p_size = points.size();

	for (int i = 0; i < p_size; i++) {
		delete[] G[i];
	}

	delete[] G;
}

// Функция обхода графа в ширину (алгоритм Дейкстры)
double BFC(double** G, pqueue& unvisited, vector<double> visited, const vector<vector<double>>& points, int num) {
	bool ans = 0;
	double sum = 0;

	visited.push_back(num);
	for (int i = 0; i < points.size(); i++) {
		ans = 0;
		if (G[num][i] > 0) {
			for (int j = 0; j < visited.size(); j++) {						// Добавление в список непосещенных точек  
				if (i == visited[j]) ans = 1;							// Добавление структуры, содержащую номер вершины и время прохождения до нее
			}
			if (ans == 0) unvisited.push(G[num][i], i);
		}
	}

	if (unvisited.size() != 0) {
		num = unvisited.min()->data->val;
		pqueue::Cell* cell = unvisited.getFirst(), * last_cell = unvisited.min();			// Запись номера вершины из списка непосещенных вершин
		while (cell != last_cell) {
			cell->data->time -= last_cell->data->time;
			if (last_cell->data->val == cell->data->val)						// Прохождение по списку непомещенных вершин и изменение время сгорания спички(ребра)
				cell->data->time /= 2;								// Если посещаемая точка есть в списке непосещенных точек,
			cell = cell->next;									// то время сокращается в 2 раза
		}
		sum += last_cell->data->time;
		unvisited.pop();
		sum += BFC(G, unvisited, visited, points, num);
	}

	return sum;
}
