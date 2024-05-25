#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main(){
    int n;//比赛次数or一方马数
    while(cin>>n&&n!=0){
        vector<int> tian(n),king(n);
        //输入
        for(int i=0;i<n;i++){
            cin>>tian[i];
        }
        for(int i=0;i<n;i++){
            cin>>king[i];
        }
        //排序
        sort(tian.begin(),tian.end());
        sort(king.begin(),king.end());
        int MaxMoney=0,index=0;
        for(int i=0;i<n;i++){
            while(index<n&&tian[index]<=king[i]){
                index++;
            }
            if(index<n){
                MaxMoney+=200;
                index++;
            }
        }
        cout<<MaxMoney<<endl;
    }
    return 0;
}