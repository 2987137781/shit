#include<stdio.h>
#include <stdlib.h>
#define int_max 100000000
int min_step(int target,int n);
int g(int x);
int f(int x);
int g(int x){
    return x/2;
}
int f(int x){
    return 3*x;
}
//分治界限
int min_step(int target,int n){
    //评估
    if(target>n){
        printf("f");
        return min_step(target,f(n))+1;
    }
    else if(target<n){
        printf("g");
        return min_step(target,g(n))+1;
    }
    else{
        return 0;
    }
}
int main(){
    int n,target;
    scanf("%d%d",&n,&target);
    int count=min_step(target,n);
    printf("\nstep:%d",count);
    return 0;
}