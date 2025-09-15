#include <bits/stdc++.h>
using namespace std;
#define int long long

const int max_hp = 1E9;
const int max_N = 2E5 + 50;
int N, M, K, hp[max_N], arrows_shot[max_N];

bool check(int X) {
    for (int i = 1; i <= N; i++) arrows_shot[i] = 0;
    
    int d = sqrt(M * X);
    int sum_i = 0, sum_i2 = 0, cnt_arrows = 0;
    
    for (int i = 1; i <= N; i++) {
        if (i - d - 1 >= 1) {
            cnt_arrows -= arrows_shot[i - d - 1];
            sum_i -= arrows_shot[i - d - 1] * (i - d - 1);
            sum_i2 -= arrows_shot[i - d - 1] * (i - d - 1) * (i - d - 1);
        }
        
        int dmg = M * X * cnt_arrows - 1LL * i * i * cnt_arrows + 2LL * sum_i * i  - sum_i2;
        int remaining_hp = hp[i] - dmg;
        if (remaining_hp > 0) {
            int arrows_needed = (remaining_hp + M * X - 1) / (M * X);

            arrows_shot[i] = arrows_needed;
            cnt_arrows += arrows_needed;
            sum_i += arrows_needed * i;
            sum_i2 += arrows_needed * i * i;
        }
    }

    int total_arrows_shot = 0;
    for (int i = 1; i <= N; i++) total_arrows_shot += arrows_shot[i];
 
    return total_arrows_shot <= K;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
     
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) 
        cin >> hp[i];
    
    int lo = 1, hi = max_hp + 1LL * N * N, ans = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) {
            ans = mid;
            hi = mid - 1;
        }
        else lo = mid + 1;
    }
    cout << ans << '\n';
    return 0;
}