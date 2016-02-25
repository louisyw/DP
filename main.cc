/*
 *最长递增子序列（LIS）的问题是要找到一个给定序列的最长子序列的长度，使得
 *子序列中的所有元素被排序的顺序增加。
 *采用了两种不同的方法：递归法和动态规划发
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
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

int LIS_DP(int array[], int length){
	int record[length];
	fill(record, record + length, 1);

	for(int i = 0; i < length; i++){
		for(int j = 0; j < i; j++){
			if (array[j] < array[i] && record[j] + 1 > record[i]){
				record[i] = record[j] + 1;
			}
		}
	}

	int max = 1; 
	for(int i = 0; i < length; i++){
		if (record[i] > max)
			max = record[i];
	}

	return max;
}

int main(){
	int a[] = { 10, 22, 9, 33, 21, 50, 41, 60 };
	int n = sizeof(a)/sizeof(int);
	printf("the longest subarray length is %d\n",LIS(a, n));
	printf("the longest subarray length is %d\n",LIS_DP(a, n));
	return 0;
}
