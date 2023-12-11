#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

#define NUM 110000
#define limit 100

using namespace std;


int mmax;
//蛮力法，递归
int bruteForce(vector<int> &nums,int start,int end,vector<vector<int>> &s){
    if(start==end){
        return  nums[start] ;
    }
    int scoreStart=nums[start]-bruteForce(nums,start+1,end,s);
    int scoreEnd=nums[end]-bruteForce(nums,start,end-1,s);
    if(scoreStart>=scoreEnd) {
        s[start][end] = start;
        mmax =scoreStart;
        return mmax;
    }else if(scoreStart<scoreEnd) {
        s[start][end] = end;
        mmax =scoreEnd;
        return mmax;
    }
}

int bruteForce1(vector<int> &nums,int start,int end,int turn){
    if(start==end){
        return  nums[start] * turn;
    }
    int scoreStart=nums[start]*turn+bruteForce1(nums,start+1,end,-turn);
    int scoreEnd=nums[end]*turn+bruteForce1(nums,start,end-1,-turn);//每一轮循环turn要取反，表示下一轮为另一个玩家
    if(turn==1){//玩家A
        return max(scoreStart,scoreEnd);
    }else{
        return min(scoreStart,scoreEnd);
    }
}

//二维dp
int normalDP(vector<int> &nums,vector<vector<int>> &s){
    int n=nums.size();
    auto dp=vector<vector<int>>(n, vector<int>(n));
    for(int i=0;i<n;i++){
        dp[i][i]=nums[i];
    }
    for(int i=n-2;i>=0;i--){//自底向上
        for(int j=i+1;j<n;j++){
            dp[i][j]=max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
            s[i][j]=nums[i] - dp[i + 1][j]>=nums[j] - dp[i][j - 1]? i:j;
        }
    }
    return dp[0][n-1];
}
//优化：一维dp
int improvedDP(vector<int>& nums,vector<vector<int>> &s) {
    int length = nums.size();
    auto dp = vector<int>(length);
    for (int i = 0; i < length; i++) {
        dp[i] = nums[i];
    }
    for (int i = length - 2; i >= 0; i--) {
        for (int j = i+1 ; j < length; j++) {
            dp[j] = max(nums[i] - dp[j], nums[j] - dp[j - 1]);
            s[i][j]=nums[i] - dp[j]>nums[j] - dp[j - 1]? i:j;
        }
    }
    return dp[nums.size() - 1];
}
//优化：博弈论优化+一维dp
int improvedDP2(vector<int>& nums,vector<vector<int>> &s) {
    if(nums.size()&1==0) {
        int sum=0;
        for(int i=0;i<nums.size();i+=2){
            sum+=nums[i]-nums[i+1];
        }
        return sum>0? sum:-sum;
    }
    int length = nums.size();
    auto dp = vector<int>(length);
    for (int i = 0; i < length; i++) {
        dp[i] = nums[i];
    }
    for (int i = length - 2; i >= 0; i--) {
        for (int j = i+1 ; j < length; j++) {
            dp[j] = max(nums[i] - dp[j], nums[j] - dp[j - 1]);
         //   s[i][j]=nums[i] - dp[j]>nums[j] - dp[j - 1]? i:j;
        }
    }
    return dp[nums.size() - 1];
}

int memorized(vector<int> &nums,int n,vector<vector<int>> &s){
    n=nums.size();
    for(int i=0;i<n;i++) {
        s[i][i]=i;
    }
    return bruteForce(nums,0,n-1,s);
}

void print(vector<vector<int>> &s,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout<<s[i][j]<<" ";
        cout<<endl;
    }
}

int main(){
   // vector<int> nums={6,1,4,9,8,5};
    //vector<int> nums={4,6,2,3};
    int n=NUM;
    vector<int> nums(n);
    for(int i=0;i<n;i++){
        nums[i]=rand()%limit;
    }
//    for(int i=0;i<n;i++){
//        cout<<nums[i]<<" ";
//    }
    cout<<endl;

    vector<vector<int>> s(nums.size(),vector<int>(nums.size()));
    double t,t1,t2,t3,t4;

    clock_t start, end;

//    start=clock();
//    int ans=bruteForce1(nums,0,nums.size()-1,1);
//    end=clock();
//    t=double(end-start);
//    cout<<"蛮力法："<<ans<<endl; //得到A与B的最大金币差值
//    cout<<"Time:"<<t<<endl;
//    cout<<endl;

//    start=clock();
//    int ans1=memorized(nums,nums.size(),s);
//    end=clock();
//    t1=double(end-start);
//    cout<<"记忆化搜索蛮力法："<<ans1<<endl;
//    print(s,nums.size());
//    cout<<"Time:"<<t1<<endl;
//    cout<<endl;

//    start=clock();
//    int ans2= normalDP(nums,s);
//    end=clock();
//    t2=double(end-start);
//    cout<<"优化前dp："<<ans2<<endl;
//   // print(s,nums.size());
//    cout<<"Time:"<<t2<<endl;
//    cout<<endl;

//    start=clock();
//    int ans3=improvedDP(nums,s);
//    end=clock();
//    t3=double(end-start);
//    cout<<"优化后dp："<<ans3<<endl;
//   // print(s,nums.size());
//    cout<<"Time:"<<t3<<endl;
//    cout<<endl;

    start=clock();
    int ans4= improvedDP2(nums,s);
    end=clock();
    t4=double(end-start);
    cout<<"博弈优化后的dp："<<ans4<<endl;
   // print(s,nums.size());
    cout<<"Time:"<<t4<<endl;
    cout<<endl;


}