#include <iostream>
#include <queue>
using namespace std;

//STL的sort()降序排序
void mySort1(vector<int>& nums, int n) {
    sort(nums.begin(), nums.end(), greater<int>());

}

//快速排序
void mySort2(vector<int>& Key, int low, int high) {
    int i, j, Pivotkey;
    i = low;
    j = high;    //记录顺序表的上、下界
    Pivotkey = Key[low];       //PrivotKey记录枢轴记录
    while (low < high) {        //当high>low的时候循环
        while ((low < high) && (Key[high] <= Pivotkey))high--;
        if (low < high) {
            Key[low] = Key[high];
            low++;
        } else break;
        while ((low < high) && (Key[low] >= Pivotkey)) low++;
        if (low < high) {
            Key[high] = Key[low];
            high--;
        }
    }
    Key[low] = Pivotkey;         // low == high
    if (i < low - 1) mySort2(Key, i, low - 1); //对子对象数组进行递归快速排序
    if (high + 1 < j) mySort2(Key, high + 1, j);
}

//10轮冒泡，将最大的十个数冒泡到数列尾。
void mySort3(vector<int>& nums, int n) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < n - 1 - i; j++)
            if (nums[j] > nums[j + 1]) {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
    }
}
//堆调整 小顶堆
void mySort4(vector<int>& nums,int n,int k,priority_queue<int, vector<int>, greater<int> > &q)
{
    for(int i=0; i<n; i++)
    {
        if(q.size()<k) q.push(nums[i]);
        else if(q.top()<nums[i]){
            q.pop();
            q.push(nums[i]);
        }
    }
}

//堆排序 建大顶堆，输出前10个
void shift(vector<int>&data,int k,int m){
    int i,j;
    i=k;
    j=2*i;
    while(j<=m){
        if(j<m && data[j]<data[j+1])//比较i的左右两个孩子谁大，j指向较大的孩子
            j++;
        if(data[i]>=data[j])
            break;
        else{
            int temp=data[i];
            data[i]=data[j];
            data[j]=temp;
            i=j;
            j=2*i;
        }
    }
}
void init(vector<int>&data,int len){    //初始化堆
    for(int i=(len-1)/2;i>=0;i--)
        shift(data,i,len-1);
}
void HeapSort(vector<int>&data,int len,int k){
    init(data,len);
    for(int i=len-1;i>len-1-k;i--){  ///共进行10(k)次，同时输出前10(k)个
        int temp=data[0];    //将第1个元素和第i个元素的值进行交换
        data[0]=data[i];
        data[i]=temp;
        //cout<<data[i]<<endl;
        shift(data,0,i-1);  //调整堆，注意已经排完的i号元素不再参加
        // print();
    }
}
//输出前k个数
void print(vector<int> &nums, int k) {
    for (int i = 0; i <k ; i++)
        cout << nums[i] << " ";
    cout << endl;
}
void print1(vector<int> &nums,int n,int k){
    for(int i=n-k;i<n;i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;
}
void print2(priority_queue<int, vector<int>, greater<int> > &q){
    while(!q.empty()){
        cout<<q.top()<<" ";
        q.pop();
    }
}
int main() {
    //测试数据
   // int nums[20]={0,2,4,6,8,10,1,3,5,7,9,12,14,16,18,11,13,15,17,19};
    //mySort1(nums,20);
    //mySort2(nums,0,19);
    //mySort3(nums,20);
    //mySort4(nums,20,10,q);
    //print(nums,10);
    //print1(nums,20,10);
    //print2(q);
    priority_queue<int, vector<int>, greater<int> > q;
#define sample 20
#define batch 3000000
    int t = sample;
    double t1=0, t2=0, t3=0, t4=0, t5=0;
    int n=batch, limit=99999;
    clock_t startTime, endTime;
    while(t--)
    {
        cout<<t<<endl;
        vector<int> nums(n),num1;
        for(int i=0; i<n; i++) nums[i]=rand()%limit;

        // 1
        num1=nums;
        startTime = clock();
        mySort1(num1,n);
        endTime = clock();
        t1 += (double)(endTime - startTime) / CLOCKS_PER_SEC;

        // 2
        num1=nums;
        startTime = clock();
        mySort2(num1,0,n-1);
        endTime = clock();
        t2 += (double)(endTime - startTime) / CLOCKS_PER_SEC;

        // 3
        num1=nums;
        startTime = clock();
        mySort3(num1,n);
        endTime = clock();
        t3 += (double)(endTime - startTime) / CLOCKS_PER_SEC;

        //4
        num1=nums;
        startTime = clock();
        mySort4(num1,n,1000000,q);
        endTime = clock();
        t4 += (double)(endTime - startTime) / CLOCKS_PER_SEC;

        //5
        num1=nums;
        startTime = clock();
        HeapSort(num1,n,1000000);
        endTime = clock();
        t5 += (double)(endTime - startTime) / CLOCKS_PER_SEC;
    }

    cout<<"sort1: "<<t1/sample<<endl;
    cout<<"sort2: "<<t2/sample<<endl;
    cout<<"sort3: "<<t3/sample<<endl;
    cout<<"sort4: "<<t4/sample<<endl;
    cout<<"sort5: "<<t5/sample<<endl;

    return 0;
}

