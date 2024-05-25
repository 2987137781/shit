#include<stdio.h>
void quick(int arr[],int low,int high);
int quicksort(int arr[],int low,int high);
int quicksort(int arr[],int low,int high){
    int k=arr[low];//体育委员
    int i=low,j=high;
    while(i<j){
        //从右向左找到k小的第一个数
        while(i<j&&arr[j]>=k){
            j--;
        }
        if(i<j){
            arr[i]=arr[j];
            i++;
        }
        //从左向右找到k大的第一个数
        while(i<j&&arr[i]<=k){
            i++;
        }
        if(i<j){
            arr[j]=arr[i];
            j--;
        }
    }
    //i==j 体育委员的位置
    arr[i]=k;
    return i;
}
void quick(int arr[],int low,int high){
    if(low<high){
        int k=quicksort(arr,low,high);
        quick(arr,low,k-1);
        quick(arr,k+1,high);
    }
}

int main(){
    int arr[]={10,7,8,9,1,5};
    int n=sizeof(arr)/sizeof(arr[0]);
    quick(arr,0,n-1);
    int i=0;
    while(i<n){
        printf("%d ",arr[i]);
        i++;
    }
}