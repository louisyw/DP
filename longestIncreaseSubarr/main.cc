/*
 *最长递增子序列（LIS）的问题是要找到一个给定序列的最长子序列的长度，使得
 *子序列中的所有元素被排序的顺序增加。
 *采用了两种不同的方法：递归法和动态规划发
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

/*递归法*/
int _LIS(int array[], int length, int *max){

	int res = 0;
	int max_ending_here = 1;

	if (length == 1) return 1;

	for(int i = 0; i < length - 1; i++){
		res = _LIS(array, i, max);
		if (array[i] < array[length-1] && res + 1 > max_ending_here){
			max_ending_here = res + 1;
		}

		if (*max < max_ending_here)
			*max = max_ending_here;
	}
	return max_ending_here;
}

/*wrapper of _LIS*/
int LIS(int array[], int length){
	int max = 1;

	_LIS(array, length, &max);

	return max;
}

//dynalic programming
void print_LIS(int array[], int index, int lis, int dp[]);

int LIS_DP(int array[], int length){
	int record[length];
	fill(record, record + length, 1);
	int max = 1; 
	
	for(int i = 0; i < length; i++){
		for(int j = 0; j < i; j++){
			if (array[j] < array[i] && record[j] + 1 > record[i]){
				record[i] = record[j] + 1;
			}
		}
		if (record[i] > max)
			max = record[i];
	}
	print_LIS(array, length -1, max, record);
	return max;
}

void print_LIS(int array[], int index, int lis, int dp[]){
	bool isLIS = 0;
	if(index < 0 || lis == 0)
		return;
	if(dp[index] == lis){
		--lis;
		isLIS = 1;
	}
							 
	print_LIS(array,--index, lis, dp);
							      
	if(isLIS){
		printf("the %d in LIS is %d\n",lis+1, array[index+1]);
	}
}

/*sort + LCS*/
const int MAX_N= 1000;
int dp[MAX_N][MAX_N];

void qsort(int *array, int left, int right){
	if (left >= right) return;

	int index = left;

	for(int i = left +1; i <= right; ++i){
		if (array[i] < array[left])
			swap(array[i], array[++index]);
	}
	swap(array[left], array[index]);
	qsort(array, left, index-1);
	qsort(array, index + 1, right);
}

int LCS(int *arr, int len1, int *sort_arr, int len2){
	/*全局变量，没有必要初始化*/
	for (int i = 0; i < len1; ++i){
		dp[i][0]  = 0;
	}
	for (int i = 0 ; i < len2; ++i){
		dp[0][i] = 0;
	}

	for(int i = 1; i <= len1; ++i){
		for(int j = 1; j <= len2; ++j){
			if (arr[i - 1 ] == sort_arr[j - 1]){
				dp[i][j] = dp[i-1][j-1] + 1;
			}
			else{
				dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
			}
		}
	}

	return dp[len1][len2];
}


/*end[i]记录长度为i的递增自序列的最小元素*/

/*arr为有序序列，判断在arr中大于等于val的最小下标*/
int upper_bound(int *arr, int length, int val){

	int left = 1, right = length;

	if (arr[right] < val)
		return right+1;

	//while(left < right)   //此处注意循环终止的条件
	while(right - left > 1){
		
		int mid = (left + right)/2;
		if (arr[mid] >= val)
			right = mid;
		else 
			left = mid;
	}
	return right;
}

int LIS2(int *arr, int length){
	
	int end[length + 1];   //end[0]不用

	end[1] = arr[0];

	int len = 1;
	for(int i = 1; i < length; i++){
		int index = upper_bound(end, len, arr[i]);
		end[index] = arr[i];

		if(len < index)
			len = index;
	}
	return len;
}


int main(){
	int a[] = { 10, 22, 9, 33, 21, 50, 41, 60 };
	int n = sizeof(a)/sizeof(int);

	printf("using the last record:\n");
	printf("the longest subarray length is %d\n", LIS2(a, n));
	int sort[n];
	memcpy(sort, a ,sizeof(a));
	qsort(sort, 0, n - 1);

	printf("using sort and LCS:\n");
	printf("the longest subarray length is %d\n",LCS(a, n, sort, n));
	printf("using recursice:\n");
	printf("the longest subarray length is %d\n",LIS(a, n));
	printf("using DP:\n");
	printf("the longest subarray length is %d\n",LIS_DP(a, n));
	return 0;
}
