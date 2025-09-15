#include<bits/stdc++.h>
using namespace std;
int main() {
	int N, K; cin >> N >> K;  //read the first two integers N and K
	K = min(K, N); //you actually need at most N blue rectangles

	vector<int> h(N + 1), w(N + 1);
	for (int i = 1; i <= N; i++)  cin >> h[i] >> w[i]; 
	//dp[i][j]=minimum area to cover i rectangles using j blue rectangles
	vector<vector<int>> dp(N + 1, vector<int>(K + 1, 1E9)); //initialise all states to be inf
	dp[0][0] = 0; //define initial state
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j < K; j++) {
			int mx = 0, sum = 0; //initialise the sum of width to 0 and max height to be 0
			for (int t = i + 1; t <= N; t++) { //t is the next index that you are going to cover until
				mx = max(mx, h[t]); //update the max height
				sum += w[t]; //update the sum of width
				dp[t][j + 1] = min(dp[t][j + 1], dp[i][j] + mx * sum); //setting minimum
			}
		}
	}
	cout << dp[N][K] << '\n'; //print final answer
}

