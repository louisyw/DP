/*
 *matrix chain order
 *author:louisyw
 */

#include <cstdio>
#include <limits.h>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

/**/
typedef pair<int , int> P;     //row, col

const int MAX_N= 100;
int m[MAX_N][MAX_N];      //cost
int s[MAX_N][MAX_N];     //split point

void matrix_chain_order(vector<P> matrix_chain){
	
	int n = matrix_chain.size();
	
	for(int i = 0; i < n; i++){
		m[i][i] = 0;
	}
	

	for(int l = 2; l <= n; l++){             //chain length
		for (int i = 0; i < n - l + 1; i++){
			int j = i + l - 1;
			m[i][j] = INT_MAX;

			for(int k = i; k <=j; k++){
				int q = INT_MAX;

				q = m[i][k] + m[k+1][j] + matrix_chain.at(i).first * matrix_chain.at(k).second * matrix_chain.at(j).second;

				if (q < m[i][j]){
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
		
	}
}


void print_optimal_parents(int i, int j){
	if (i == j)
		printf("A%d", i);
	else{
		printf("(");
		print_optimal_parents(i, s[i][j]);
		print_optimal_parents(s[i][j] + 1, j);
		printf(")");

	}
}

int main(){
	vector<P> ma;
	ma.push_back(P(30, 35));
	ma.push_back(P(35, 15));
	ma.push_back(P(15, 5));
	ma.push_back(P(5, 10));
	ma.push_back(P(10, 20));
	ma.push_back(P(20, 25));

	matrix_chain_order(ma);
	
	int ret = m[0][ma.size() -1];

	printf("%d\n", ret);
	print_optimal_parents(0, ma.size() -1);
	printf("\n");
	return 0;
}
