#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

#define L(i,j,k) for(int i=(j);i<=(k);++i)
#define R(i,j,k) for(int i=(j);i>=(k);--i)

int dx[4] = { 0,0,1,-1 }, dy[4] = { 1,-1,0,0 };
const int _ = 3005, inf = 3005 * 3005 + 1;

char grid[_][_];
int N, M, dog_cnt = 0, dis_exits[_][_];
pair<int, int> dis[_][_][2];
vector<int> bfs_layer[_ * _ / 2 + 5000 * 2];

bool can_go(int x, int y) { 
    return x >= 1 && x <= N && y >= 1 && y <= M && grid[x][y] != '#'; 
}

bool painted[_][_];
void paint(int x, int y) {
    if (painted[x][y]) return;
    painted[x][y] = true;
    for (int dir = 0; dir < 4; dir++) {
        int xx = x + dx[dir], yy = y + dy[dir];
        if (can_go(xx, yy) && !painted[xx][yy]) paint(xx, yy);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> N >> M;
    L(i, 1, N) {
        L(j, 1, M) {
            cin >> grid[i][j];
        }
    }
    L(i, 1, N) L(j, 1, M) dis[i][j][0] = dis[i][j][1] = { inf,inf };

    queue<int> Q; // (coordinate * 2 + op is odd)
    auto compress = [&](int x, int y) { return x * (M + 1) + y; };
    auto unzip = [&](int x) { return make_pair(x / (M + 1), x % (M + 1)); };

    L(i, 1, N) L(j, 1, M) {
        if (grid[i][j] == 'd') { // is a dog, we push into the queue
            int T = compress(i, j);
            Q.push(T << 1);
            dis[i][j][0] = { 0, ++dog_cnt };
        }
    }

    while (Q.size()) {
        auto p = Q.front(); Q.pop();
        int G = p / 2, op = p & 1;
        auto T = unzip(G);
        int x = T.first, y = T.second;
        for (int dir = 0; dir < 4; dir++) {
            int xx = x + dx[dir], yy = y + dy[dir];
            if (can_go(xx, yy)) {
                if (dis[xx][yy][0].first > dis[x][y][op].first + 1) {
                    dis[xx][yy][0] = make_pair(dis[x][y][op].first + 1, dis[x][y][op].second);
                    Q.push(compress(xx, yy) << 1);
                }
                else if (dis[x][y][op].second != dis[xx][yy][0].second && dis[xx][yy][1].first > dis[x][y][op].first + 1) {
                    dis[xx][yy][1] = make_pair(dis[x][y][op].first + 1, dis[x][y][op].second);
                    Q.push(compress(xx, yy) << 1 | 1);
                }
            }
        }
    }
    L(i, 1, N) L(j, 1, M) {
        painted[i][j] = false;
        dis_exits[i][j] = -1;
    }

    int mx = -1;
    L(i, 1, N) L(j, 1, M) {
        if (painted[i][j]) continue;
        if (grid[i][j] == 'e') {
            if (dis[i][j][1].first == inf) paint(i, j);
            else {
                if (dis[i][j][1].first - 1 >= 0) {
                    bfs_layer[dis[i][j][1].first - 1].push_back(compress(i, j));
                    dis_exits[i][j] = dis[i][j][1].first - 1;
                    mx = max(mx, dis[i][j][1].first - 1);
                }
            }
        }
    }

    for (int layer = mx; layer >= 0; layer--) {
        if (bfs_layer[layer].size() == 0) continue;
        for (auto& v : bfs_layer[layer]) {
            auto T = unzip(v);
            int d = layer, x = T.first, y = T.second;
            if (dis_exits[x][y] > d) continue;
            for (int dir = 0; dir < 4; dir++) {
                int xx = x + dx[dir], yy = y + dy[dir];
                if (can_go(xx, yy) && dis_exits[xx][yy] < d - 1) {
                    dis_exits[xx][yy] = d - 1;
                    if (d >= 1) bfs_layer[d - 1].push_back(compress(xx, yy));
                }
            }
        }
    }

    int ans = 0;
    L(i, 1, N) {
        L(j, 1, M) {
            if (painted[i][j]) ans++;
            else if (grid[i][j] == '#' || dis_exits[i][j] == -1) continue;
            else ans++;
        }
    }
    cout << ans << '\n';
}