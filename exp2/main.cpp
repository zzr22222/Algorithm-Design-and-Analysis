#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <random>
#include <unordered_set>
#include <algorithm>
#include  <cstddef>
using namespace std;


//浮点最小函数，防止默认min的int形参截断
double min_d(double a, double b) {
    return (a < b) ? a : b;
}

//定义点类
class Point {
public:
    int x, y;

    Point() {}

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

//按照横坐标x从小到大排序，若x相等则按纵坐标y从小到大排序
bool cmpx(const Point &n1, const Point &n2) {
    if (n1.x != n2.x) return n1.x < n2.x;
    return n1.y < n2.y;
}


//按y升序排序
bool cmpy(const Point &n1, const Point &n2) {
    return n1.y < n2.y;
}

//计算两点间距离的函数
double dis(const Point &a, const Point &b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}


//求两点水平距离
double disX(const Point &p1, const Point &p2) {
    double ans = (double) p1.x - (double) p2.x;
    if (ans < 0) return ans * -1;
    return ans;
}

//重载哈希函数，用于去除重复点
struct createhash {
    size_t operator()(const Point &P) const {
        return size_t(P.x * 202028 + P.y);
    }
};

//重载比较函数，哈希set去重复点用
struct isEqual {
    bool operator () (const Point &p1, const Point &p2) const {
        return (p1.x == p2.x) && (p1.y == p2.y);
    }
};
//暴力法求最近点对
double numerous(vector<Point> &node) {
    int n = node.size();
    auto Min = (double) INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // 更新最小值
            Min = min_d(Min, dis(node[i], node[j]));
        }
    }
    return Min;
}

//分治法求最近点对
double divide(vector<Point> &p, int left, int right) {
    //只有一个点,返回无穷大
    if (left == right)
        return INFINITY;
    //只有两个点，直接求两点距离
    if (left + 1 == right)
        return dis(p[left], p[right]);
    int mid = (left + right) / 2;
    double d = min_d(divide(p, left, mid), divide(p, mid + 1, right));

    double ans = d;

    int l = mid, r = mid;//定义左右两个起点，分别从中间向外找到符合水平距离<=d的点
    vector<Point> p1, p2;//用来存储这些点

    for(int i=left;i<right;i++){
        //找到距离中间的点的x的距离小于d的点
        if (p[mid].x >= p[i].x && disX(p[mid], p[i]) <= d) p1.push_back(p[i]);
        if (p[mid].x <= p[i].x && disX(p[mid], p[i]) <= d) p2.push_back(p[i]);
    }
    //用sort分别对左右空间的点按y值升序排序，时间复杂度O(nlogn)，即合并效率O(nlogn)
    sort(p1.begin(), p1.end(), cmpy);
    sort(p2.begin(), p2.end(), cmpy);

    int cnt = 0;//用来记录从小到大找到右侧第一个<=d的点的序号，此后最多有6个点在范围内
    for (int i = 0; i < p1.size(); i++) {
        while (cnt < p2.size() && (p1[i].y - p2[cnt].y) >= d)
            cnt++;
        cnt = min((int) p2.size(), cnt);
        for(int j=cnt;j<min((int)p2.size(),cnt+6);j++){
            if(!isEqual()(p1[i],p2[j]))//去除重复点
                ans = min_d(ans, dis(p1[i], p2[j]));
        }
    }
    return min_d(ans,d);//找到三种情况下的最小点
}
//分治+按y归并排序求最近点对
double merge_divide(vector<Point> &p, int left, int right) {
    //只有一个点,返回无穷大
    if (left == right)
        return (double)INT_MAX;
    //只有两个点，直接求两点距离,并对y排序
    if (left + 1 == right) {
        if (cmpy(p[right], p[left])) swap(p[left], p[right]);
        return dis(p[left], p[right]);
    }
    //当点数大于2时进行分治
    int mid = (left + right) / 2;
    int l = mid, r = mid;//定义左右两个起点，分别从中间向外找到符合水平距离<=d的点
    //记录中点的点
    Point midp=p[mid];
    double d = min_d(merge_divide(p, left, mid), merge_divide(p, mid + 1, right));

    double ans = d;
    //对y坐标进行排序
    inplace_merge(p.begin() + l, p.begin() + mid + 1, p.begin() + r + 1, cmpy);///所有的点按y排序的归并排序，合并效率O(n)
    vector<Point> p1, p2;//用来存储这些点
    for(int i=left;i<right;i++){
        //找到距离中间的点的x的距离小于d的点，将左右的点分开存放
        if (midp.x >= p[i].x && disX(midp, p[i]) <= d) p1.push_back(p[i]);
        if (midp.x <= p[i].x && disX(midp, p[i]) <= d) p2.push_back(p[i]);
    }
    int cnt = 0;//用来记录从小到大找到右侧第一个<=d的点的序号，此后最多有6个点在范围内
    for (auto & i : p1) {
        while (cnt < p2.size() && (i.y - p2[cnt].y) > d)//如果两个纵坐标之差大于d,则直接进行下一轮循环
            cnt++;
        cnt = min((int) p2.size(), cnt);
        for(int j=cnt;j<min((int)p2.size(),cnt+6);j++){
            if(!isEqual()(i,p2[j]))//去除重复点
                ans = min_d(ans, dis(i, p2[j]));
        }
    }
    return min_d(ans,d);//找到三种情况下的最近点对
}

int main() {
#define sample 10
#define batch 300000

    int n = batch;
    double t1 = 0,t2=0,t3=0;
    double ans1,ans2,ans3;
    vector<Point> node(n),node1,node2,node3;

    std::random_device rd;                // 产生一个随机数当作种子
    std::default_random_engine rng{rd()}; // 随机数生成引擎
    std::uniform_int_distribution<int> dist(0, n * 10);// 均匀分布生成数据

    for (int t = 1; t <= sample; t++) {
        cout << t << endl;
        //定义哈希表用来去重
        unordered_set<Point, createhash, isEqual> hash;
        //随机点对
        for (int i = 0; i < n; i++) {
            node[i].x = dist(rd);
            node[i].y = dist(rd);
            //选取10个样本点(这里选取0，1000，2000，...，9000十个样本点）
            if (i % (batch / 10) == 0) {
                cout << i << endl;
                cout << "样本点" << i / (batch / 10) << " : (" << node[i].x << ", " << node[i].y << "), 范围:[0," << n*10
                     << "]"
                     << endl;
            }
            if (hash.find(node[i]) == hash.end()) hash.insert(node[i]);
            else i--;
        }
        node1 = node,node2 =node,node3=node;
        clock_t start, end;

        start = clock();
        ans1 = numerous(node1);
        end = clock();
        t1 += (double) (end - start) / CLOCKS_PER_SEC;
        //cout <<"暴力: "<<t1<< endl;

        node2=node;
        sort(node2.begin(),node2.end(),cmpx);
        start = clock();
        ans2 = divide(node2,0,node2.size()-1);
        end = clock();
        t2 += (double) (end - start) / CLOCKS_PER_SEC;
        //cout<<"分治: "<<t2<<endl;

        node3=node;
        sort(node3.begin(),node3.end(),cmpx);
        start = clock();
        ans3 = merge_divide(node3,0,node3.size()-1);
        end = clock();
        t3 += (double) (end - start) / CLOCKS_PER_SEC;
        //cout<<"分治+归并: "<<t3<<endl;


    }
    cout<<"最终结果："<<endl;
    cout << "暴力："<<t1 / sample << endl;
    cout << "分治："<<t2 / sample << endl;
    cout << "分治+归并："<<t3 / sample << endl;
    //检验三种方法的正确性
    cout <<"暴力法求得距离： " <<ans1 << endl;
    cout <<"一般分治法求得距离： " <<ans2 << endl;
    cout <<"归并分治法求得距离 " <<ans3 << endl;
    return 0;
}
