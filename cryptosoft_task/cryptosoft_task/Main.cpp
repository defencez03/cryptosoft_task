#include "Resource.h"


int main() {
	setlocale(LC_ALL, "rus");

	vector<vector<double>> mass, points;
	vector<double> visited;
	pqueue unvisited;
	int value = 0;
	double min_time = 0;
	double* sum = NULL;
	double** G = NULL;

	ifstream fcin("f.in.txt");
	ofstream fout("f.out.txt");

	if (fcin.is_open()) {

		// Считывание значений из файла в список
		mass = scanFile(fcin);

		// Получение списка вершин
		totalPoints(mass, points);

		// Генерация граф
		G = generateGraph(points, mass);

		// Получение наименьшего времени сгорания фигуры
		sum = new double[points.size()] {};

		for (int i = 0; i < points.size(); i++) {
			sum[i] = BFC(G, unvisited, visited, points, i);						// Опредиление времени сгорания фигуры из всех точек
			visited.clear();
		}

		min_time = sum[0];

		for (int i = 0; i < points.size(); i++) {
			if (sum[i] < min_time && (int)points[i][0] % 2 == 0 &&				// Поиск наименьшего времени сгорания
					(int)points[i][1] % 2 == 0) {
				min_time = sum[i];
				value = i;
			}
		}

		// Запись результата в файл
		fout << points[value][0] / 2 << " " << points[value][1] / 2 << endl;
		fout << fixed;
		fout << setprecision(2);
		fout << min_time << endl;

		// Очистка памяти
		delete[] sum;
		clearMemory(G, points);
	}
	else cout << "File not found...";

	fcin.close();
	fout.close();

	return 0;
}