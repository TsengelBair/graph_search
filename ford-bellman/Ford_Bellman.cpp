#include <iostream>
#include <vector>
#include <climits>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::max;

const int INF = 100000;

vector<int>bellman_ford(const vector<pair<pair<int, int>, int>>&graf, int start) {
	// Определяем размер графа
	int n{0};
	for (const auto& edge : graf) {
		n = max({ edge.first.first, edge.first.second });
	}
	n++;

	// Массив расстояний и инициализация стартовой точки нулем
	vector<int>dist(n, INF);
	dist[start] = 0;

	// Релаксация
	for (int i = 0; i < n - 1; i++) {
		for (const auto& edge : graf) {
			int u = edge.first.first;
			int v = edge.first.second;
			int weight = edge.second;

			if (dist[u] != INF and dist[v] > dist[u] + weight) {
				dist[v] = dist[u] + weight;
			}
		}
	}

	return dist;
};

int main() {
	vector<pair<pair<int, int>, int>>graf = {
		{{0, 1}, -1}, 
		{{0, 2}, 4},
		{{1, 2}, 3},
		{{1, 3}, 2},
		{{1, 4}, 2},
		{{3, 1}, 1},
		{{3, 2}, 5},
		{{4, 3}, -3}
	};

	int start = 0;
	vector<int>res = bellman_ford(graf, start);
	for (int i = 0; i < res.size(); i++) {
		cout << res[i] << " ";
	}
}




