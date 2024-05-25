#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define n1 10
#define n2 20

void merge(int arr[],int reg[],int start,int mid,int end){
    int start1=start,start2=mid+1;
    int end1=mid,end2=end;
    int k=start;
    //合并
    while(start1<=end1&&start2<=end2){
        reg[k++]=arr[start1]<arr[start2]?arr[start1++]:arr[start2++];
    }
    while(start1<=end1){
        reg[k++]=arr[start1++];
    }
    while(start2<=end2){
        reg[k++]=arr[start2++];
    }
    //辅助数组赋值原数组
    for(k=start;k<=end;k++){
        arr[k]=reg[k];
    }
}

void merge_sort(int arr[], int reg[], int start, int end) {
    //递归结束条件
    if(start>=end){
        return;
    }
    //中间值
    int mid=(start+end)/2;
    //递归 先分治到足够小再排序
    merge_sort(arr,reg,start,mid);
    merge_sort(arr,reg,mid+1,end);
    merge(arr,reg,start,mid,end);
}

int binarySeach(int arr[],int n,int targe){
    int left=0,right=n-1;
    int mid=(left+right)/2;
    while(left<=right){
        if(arr[mid]==targe){
            return mid+1;
        }
        else if(arr[mid]<targe){
            left=mid+1;
        }
        else{
            right=mid-1;
        }
        mid=(right+left)/2;
    }
}

int main(){
    //
    int a[n1],reg[n1];
    for (int i = 0; i < n1; i++) {
	    scanf("%d", &a[i]);
    }
    int findnum = 0;
    scanf("%d", &findnum);
    merge_sort(a,reg,0,n1-1);
    for (int i = 0; i < n1; i++) {
	    printf("%d ", a[i]);
    }
    printf("\n%d",binarySeach(a,sizeof(a)/sizeof(a[0]),findnum));
    return 0;
}