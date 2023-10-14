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

		// считал значения из файла в список
		mass = scanFile(fcin);

		// получил список вершин
		totalPoints(mass, points);

		// сгенерировал взвешанный граф
		G = generateGraph(points, mass);

		// получил наименьшее время сгорания фигуры
		sum = new double[points.size()] {};

		for (int i = 0; i < points.size(); i++) {
			sum[i] = BFC(G, unvisited, visited, points, i);
			visited.clear();
		}

		min_time = sum[0];

		for (int i = 0; i < points.size(); i++) {
			if (sum[i] < min_time && (int)points[i][0] % 2 == 0 &&
					(int)points[i][1] % 2 == 0) {
				min_time = sum[i];
				value = i;
			}
		}

		// записал результат в файл
		fout << points[value][0] / 2 << " " << points[value][1] / 2 << endl;
		fout << fixed;
		fout << setprecision(2);
		fout << min_time << endl;

		//очистил память
		delete[] sum;
		clearMemory(G, points);
	}
	else cout << "File not found...";

	fcin.close();
	fout.close();

	return 0;
}