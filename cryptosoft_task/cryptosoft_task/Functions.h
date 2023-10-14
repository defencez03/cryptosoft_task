#pragma once


vector<vector<string>> scanFile(ifstream& fcin);

void totalPoints(vector<vector<string>>& mass, vector<vector<string>>& points);

int** generateGraph(const vector<vector<string>>& points, const vector<vector<string>>& mass);

void clearMemory(int** G, const vector<vector<string>>& points);

void printGraph(int** G, const vector<vector<string>>& points);
