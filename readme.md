# Поиск кратчайших путей на графе

## BFS (поиск в ширину)

![граф для bfs](https://github.com/TsengelBair/graph_search/blob/master/bfs.jpg)

[Поиск в ширину (улГТУ)](https://www.youtube.com/watch?v=4iDv8Zu8L3I&list=PLGhUJWLZ8uQ4EWdQwVyUFnz82kbeGRP97)

[bresprog](https://brestprog.by/topics/bfs/)

`код`

```c++
const int INF = 10000; // для инициализации

pair<vector<int>, vector<int>> bfs(vector<vector<int>>& graf, int start) {
    // Создаем массив расстояний, массив from для восстановления пути и очередь
    vector<int> dist(graf.size(), INF);
    vector<int> from(graf.size(), -1);
    queue<int> q;

    // Инициализируем стартовую точку нулем и закидываем в очередь
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        // Извлекаем вершину из очереди
        int v = q.front();
        q.pop();

        // В цикле просматриваем соседей
        for (int to : graf[v]) {
            if (dist[to] > dist[v] + 1) {
                dist[to] = dist[v] + 1;
                from[to] = v;
                q.push(to);
            }
        }
    }
    return { dist, from };
}

// Ф-ция для восстановления пути
vector<int> restorePath(vector<int>& from, int end) {
    vector<int> path;
    for (int v = end; v != -1; v = from[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    setlocale(LC_ALL, "ru");
    // Граф задан списком смежности
    vector<vector<int>> graf = {
        {1, 2},
        {0, 2, 3},
        {0, 1, 4, 5},
        {1, 4},
        {2, 3, 5},
        {2, 4, 6},
        {5},
    };

    int start = 0;
    int end = 6;

    // bfs для поиска в ширину
    pair <vector<int>, vector<int>> res = bfs(graf, start);
    // Восстанавливаем путь
    vector<int> path = restorePath(res.second, end);

    cout << "Путь от вершины " << start << " до вершины " << end << ": ";
    for (int v : path) {
        cout << v << " ";
    }
}
```

## Дейкстра (очередь с приоритетом)

![граф для дейкстры](https://github.com/TsengelBair/graph_search/blob/master/dkstar.jpg)

[Идея алгоритма Дейкстры (улГТУ)](https://www.youtube.com/watch?v=fA_xvuqzuGs&t=458s)

[Код и два варианта (улГТУ)](https://www.youtube.com/watch?v=J-7MzbEtTR0&t=222s)

`код`

```c++
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
```

## Алгоритм Флойда-Уоршелла

![Суть алгоритма](https://github.com/TsengelBair/graph_search/blob/master/floyd_warshall_thesis.jpg)

![граф для уоршелла](https://github.com/TsengelBair/graph_search/blob/master/warshall.jpg)

[Идея алгоритма Флойда-Уоршелла (улГТУ)](https://www.youtube.com/watch?v=kaA3_qNfpCA)

`код`

```c++
const int INF = 10000;

vector<vector<int>> floydWarshall(const vector<pair<pair<int, int>, int>>& graf) {
    // Для определения размера графа
    int n = 0;
    for (const auto& edge : graf) {
        n = max({ n, edge.first.first, edge.first.second });
    }
    n++; // Увеличиваем n на 1, так как индексы начинаются с 0

    vector<vector<int>> dist(n, vector<int>(n, INF)); // результирующая матрица
    // Главная диагональ - нули
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    // Заполняем матрицу dist значениями графа
    for (const auto& edge : graf) {
        int u = edge.first.first;
        int v = edge.first.second;
        int weight = edge.second;
        dist[u][v] = weight;
    }

    // алгоритм
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return dist;
}

int main() {
    vector<pair<pair<int, int>, int>> graf = {
        {{0, 1}, 5},
        {{1, 2}, 5},
        {{1, 3}, 3},
        {{2, 0}, -3},
        {{3, 0}, 2},
        {{3, 2}, -5}
    };

    vector<vector<int>> res = floydWarshall(graf);
    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < res[i].size(); j++) {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
```

## Алгоритм Форда-Беллмана

![граф для Форда-Беллмана](https://github.com/TsengelBair/graph_search/blob/master/ford-bellman.jpg)

[Хабр](https://habr.com/ru/companies/otus/articles/484382/)

[Алгоритм Форда-Беллмана (улГТУ)](https://www.youtube.com/watch?v=cE5n2IKf7W4&list=PLGhUJWLZ8uQ4EWdQwVyUFnz82kbeGRP97&index=7)

`код`

```c++
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

```
