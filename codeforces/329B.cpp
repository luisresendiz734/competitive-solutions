#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> forest(n);
    int sr, sc, er, ec;
    for(int i = 0; i < n; ++i) {
        cin >> forest[i];
        for(int j = 0; j < m; ++j) {
            if(forest[i][j] == 'S') {
                sr = i;
                sc = j;
            }
            if(forest[i][j] == 'E') {
                er = i;
                ec = j;
            }
        }
    }
    queue<int> q;
    vector<vector<int>> visited(1005, vector<int>(1005, -1));
    vector<int> dr = {0, 0, 1, -1};
    vector<int> dc = {1, -1, 0, 0};
    auto isValid = [&](int r, int c) {
        return 0 <= r && r < n && 0 <= c && c < m && visited[r][c] == -1 && forest[r][c] != 'T';
    };
    q.push(er);
    q.push(ec);
    int r, c;
    visited[er][ec] = 0;
    while(not q.empty()) {
        r = q.front();
        q.pop();
        c = q.front();
        q.pop();
        for(int i =  0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(isValid(nr, nc)) {
                visited[nr][nc] = visited[r][c] + 1;
                q.push(nr);
                q.push(nc);
            }
        }
    }
    int goal = visited[sr][sc];
    int ans = 0;
    auto isDigit = [&](char x) {
        return x - '0' >= 0 && x - '0' <= 9;
    };
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(visited[i][j] != -1 && isDigit(forest[i][j]) && visited[i][j] <= goal) {
                ans += forest[i][j] - '0';
            }
        }
    }
    cout << ans << endl;
    return 0;
}