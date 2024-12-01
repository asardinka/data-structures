#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

void print(vector<vector<int>> m){
    for (int i = 0; i < m.size(); i++){
        for (int j = 0; j < m.size(); j++)
            cout << m[i][j] << " "; 
        cout << endl;
    }
    cout << endl;
}

class Edge
{
public:
    int from, to, weight;
    Edge(int from = -1, int to = -1, int weight = 0) : from(from), to(to), weight(weight) {}
    Edge(const Edge& E)
    {
        from = E.from;
        to = E.to;
        weight = E.weight;
    }
    bool operator<(const Edge& E) const
    {
        return weight > E.weight;
    }
    friend ostream& operator<<(ostream& s, const Edge& e)
    {
        s << "From: " << e.from << ", to: " << e.to << ", weight: " << e.weight;
        return s;
    }
};

vector<vector<int>> Prim(vector<vector<int>> mat, Edge e) {
    int n = mat.size();
    vector<vector<int>> mst(n, vector<int>(n, 0));
    vector<bool> used(n, false);
    priority_queue<Edge> pq;
    vector<Edge> result;
    int sumWeight = 0;
    used[e.from] = true;
    pq.push(e);
    while (!pq.empty()) {
        Edge minEdge = pq.top();
        pq.pop();
        if (used[minEdge.to]) {
            continue;
        }
        result.push_back(minEdge);
        sumWeight += minEdge.weight;
        used[minEdge.to] = true;
        for (int i = 0; i < n; ++i) {
            if (mat[minEdge.to][i] != 0 && !used[i]) {
                pq.push(Edge(minEdge.to, i, mat[minEdge.to][i]));
            }
        }
    }
    for (const auto& edge : result) {
        mst[edge.from][edge.to] = edge.weight;
        mst[edge.to][edge.from] = edge.weight;
    }
    cout << "Minimum Spanning Tree Edges:" << endl;
    for (auto& edge : result) {
        cout << edge << endl;
    }
    cout << endl << "Total Weight: " << sumWeight << endl << endl;

    return mst;
}
void BFS(vector<vector<int>> mat, int v) {
    int n = mat.size();
    vector<bool> used_bfs(n, false);
    vector<int> dist_bfs(n, -1);
    vector<int> degree(n, 0);

    queue<int> q;
    q.push(v);
    dist_bfs[v] = 0;
    used_bfs[v] = true;
    while (!q.empty()) {
        int cur_vertex = q.front();
        q.pop();
        for (int i = 0; i < n; i++) {
            if (mat[cur_vertex][i] != 0 && used_bfs[i] == 0) {
                q.push(i);
                used_bfs[i] = true;
                dist_bfs[i] = dist_bfs[cur_vertex] + 1;
            }
            if (mat[cur_vertex][i] != 0) {
                degree[cur_vertex]++;
            }
        }
        used_bfs[cur_vertex] = 2;
    }
    int sumDegree = 0;
    cout << "Degrees of vertices: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i << ": Degree = " << degree[i] << " " << endl;
        sumDegree += degree[i];
    }
    cout << endl;
    double avg = static_cast<double>(sumDegree) / n;
    cout << "Average Degree: " << avg << endl << endl;
    cout << "BFS Distances: " << endl;
    for (int i = 0; i < n; i++) {
        cout << v << " - " << i << ": " << dist_bfs[i] << " " << endl;
    }
    cout << endl;
}
void DFS(const vector<vector<int>>& matrix, int v) {
    int n = matrix.size();
    vector<bool> visited(n, false);
    stack<int> s;
    s.push(v);
    vector<int> result;
    while (!s.empty()) {
        int v = s.top();
        s.pop();
        if (!visited[v]) {
            visited[v] = true;
            result.push_back(v);
            for (int i = n - 1; i >= 0; --i) {
                if (matrix[v][i] != 0 && !visited[i]) {
                    s.push(i);
                }
            }
        }
    }
    cout << "DFS Steps: ";
    for (int v : result) {
        cout << v << " ";
    }
    cout << endl << endl;
}
void Dijkstra(vector<vector<int>> mat, int v) {
    int n = mat.size();
    vector<int> dist_dijkstra(n, INT_MAX);
    vector<bool> used_dijkstra(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist_dijkstra[v] = 0;
    pq.push({0, v});

    while (!pq.empty()) {
        int cur_dist = pq.top().first;
        int cur_vertex = pq.top().second;
        pq.pop();

        if (used_dijkstra[cur_vertex]) continue;
        used_dijkstra[cur_vertex] = true;

        for (int i = 0; i < n; i++) {
            if (mat[cur_vertex][i] != 0 && dist_dijkstra[i] > cur_dist + mat[cur_vertex][i]) {
                dist_dijkstra[i] = cur_dist + mat[cur_vertex][i];
                pq.push({dist_dijkstra[i], i});
            }
        }
    }

    cout << "Dijkstra Distances: " << endl;
    for (int i = 0; i < n; i++) {
        cout << v << " - " << i << ": " << dist_dijkstra[i] << " " << endl;
    }
    cout << endl << endl;
}
int main() {
    vector<vector<int>> matrix = {
        {0, 5, 3, 1, 0, 3, 4, 3, 6, 0, 4},
        {5, 0, 6, 7, 9, 4, 3, 3, 6, 9, 6},
        {3, 6, 0, 4, 5, 1, 9, 5, 3, 1, 8},
        {1, 7, 4, 0, 5, 5, 2, 4, 2, 5, 8},
        {0, 9, 5, 5, 0, 3, 8, 2, 6, 4, 3},
        {3, 4, 1, 5, 3, 0, 3, 2, 2, 2, 8},
        {4, 3, 9, 2, 8, 3, 0, 7, 6, 7, 6},
        {3, 3, 5, 4, 2, 2, 7, 0, 4, 3, 4},
        {6, 6, 3, 2, 6, 2, 6, 4, 0, 7, 3},
        {0, 9, 1, 5, 4, 2, 7, 3, 7, 0, 9},
        {4, 6, 8, 8, 3, 8, 6, 4, 3, 9, 0}
    };
    int v = 0;
    vector<vector<int>> newMatrix = Prim(matrix, Edge(0, 1, 5));
    print(newMatrix);
    BFS(newMatrix, v);
    DFS(newMatrix, v);
    Dijkstra(newMatrix, v);
    
    //Изображение графа: https://disk.yandex.ru/i/W_mbKA5BztVBeQ
}
