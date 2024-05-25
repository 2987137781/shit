#include <stdio.h>
void print(int a[] ,int n)
{//输出数组元素，数字之间以一个空格为界，输出结束后换一行
    for(int i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}

void selectSort(int a[] ,int n) //对数组a中的n个元素进行排序，调用print函数输出每趟排序后的结果
{
    int k,temp;
    for(int i=0;i<n-1;i++){
        k=i;
        for(int j=i+1;j<n;j++){
            if(a[j]<a[k]){
                k=j;
            }
        }
        if(k!=i){
            temp=a[k];
            a[k]=a[i];
            a[i]=temp;
        }
        print(a,n);
    }
}


int main(void)
{
  int num;
  scanf("%d",&num);
  int data[num];
  for(int i=0;i<num;i++)
    scanf("%d",&data[i]);
  selectSort(data ,num);
}