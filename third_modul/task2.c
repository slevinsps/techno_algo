#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>
#include <cstddef>
#include <cstdlib>
#include "stdio.h"
#include "string.h"
#include <iostream>
#include <assert.h>
#include <limits.h>
#include <ctime>
#include <utility>
#include <queue>
#include <list>
#include <set>
#include <iostream>
#include <algorithm>
#include <iterator>

typedef struct node_time {
    int n;
    int time;
    node_time(int n_v, int time_v) {
        n = n_v;
        time = time_v;
    }
    node_time& operator=(const node_time& v)  //перегрузка
    {
        n = v.n;
        time = v.time;
        return *this;  //возвращаем ссылку на текущий объект
    }
} node_time;

void MySwap(node_time& a1, node_time& a2) {
    node_time tmp = a1;
    a1 = a2;
    a2 = tmp;
}

void ShiftDown(std::vector<node_time>& arr, int i,
               std::vector<int>& pos_in_arr) {
    int n = arr.size();
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if (left < n && arr[left].time < arr[i].time) largest = left;
    if (right < n && arr[right].time < arr[largest].time) largest = right;
    if (largest != i) {
        std::cout << i << " " << largest << " " << pos_in_arr[arr[i].n] << " "
                  << pos_in_arr[arr[largest].n] << "!!! \n";
        std::swap(pos_in_arr[arr[i].n], pos_in_arr[arr[largest].n]);
        MySwap(arr[i], arr[largest]);

        ShiftDown(arr, largest, pos_in_arr);
    }
}

int ShiftUp(std::vector<node_time>& arr, int index,
            std::vector<int>& pos_in_arr) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (arr[index].time >= arr[parent].time) return index;
        std::swap(pos_in_arr[arr[index].n], pos_in_arr[arr[parent].n]);
        MySwap(arr[index], arr[parent]);

        index = parent;
    }
    return 0;
}

node_time ExtractMin(std::vector<node_time>& arr,
                     std::vector<int>& pos_in_arr) {
    assert(arr.size() != 0);
    node_time result = arr[0];
    pos_in_arr[arr[0].n] = -1;
    pos_in_arr[arr[arr.size() - 1].n] = 0;
    arr[0] = arr[arr.size() - 1];

    arr.erase(arr.begin() + arr.size() - 1);
    if (arr.size() != 0) {
        ShiftDown(arr, 0, pos_in_arr);
    }
    return result;
}

void HeapAdd(std::vector<node_time>& arr, node_time elem,
             std::vector<int>& pos_in_arr) {
    arr.push_back(elem);
    pos_in_arr[elem.n] = arr.size() - 1;
    ShiftUp(arr, arr.size() - 1, pos_in_arr);
}

void BuildHeap(std::vector<node_time>& arr, std::vector<int>& pos_in_arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        ShiftDown(arr, i, pos_in_arr);
    }
}

int min_num(std::vector<node_time>& arr) {
    int min = arr[0].time;
    int i_min = 0;
    for (int i = 1; i < arr.size(); i++) {
        if (min > arr[i].time) {
            min = arr[i].time;
            i_min = i;
        }
    }
    int a = arr[i_min].n;
    arr.erase(arr.begin() + i_min);
    return a;
}

int Dijkstra1(std::vector<std::list<std::pair<int, int>>>& w, int st, int end) {
    int n = w.size();
    bool visited[n];
    int D[n];
    for (int i = 0; i < n; i++) {
        D[i] = INT_MAX;
        visited[i] = false;
    }
    D[st] = 0;
    int index = 0, u = 0;
    for (int i = 0; i < n; i++) {
        int min = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && D[j] < min) {
                min = D[j];
                index = j;
            }
        }
        u = index;
        visited[u] = true;
        for (int j = 0; j < n; j++) {
            int dist = -1;
            auto begin = w[u].begin(), end = w[u].end();
            for (; begin != end; begin++) {
                if ((*begin).first == j) {
                    dist = (*begin).second;
                    break;
                }
            }
            if (dist == -1) continue;
            if (!visited[j] && D[u] != INT_MAX && (D[u] + dist < D[j])) {
                D[j] = D[u] + dist;
            }
        }
    }
    if (D[end] == INT_MAX) {
        D[end] = -1;
    }
    return D[end];
}
class comparator_set {
public:
    bool operator()(const std::pair<int, int>& lhs,
                    const std::pair<int, int>& rhs) const {
        return lhs.second <= rhs.second;
    }
};

int Dijkstra(std::vector<std::list<std::pair<int, int>>>& matrix, int begin,
             int end) {
    int size = matrix.size();
    std::vector<int> pi(size, -1);
    std::vector<bool> used(size, false);
    std::vector<int> d(size, INT_MAX);

    d[begin] = 0;
    std::set<std::pair<int, int>, comparator_set> city_set;
    city_set.insert(std::pair<int, int>(begin, d[begin]));
    while (!city_set.empty()) {
        int u = (*city_set.begin()).first;
        city_set.erase(city_set.begin());

        used[u] = true;

        auto i = matrix[u].begin(), end = matrix[u].end();

        for (; i != end; i++) {
            int v = (*i).first;
            if (!used[v]) {
                if (d[v] == INT_MAX) {
                    d[v] = d[u] + (*i).second;
                    city_set.insert(std::pair<int, int>(v, d[v]));
                } else {
                    if (d[v] > d[u] + (*i).second) {
                        auto bbegin = city_set.begin(), eend = city_set.end();
                        for (; bbegin != eend; bbegin++) {
                            if ((*bbegin).first == v) {
                                break;
                            }
                        }

                        city_set.erase(bbegin);
                        d[v] = d[u] + (*i).second;
                        pi[v] = u;
                        city_set.insert(std::pair<int, int>(v, d[v]));
                    }
                }
            }
        }
    }
    return d[end];
}

int main() {
    int m, n;
    int begin, end;
    std::cin >> m;
    std::cin >> n;
    std::vector<std::list<std::pair<int, int>>> matrix(m);
    for (int i = 0; i < n; i++) {
        int ii, jj, dist;
        std::cin >> ii >> jj >> dist;
        matrix[ii].push_back(std::pair<int, int>(jj, dist));
        matrix[jj].push_back(std::pair<int, int>(ii, dist));
        /*
        std::list<std::pair<int, int>>::iterator begin = matrix[ii].begin(), end =
        matrix[ii].end();
        for (; begin != end; begin++) {
            if ((*begin).first == jj) {
                break;
            }
        }
        if (begin != end) {
            if ((*begin).second > dist) {
                std::list<std::pair<int, int>>::iterator begin1 =
        matrix[jj].begin(), end1 = matrix[jj].end();
                auto list_value1 = std::find(begin1, end1, std::pair<int,
        int>(ii,(*begin).second));
                (*begin).second = dist;
                (*list_value1).second = dist;
            }
        } else {

        }*/
    }
    std::cin >> begin >> end;

    /*for(int i = 0; i < matrix.size(); i++) {
        std::cout << i << " - ";
        auto bbegin = matrix[i].begin(), eend = matrix[i].end();
        for (; bbegin != eend; bbegin++) {
            std::cout << (*bbegin).first << " " << (*bbegin).second << "; ";
        }
        std::cout << "\n";
    }*/

    /*int m, n; // тесты

    std::srand(unsigned(std::time(0)));
    for(int q = 0; q < 50; q++) {
        m = 2 + rand() % 8;
        std::vector<std::vector<int>> mat(m,std::vector<int>(m,0));
        std::vector<std::list<std::pair<int, int>>> matrix(m);
        int begin, end;
        begin = 0 + rand() % (m - 1);
        end = 0 + rand() % (m - 1);
        for(int i = 0; i < m; i++) {
            for(int j= 0; j < m; j++) {
                n = 0 + rand() % 10;
                mat[i][j] = n;
                if (i == j) {
                    n = 0;
                    mat[i][j] = 0;
                }
                if (n > 0) {
                    matrix[i].push_back(std::pair<int, int>(j,n));
                }
            }
        }
        int ans1 = Dijkstra(matrix, begin, end);
        int ans2 =  Dijkstra1(matrix, begin, end);
        if (ans1 != ans2) {
            for(int i = 0; i < m; i++) {
                for(int j= 0; j < m; j++) {
                    std::cout << mat[i][j] << " ";

                }
                std::cout <<"\n";
            }
            std::cout << begin << " " << end <<"\n";


            std::cout << "My = " << ans1 << "\n";
            std::cout << "Right = " << ans2 << "\n";
        }
        mat.clear();
        matrix.clear();
    }
    std::cout << "\nend";*/

    std::cout << Dijkstra(matrix, begin, end);
    return 0;
}
