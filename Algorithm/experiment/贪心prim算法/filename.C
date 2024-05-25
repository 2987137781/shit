#include <stdio.h>
#include<stdlib.h>

#define N 6
#define intmax 9999

typedef struct  Graph
{
    /* data */
    int vcount;//顶点数
    int Gtype;//有向还是无向
    char vinfor[N];//顶点的信息
    int arg[N][N];//邻接矩阵
}G;

void prim(G* gprah);
void init(G* gprah, int args[N][N]);
int minIndex(int key[], int mstSet[], int vcount);
void printanser(G* gprah, int key[], int parent[], int vcount);

void prim(G* gprah) {
    //边 集合m 父母
    int key[N] = { 0 }, mstSet[N] = { 0 }, parent[N] = { 0 };
    int u,finally;
    for (int i = 0; i < gprah->vcount; i++) {
        key[i] = gprah->arg[0][i];
        mstSet[i] = 0;
    }
    parent[0] = -1;
    key[0] = 0;
    for (int i = 0; i < gprah->vcount - 1; i++) {
        u = minIndex(key, mstSet, gprah->vcount);
        mstSet[u] = 1;
        printf("%c-", gprah->vinfor[u]);
        for (int v = 0; v < gprah->vcount; v++) {
            if (gprah->arg[u][v] && mstSet[v] == 0 && gprah->arg[u][v] < key[v]) {
                parent[v] = u;
                finally = v;
                key[v] = gprah->arg[u][v];
            }
        }
    }
    printf("%c", finally+'A');
    //printanser(gprah,key, parent, gprah->vcount);
}
//初始化
void init(G* gprah, int args[N][N]) {
    gprah->Gtype = 0;//无向图
    gprah->vcount = N;
    for (int i = 0; i < gprah->vcount; i++) {
        gprah->vinfor[i] = 'A' + i;
        for (int j = 0; j < gprah->vcount; j++) {
            gprah->arg[i][j] = args[i][j];
        }
    }
}
//选最小下标
int minIndex(int key[], int mstSet[], int vcount) {
    int minidex=0, min = intmax;
    for (int i = 0; i < vcount; i++) {
        //不在集合m
        if (mstSet[i] == 0 && key[i] < min) {
            minidex = i;
            min = key[i];
        }
    }
    return minidex;
}

void printanser(G* gprah, int key[], int parent[], int vcount) {
    printf("Edge \tWeight\n");
    // 从 1 开始遍历因为 0 是起点，没有父节点
    for (int i = 1; i < vcount; i++) {
        printf("%c - %c \t%d \n", gprah->vinfor[parent[i]], gprah->vinfor[i], gprah->arg[parent[i]][i]);
    }
}


int main(void)
{
    G* gprah = (G*)malloc(sizeof(struct Graph));
    int args[N][N] = {
        {0,5,6,4,intmax,intmax},
        {5,0,1,2,intmax,intmax},
        {6,1,0,2,5,3,},
        { 4,2,2,0,intmax,4 },
        {intmax,intmax,5,intmax,0,4 },
        {intmax,intmax,3,4,4,0}
    };
    init(gprah, args);
    prim(gprah);
    free(gprah);
    return  0;
}