#include<iostream>
#include <ctime>

using namespace std;

#define COLOR 4    //颜色数
#define VERTEX  9    //点数
#define EDGE 17

class Color{
private:
    int n=VERTEX,			//顶点数
    m=COLOR;			//颜色数
public:
    bool OK(int k);
    int Backtrack(int t);
};

int a[VERTEX + 1][VERTEX + 1];  //图的邻接矩阵
//int a[VERTEX + 1][9];    ///图的邻接表
long sum=0; //解的个数
int * x=new int[VERTEX+1];		//当前解, x[2]=3;表示第二个点染3号色

bool Color::OK(int k)
{//查看是否符合条件
    for(int j=1;j<=n;j++)
        if( (a[k][j]==1)&&(x[k]==x[j]) )//即第k个和第j个相邻且染同色(在邻接表里有边的点不能染同色)
            return false;
    return true;	//此处不可写else 必须走完j,和所有相邻的点检测一遍
}
int paintcolor(int i,int color){
    for(int j=1;j<=a[i][0];i++){
        int k=a[i][j];
        if(x[i]==0){}
    }

}
int Color::Backtrack(int t)
{
    if(t>n){
        sum++;//解决方案++ 拓展至子结点
        cout<<"染色方案_"<<sum<<":\t";
        for (int i = 1; i <=n; i++) //输出解决方案
            cout<<x[i]<<" ";
        cout<<endl;
    }
    else
        for (int i = 1; i <=m; i++)	//每种颜色都试下
        {
            x[t]=i;					//尝试染色
            if(OK(t))Backtrack(t+1);//if:ok 递归进入下一个
            x[t]=0;
        }
        return sum;
}

int main(){
    FILE *fp=NULL;
    int command;
    cin >> command;
    if (command == 1) {
        if ((fp = fopen("test.txt", "r")) == NULL)  //储存地图的边的关系
        {
            printf("Can not open file!\n");
            exit(1);
        }
    } else if (command == 2) {
        if ((fp = fopen("le450_5a.txt", "r")) == NULL)  //打开文件
        {
            printf("Can not open file!\n");
            exit(1);
        }
    } else if (command == 3) {
        if ((fp = fopen("le450_15b.col", "r")) == NULL)  //打开文件
        {
            printf("Can not open file!\n");
            exit(1);
        }
    } else if (command == 4) {
        if ((fp = fopen("le450_25a.col", "r")) == NULL)  //打开文件
        {
            printf("Can not open file!\n");
            exit(1);
        }
    }
    int u, v;
    char ch;
    for (int i = 1; i <= EDGE; i++) {
        fscanf(fp, "%c%d%d\n", &ch, &u, &v);
        a[u][v] = a[v][u] = 1;
       /* a[u][0]++;
        a[u][a[u][0]] = v;
        a[v][0]++;
        a[v][a[v][0]] = u;*/
    }

    cout << "开始实验！" << endl;
    fclose(fp);
    Color co;

    for(int i=0;i<=VERTEX;i++) x[i]=0;

    clock_t start,end;
    start = clock();
    int sum = co.Backtrack(1);
    end = clock();

    cout<<"Time:"<<end-start<<"ms"<<endl;
    cout<<"共有"<<sum<< " 个染色方案"<< endl;	//调用
}

