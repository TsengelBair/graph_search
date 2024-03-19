#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::queue;
using std::pair;

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
