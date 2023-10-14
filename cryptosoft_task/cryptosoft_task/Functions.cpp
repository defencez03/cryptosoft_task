#include "Resource.h"


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
						 mas_buff[4] / 2});
		mass.push_back({ mas_buff[0] + mas_buff[2],
						 mas_buff[1] + mas_buff[3],
						 mas_buff[2] * 2, mas_buff[3] * 2,
						 mas_buff[4] / 2 });
		mas_buff.clear();
	}
	return mass;
}

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
			if (mass[i][2] == points[j][0] && mass[i][3] == points[j][1]) {
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

double** generateGraph(const vector<vector<double>>& points, const vector<vector<double>>& mass) {
	
	int p_size = points.size();
	int m_size = mass.size();
	int count = 0;
	double** G = new double*[p_size]{0};

	for (int i = 0; i < p_size; i++) {
		G[i] = new double[p_size]{0};
	}

	for (int i = 0; i < p_size; i++) {
		for (int j = 0; j < m_size; j++) {
			if (points[i][0] == mass[j][0] && points[i][1] == mass[j][1]) {
				for (int k = 0; k < p_size; k++) {
					if (points[k][0] == mass[j][2] && points[k][1] == mass[j][3]) {
						G[i][k] = mass[j][4];
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

void clearMemory(double** G, const vector<vector<double>>& points) {
	int p_size = points.size();

	for (int i = 0; i < p_size; i++) {
		delete[] G[i];
	}

	delete[] G;
}

double BFC(double** G, pqueue& unvisited, vector<double> visited, const vector<vector<double>>& points, int num) {
	bool ans = 0;
	double sum = 0;

	visited.push_back(num);
	for (int i = 0; i < points.size(); i++) {
		ans = 0;
		if (G[num][i] > 0) {
			for (int j = 0; j < visited.size(); j++) {
				if (i == visited[j]) ans = 1;
			}
			if (ans == 0) unvisited.push(G[num][i], i);
		}
	}

	if (unvisited.size() != 0) {
		num = unvisited.min()->data->val;
		pqueue::Cell* cell = unvisited.getFirst(), * last_cell = unvisited.min();
		while (cell != last_cell) {
			cell->data->time -= last_cell->data->time;
			if (last_cell->data->val == cell->data->val)
				cell->data->time /= 2;
			cell = cell->next;
		}
		sum += last_cell->data->time;
		unvisited.pop();
		sum += BFC(G, unvisited, visited, points, num);
	}

	return sum;
}