#include <iostream>
#include <vector>
#include <algorithm>
#include <utility> 

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::max;

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
