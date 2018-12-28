#include <queue>
#include <list>
#include <iostream>
#include <algorithm>


int find_ways( std::vector<std::list<int>>& matrix, int begin, int end) {
    std::queue<int> q;
    int size = matrix.size();
    std::vector<int> pi(size, 1);
    std::vector<bool> used(size, false);
    std::vector<int> d(size, 0);
    used[begin] = true;
    q.push(begin);
    pi[end] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        auto i = matrix[u].begin(), end = matrix[u].end();
        for (; i != end; i++) {
                int to = *i;
                if (!used[to]) {
                    used[to] = true;
                    q.push(to);
                    d[to] = d[u] + 1;
                    pi[to] = pi[u];
                } else {
                    if (d[to] == d[u] + 1) {
                        pi[to] += pi[u];
                     }

                }
            }

    }
    return pi[end];

}

int main()
{
    int m, n;
    std::cin >> m;
    std::cin >> n;
    std::vector<std::list<int>> matrix(m, std::list<int>(0));
    for(int i = 0; i < n; i++){
        int ii, jj;
        std::cin >> ii >> jj;
        matrix[ii].push_back(jj);
        matrix[jj].push_back(ii);

    }

    int begin, end;
    std::cin >> begin >> end;

    std::cout << find_ways(matrix, begin, end);

}
