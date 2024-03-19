#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::priority_queue;
using std::pair;
using std::greater;
using std::make_pair;

const int INF = 10000; // для инициализации

vector<int>dkstra(vector<vector<int>>&graph, int start, int end) {
	vector<int>dist(graph.size(), INF);
	vector<int>from(graph.size(), -1);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>q; // очередь с приоритетом в порядке возрастания

	dist[start] = 0;
	q.push(make_pair(0, start));

	while (!q.empty()) {
		// Извлекаем длина и вершину
		int distance = q.top().first;
		int v = q.top().second;
		q.pop();

		if (distance > dist[v]) continue; // Если извлеченная длина больше имеющейся, пропускаем
		for (size_t i = 0; i < graph[v].size(); i++) {
			int to = i;
			int weight = graph[v][i];
			if (dist[to] > dist[v] + weight) {
				dist[to] = dist[v] + weight;
				from[to] = v;
				q.push(make_pair(dist[to], to));
			}
		}
	}

	vector<int>path; // результирующий вектор с маршрутом
	for (int v = end; v != -1; v = from[v]) {
		path.push_back(v);
	}
	reverse(path.begin(), path.end()); // переворачиваем, т.к. добавляли в конец
	return path;
}

int main() {
	// Граф - матрица смежности
	vector<vector<int>>graph = {
		{0, 1, 1},
		{4, 0, 1},
		{2, 1, 0}
	};
	int start = 2;
	int end = 1;

	// Декремент, т.к. индексация с нуля
	start--;
	end--;

	vector<int>res = dkstra(graph, start, end);
	for (int i = 0; i < graph.size(); i++) {
		cout << res[i] + 1 << " "; // +1 из-за декремента
	}
}