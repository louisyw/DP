#include <cstdio>

using namespace std;
const int SIZE = 11;

int p[SIZE]={0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};    //不同长度对应的不同的价格

//自顶向下递归实现
int cut-rod(int p[], int n){
	if (n == 0)
		return 0;
	int q = -1;
	for(int i = 1; i <= n; i++){
		q = max(q, p[1] + cut-rod(int p, n -i));
	}
	return q;
}


//备忘录法
int memoized-cut-rod(int p[], int n){
	int r[n];
	for (int i = 0; i <= n; i++){
		r[n] = -1;
	}
	return memoized-cut-rod-aux(p, n, r);
}

int memoized-cut-rod-aux(int p[], int n, int r){
	if (r[n] >= 0)
		return r[n];
	if (n == 0)
		return 0;
	else{
		q= -1;
		for (int i = 0; i < n; i++){
			q = max(q, p[i] + memoized-cut-rod-aux(p, n-i, r));
			r[n] = q;
		}
	}
}

//自底向上的DP算法
int bottom-up-cut-rod(int p[], int n){
	int dp[n+1];    //
	dp[0] = 0;

	for(int i= 1; i <= n; i++){
		int q = -1;
		for(int j = 1; j < i; j++){
			q = max(q, p[j] + dp[i - j]);
		}
		dp[i] = q;
	}
}
