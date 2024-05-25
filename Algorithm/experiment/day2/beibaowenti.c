/*
本关任务：给定N个物品和一个背包，背包的容量为W， 假设背包容量范围在[0，15]，第i个物品对应的体积和价值分别为W[i]和v[i]。各种物品的价值和重量如下：
     物品编号   1   2   3   4   5
      重量W    3   4   7   8   9
      价值V    4   5   10  11  13
求: 如何选择装入背包的物品，使得装入背包的物品的总价值为最大。

*/
#include <stdio.h>

#define N 5
#define W 15
//返回两个数中的最大值
int max(int a,int b){
    return a>b?a:b;
}

int main( void )
{
    //输入和初始化
    int w[N+1]={0,3,4,7,8,9},v[N+1]={0,4,5,10,11,13};
    int anser[N+1][W+1]={0};//用于存放结果的表格
    /*
    for(int i=1;i<N+1;i++){
        scanf("%d%d",&w[i],&v[i]);
    }
    */
    //
    for(int i=1;i<N+1;i++){
        for(int j=0;j<W+1;j++){
            if(w[i]>j){
                anser[i][j]=0;
            }
            else{
                anser[i][j]=max(anser[i-1][j-w[i]]+v[i],anser[i-1][j]);
            }
        }
    }
    for(int i=1;i<N+1;i++){
        for(int j=0;j<W+1;j++){
            if(j==0 && i==1){
                printf("w v");
            }
            else{
                printf("%d %d",w[i],v[i]);
            }
            printf("%d ",anser[i][j]);
        }
        printf("\n");
    }

    return  0;
}
