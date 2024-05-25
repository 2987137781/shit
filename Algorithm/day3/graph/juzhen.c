#include <stdio.h>  
#include <stdlib.h>  
#include <limits.h>  

#define N 6 // 矩阵个数  

int m[N + 1][N + 1]; // 存储最少乘法次数的二维数组  
int s[N + 1][N + 1]; // 存储最佳分割点的二维数组  
int p[] = { 5, 10, 3, 12, 5, 50, 6 }; // 相邻两个数，前一个数是矩阵的行，后一个是矩阵列 

void print1(int i, int j) {// 输出最佳连乘次序
    if (i == j) {
        printf("A%d", i);
    }
    else {
        printf("(");
        print1(i, s[i][j]);
        print1(s[i][j] + 1, j);
        printf(")");
    }
}

void print2(int n) {// 输出最少乘法次数
    printf("最少乘法次数为: %d\n", m[1][n]);
}

    void matrixChainOrder(int n) {
        int i, j, k, q;
        for (i = 1; i <= n; i++) {
            m[i][i] = 0; // 单个矩阵的乘法次数为0  
        }

        for (int l = 2; l <= n; l++) { // l是链长  
            for (i = 1; i <= n - l + 1; i++) {
                j = i + l - 1;
                m[i][j] = INT_MAX; // 初始化为最大整数  
                for (k = i; k <= j - 1; k++) {
                    q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                    if (q < m[i][j]) {
                        m[i][j] = q;
                        s[i][j] = k; // 记录最佳分割点  
                    }
                }
            }
        }
    }
  

int main() {
    int n = N - 1; // 矩阵链长度  
    matrixChainOrder(n);

    print2(n);

    printf("最佳连乘次序为: ");
    print1(1, n);

    printf("\n");

    return 0;
}
