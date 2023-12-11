#include <iostream>
#include <stack>
#include <vector>
int Partition(int *pInt, int left, int right);

using namespace std;

void selectSort(vector<int>&num, int n) {
    int i, j, k, temp;
    for (i = 0; i < n; i++) {
        k = i;                    // k位置的值为当前的最小值
        for (j = i + 1; j < n; j++) {        // 找出最小值的位置
            if (num[k] > num[j]) k = j;
        }
        //若k!=i，则k位置与i位置的数据进行交换
        if (k != i) {
            temp = num[k];
            num[k] = num[i];
            num[i] = temp;
        }
    }
}

void bubbleSort1(vector<int>&num, int n) {
    int i, j, temp;
    for (i = 0; i < n; i++) {
        for (j = 1; j < n - i; j++) {
            if (num[j] < num[j - 1]) {
                temp = num[j - 1];
                num[j - 1] = num[j];
                num[j] = temp;

            }
        }
    }
}
//设置标记位flag的冒泡排序
void bubbleSort2(vector<int>&num, int n) {
    int i, j, temp;
    bool flag = true;
    for (i = 0; i < n &&flag; i++) {
        flag = false;
        for (j = 1; j < n - i; j++) {
            if (num[j] < num[j - 1]) {
                temp = num[j - 1];
                num[j - 1] = num[j];
                num[j] = temp;
                flag = true;
            }
        }
    }
}
//同时确定最大最小值的冒泡
void bubbleSort3(vector<int>&arr, int len)
{
    int i = 0;
    int j = 0;
    int n = 0;//同时找最大值的最小需要两个下标遍历
    int flag = 0;
    int pos = 0;//用来记录最后一次交换的位置
    int k = len - 1;
    for (i = 0; i < len - 1; i++)//确定排序趟数
    {
        pos = 0;
        flag = 0;
        //正向寻找最大值
        for (j = n; j < k; j++)//确定比较次数
        {
            if (arr[j]>arr[j + 1])
            {
                //交换
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                flag = 1;//加入标记
                pos = j;//交换元素，记录最后一次交换的位置
            }
        }
        if (flag == 0)//如果没有交换过元素，则已经有序,直接结束
        {
            return;
        }
        k = pos;//下一次比较到记录位置即可
        //反向寻找最小值
        for (j = k; j > n; j--)
        {
            int tmp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = tmp;
            flag = 1;
        }
        n++;
        if (flag == 0)//如果没有交换过元素，则已经有序,直接结束
        {
            return;
        }
    }
}

void Merge(vector<int> &num, int *Data, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {  //两两比较将较小的并入
        if (num[i] <= num[j]) Data[k++] = num[i++];
        else Data[k++] = num[j++];
    }
    while (i <= mid) { Data[k++] = num[i++]; }//将mid前剩余的并入
    while (j <= right) { Data[k++] = num[j++]; }//将mid后剩余的并入
}

void mergeSort(vector<int>&num, int n) {
    int *Data = new int[n];
    int left, mid, right, step;
    for (step = 1; step < n; step *= 2) {//step表示每个子序列的长度
        for (left = 0; left < n; left += 2 * step) {
            mid = left + step - 1;   //left指向第一个序列的第一个元素
            if (mid >= n - 1) break;   //mid指向第一个序列的最后元素
            right = left + 2 * step - 1;//right指向第二个序列的最后元素
            if (right > n - 1) right = n - 1;
            Merge(num, Data, left, mid, right);
        }
        for (int t = 0; t < n; t++) num[t] = Data[t];//保留一趟排序后的结果
    }
}



void quickSort(vector<int> &Key, int low, int high) {
    int i, j, Pivotkey;
    i = low;	j = high;	//记录顺序表的上、下界
    Pivotkey = Key[low];       //PrivotKey记录枢轴记录
    while(low <high) {		//当high>low的时候循环
        while((low < high) && (Key[high] >= Pivotkey))high--;
        if(low < high) {Key[low] = Key[high];  low++;} else break;
        while((low < high) && (Key[low]<= Pivotkey))    low++;
        if(low < high) {Key[high] = Key[low];  high--;}}
    Key[low] = Pivotkey;		 // low == high
    if (i<low-1)  quickSort(Key,i, low-1); //对子对象数组进行递归快速排序
    if (high+1<j) quickSort(Key,high+1, j);
}

void insertSort(vector<int>&num, int n) {
    {
        int i, j, temp;
        for (i = 1; i < n; i++) {         //从第2个元素开始插入排序
            temp = num[i];
            for (j = i - 1; j >= 0; j--) {
                if (temp < num[j]) num[j + 1] = num[j];
                else break;        //找到新元素位置，退出循环
            }
            num[j + 1] = temp;
        }
    }

}

void print(int *num, int n) {
    for (int i = 0; i < n; i++)
        cout << num[i] << " ";
    cout << endl;
}

int main() {
    //测试数据
    //int num[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
    //默认升序
    //int n = sizeof(num) / sizeof(num[0]);
    //selectSort(num,10);
    //bubbleSort(num,10);
    //mergeSort(num,10);
    //quickSort(num,0,n-1);
    //insertSort(num,10);
    //print(num, n);
#define sample 20//20个测试样本
#define batch 10000000 //依次为10000，20000，30000，40000，50000

    double t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0,t7=0;

    for(int t=1;t<=sample;t++) {
       // cout << "这是第" << t << "组测试样本：" << endl;
       //cout<<t<<endl;
        int n = batch, limit = 999999;
        // vector<int> v(n), v1;
        vector<int> num2(n),num3;
        //int num[n];
        for (int i = 0; i < n; i++) num2[i] = rand() % limit;
        //for(int i=0; i<n; i++) v[i]=n-i;

        clock_t startTime, endTime;

         //select
        num3=num2;
        startTime = clock();
        selectSort(num3,n);
        endTime = clock();
        t1 += (double) (endTime - startTime) / CLOCKS_PER_SEC;
        cout<<t1<<endl;
        // bubble_sort 1
        num3=num2;
        startTime = clock();
        bubbleSort1(num3,n);
        endTime = clock();
        t2 += (double) (endTime - startTime) / CLOCKS_PER_SEC;
        cout<<t2<<endl;

        // bubble_sort 2
        num3=num2;
        startTime = clock();
        bubbleSort2(num3, n);
        endTime = clock();
        t3 += (double) (endTime - startTime) / CLOCKS_PER_SEC;
          cout<<t3<<endl;
        // bubble_sort 3
        num3=num2;
        startTime = clock();
        bubbleSort3(num3, n);
        endTime = clock();
        t3 += (double) (endTime - startTime) / CLOCKS_PER_SEC;
        cout<<t4<<endl;
        // insert_sort
        num3=num2;
        startTime = clock();
        insertSort(num2,n);
        endTime = clock();
        t4 += (double) (endTime - startTime) / CLOCKS_PER_SEC;
          cout<<t5<<endl;

       //  merge_sort
        num3=num2;
        startTime = clock();
        mergeSort(num3,n);
        endTime = clock();
        t5 += (double) (endTime - startTime) / CLOCKS_PER_SEC;
          cout<<t<<": "<<t6<<endl;

        // quick_sort
        num3=num2;
        startTime = clock();
        quickSort(num3, 0, n- 1);
        endTime = clock();
        t6 += (double) (endTime - startTime)/ CLOCKS_PER_SEC; ;
          cout<<t<<": "<<t7<<endl;
    }

    cout << t1 / sample << endl;
    cout <<"bubblesort: "<< t2 / sample << endl;
    cout << t3 / sample << endl;
    cout << t4 / sample << endl;
    cout << t5 / sample << endl;
    cout <<"mergesort: "<< t6 / sample << endl;
   cout << "quicksort: "<<t7 / sample << endl;

    return 0;
}


