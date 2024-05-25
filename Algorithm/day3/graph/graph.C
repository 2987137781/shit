#include <stdio.h>
#include <limits.h>

#define N 10
#define MAX_WEIGHT INT_MAX
#define M 18
//结果邻接矩阵
int arc[N][N];
//点 边数 边
void CreateGraph(int vnum, int arcnum, int edges[][3]) {
    int i, j, weight;
    for (i = 0; i < vnum; i++)
        for (j = 0; j < vnum; j++)
            arc[i][j] = 0;
    //初始化
    for (i = 0; i < arcnum; i++) {
        int start = edges[i][0];
        int end = edges[i][1];
        weight = edges[i][2];
        arc[start][end] = weight;
    }
}

int BackPath(int n) {
    int i, j;
    int cost[N], path[N];
    for (i = 1; i < n; i++)
    {
        cost[i] = MAX_WEIGHT;
        path[i] = -1;
    }
    cost[0] = 0;
    path[0] = -1;

    for (j = 1; j < n; j++)
    {
        for (i = j - 1; i >= 0; i--)
        {
            if (arc[i][j] + cost[i] < cost[j]&&arc[i][j]!=0)
            {
                cost[j] = arc[i][j] + cost[i];
                path[j] = i;
            }
        }
    }

    printf("%d", n - 1);
    i = n - 1;
    while (path[i] >= 0)
    {
        printf("<-%d", path[i]);
        i = path[i];
    }
    return cost[n - 1];
}

int main() {
    int vnum = N; // 顶点个数
    int arcnum = M; // 边的个数
    int edges[M][3] = {
        //1
        {0, 1, 4},
        {0, 2, 2},
        {0, 3, 3},
        //2 3 4
        {1, 4, 10},
        {1, 5, 9},
        {2, 4, 6},
        {2, 5, 7},
        {2, 6, 10},
        {3, 5, 3},
        {3, 6, 8},
        //567
        {4, 7, 4},
        {4, 8, 8},
        {5, 7, 9},
        {5, 8, 6},
        {6, 7, 5},
        {6, 8, 4},
        //89
        {7, 9, 8},
        {8, 9, 4},
    };

    CreateGraph(vnum, arcnum, edges);
    
    /*  测试图
    for (int i = 0; i < vnum; i++) {
        for (int j = 0; j < vnum; j++)
            printf("%d\t", arc[i][j]);
        printf("\n");
    }
    */
    
    int shortest = BackPath(vnum);
    printf("\nShortest path length: %d\n", shortest);

    return 0;
}
