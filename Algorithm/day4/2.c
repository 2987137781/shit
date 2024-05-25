#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_INT 999999 // 定义一个表示无穷大的常量
#define N 10 // 数组长度

int minimum(int a, int b) {
    return a < b ? a : b;
}

bool isValidOperation(int a, int b, char op) {
    if (op == '/' && b == 0) return false; // 除法时除数不能为0
    if (op == '-' && a < b) return false; // 减法时结果不能为负数
    return true;
}

int calculate(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            return 0; // 默认返回值
    }
}

void minOperations(int nums[], int n, int m) {
    int dp[N][N]; // 定义动态规划数组，表示前i个数能否通过运算得到j

    // 初始化dp数组
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = MAX_INT; // 初始化为无穷大
        }
    }

    // 第一个数可以直接得到，其它数需要通过运算得到
    dp[1][nums[0]] = 0;

    // 动态规划求解
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // 如果当前数等于目标整数，则操作次数为0
            if (nums[i - 1] == j) {
                dp[i][j] = 0;
            } else {
                for (int k = 1; k < i; k++) {
                    for (char op = '+'; op <= '/'; op++) {
                        if (isValidOperation(nums[k - 1], nums[i - 1], op)) {
                            int temp = calculate(nums[k - 1], nums[i - 1], op);
                            dp[i][temp] = minimum(dp[i][temp], dp[k][nums[k - 1]] + dp[i - k][nums[i - 1]] + 1);
                        }
                    }
                }
            }
        }
    }

    // 输出最少操作次数和对应表达式
    if (dp[n][m] == MAX_INT) {
        printf("无法得到目标整数\n");
    } else {
        printf("最少操作次数为：%d\n", dp[n][m]);

        // 输出对应的表达式
        printf("表达式为：");
        int remain = m;
        for (int i = n; i > 0; i--) {
            for (char op = '+'; op <= '/'; op++) {
                if (isValidOperation(nums[i - 1], remain, op) && dp[i][remain] == dp[i - 1][remain - nums[i - 1]] + 1) {
                    printf("(%d %c %d) ", nums[i - 1], op, remain);
                    remain -= nums[i - 1];
                    break;
                }
            }
        }
        printf("= %d\n", m);
    }
}

int main() {
    int nums[N] = {2, 3, 5}; // 给定整数数组
    int m = 25; // 目标整数m

    minOperations(nums, N, m); // 调用函数计算最少操作次数

    return 0;
}
