#include <stdio.h>
#include <stdlib.h>

#define N 15

int main(){
    // 队伍初始化+编号
    int teams[N] = {0};
    for(int i = 0; i < N; i++){
        teams[i] = i + 1;
    }

    int MatchDay = N; // 比赛天数
    int day = 1;
    printf("比赛日程表：\n");

    // 循环嵌套生成比赛日程表
    for(int d = 0; d < N; d++) {
        printf("day%d:\n", day++);
        for(int i = 0; i < N / 2; i++) {
            printf("第%d场：%d vs %d\n", i + 1, teams[i], teams[N - 1 - i]);
        }
        int temp = teams[N - 1];
        for(int i = N - 1; i > 0; i--){
            teams[i] = teams[i - 1];
        }
        teams[0] = temp;
    }

    return 0;
}
