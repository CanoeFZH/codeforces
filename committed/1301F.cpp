#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1010;
const int C = 45;

int n, m, c;
int cost[C][N][N], grid_color[N][N];
bool done[C];

queue < pair<int, int> > q;
vector < pair<int, int> > color_grids[C];

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};

void BFS(int color) {
    for (auto p: color_grids[color]) {
        cost[color][p.first][p.second] = 0;
        q.push(p);
    }

    for(int c = 1; c <= C; c++) {
        done[c] = false;
    }

    while(!q.empty()) {
        pair<int, int> cell = q.front();
        q.pop();
        int current_row = cell.first;
        int current_column = cell.second;
        int current_color = grid_color[current_row][current_column];
        int current_cost = cost[color][current_row][current_column];
        if (!done[current_color]) {
            done[current_color] = true;
            for(auto same_color_grid: color_grids[current_color]) {
                int next_row = same_color_grid.first;
                int next_column = same_color_grid.second;
                if (cost[color][next_row][next_column] == -1) {
                    cost[color][next_row][next_column] = current_cost + 1;
                    q.push(same_color_grid);
                }
            }
        }
        
        for(int i = 0; i < 4; i++) {
            int next_row = current_row + dr[i];
            int next_column = current_column + dc[i];
            if (next_row >= 0 && next_row < n && next_column >= 0 && next_column <= m && cost[color][next_row][next_column] == -1) {
                cost[color][next_row][next_column] = current_cost + 1;
                q.push(make_pair(next_row, next_column));
            }
        }
    }
}

int main() {
    cin >> n >> m >> c;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> grid_color[i][j];
            color_grids[grid_color[i][j]].push_back(make_pair(i, j));
        }
    }

    memset(cost, -1, sizeof(cost));

    for(int i = 1; i <= c; i++) {
        BFS(i);
    }

    int q, rs, cs, rt, ct;
    for(cin >> q; q; q--) {
        cin >> rs >> cs >> rt >> ct;
        rs--, cs--, rt--, ct--;
        int ans = abs(rs - rt) + abs(cs - ct);
        for(int i = 1; i <= c; i++) {
            ans = min(ans, 1 + cost[i][rs][cs] + cost[i][rt][ct]);
        }
        cout << ans << endl;
    }

    return 0;
}