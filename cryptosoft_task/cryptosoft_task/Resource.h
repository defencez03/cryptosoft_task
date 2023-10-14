#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <iomanip>
#include "Pqueue.h"
using namespace std;


vector<vector<double>> scanFile(ifstream& fcin);

void totalPoints(vector<vector<double>>& mass, vector<vector<double>>& points);

double** generateGraph(const vector<vector<double>>& points, const vector<vector<double>>& mass);

void clearMemory(double** G, const vector<vector<double>>& points);

double BFC(double** G, pqueue& unvisited, vector<double> visited, const vector<vector<double>>& points, int num);