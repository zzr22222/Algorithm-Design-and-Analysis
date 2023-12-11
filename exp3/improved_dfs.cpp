#include <iostream>
#include <ctime>
#include<cstdlib>

using namespace std;

#define COLOR 25    //颜色数
#define VERTEX 450     //点数
//#define EDGE 17
//#define EDGE 5714   //边数
//#define EDGE 8169
#define EDGE 8260


class Vertex {
public:
    int color;
    int state[COLOR + 1];  //颜色状态，1为可选，非1为不可选
    int choice;  //可选颜色数，即state中1的数量
    int restrain;  //相邻数量,度
    Vertex() {
        color = 0;
        for (int i = 0; i < COLOR + 1; ++i) {
            state[i] = 1;
        }
        choice = COLOR;
        restrain = 0;
    }
};


//int map[VERTEX + 1][VERTEX + 1];  //图的邻接矩阵
int map2[VERTEX + 1][450];  ///图的邻接表
long long int sum = 0;   //记录解的个数
long Start;
long End;

int MRV_FORWARD1(Vertex *S) {
    int min = COLOR, minIndex = -1;
    for (int i = 1; i <= VERTEX; ++i) {
        for(int i=1;i<=VERTEX;i++){
            if(S[i].color==0){
                if(S[i].choice<min){
                    min=S[i].choice;
                    minIndex=i;
                }
            }
        }
    }
    S[minIndex].color = 1;
    int next=0;
    for (int k = 1; k <= map2[minIndex][0]; ++k) {
        int j = map2[minIndex][k]; //j表示与它相邻的节点的下标
        S[j].choice--;  //可选颜色数--
        S[j].restrain--; //相邻未填色数--
        S[j].state[1] = -minIndex;  //第一种颜色不可填了
        if (S[j].choice == 0) {
            minIndex = j;
        }
    }
    return next;
}
/*
int getNext(Vertex *S) {
    int min = COLOR;
    int next = -1;
    for (int i = 1; i <= VERTEX; ++i) {
        if (S[i].color == 0) {
            if (S[i].choice < min) {
                min = S[i].choice;
                next = i;
            }
            else if (S[i].choice == min) {
                if (S[i].restrain > S[next].restrain) {
                    min = S[i].choice;
                    next = i;
                }
            }
        }
    }
    return next;
}*/

int MRV(Vertex *v) { ///选择当前可填涂颜色最少的点进行涂色（MRV）
    int min=COLOR;
    int minindex=1;
    for(int i=1;i<=VERTEX;i++){
        if(v[i].color==0){
            if(v[i].choice<min){
                min=v[i].choice;
                minindex=i;
            }
        }
    }
    return minindex;
}

int MRV_DH(Vertex *v){    ///MRV+选择度最大的点（DH）
    int min=COLOR;
    int minindex=-1;
    for(int i=1;i<=VERTEX;i++){
        if(v[i].color==0) {
            if (v[i].choice < min) {
                min = v[i].choice;
                minindex = i;
            }
                //DH
            else if (v[i].choice == min) {
                if (v[i].restrain > v[minindex].restrain) {
                    minindex = i;
                }
            }
        }
    }
    return minindex;
}


//搜索函数
int DFS(Vertex *S, int now, int count, int used) {
    if (count == VERTEX) //到达叶子,找到一个着色方案
    {
        /*End = clock();
        cout << End - Start << endl;
        for (int i = 1; i <= VERTEX; i++) //输出该着色方案
            cout << S[i].color << " ";
        cout << endl;
        exit(1);*/

        sum += S[now].choice;

        /*if (sum > 1000000000) {
            End = clock();
            cout << End - Start << endl;
            exit(1);
        }*/

        return S[now].choice;

    } else {
        int s = 0;
        for (int i = 1; i <= COLOR; i++) {
            if (S[now].state[i] == 1) {
                int ss = 0;      ///一种颜色的结果数
                S[now].color = i;
                bool isNew = i > used;    //是不是新出现的颜色
                //剪枝--向前探查
                for (int k = 1; k <= map2[now][0]; ++k) {
                    int j = map2[now][k];
                    if (S[j].color == 0 && S[j].state[i] == 1) { //下一个节点没涂色并且可以选现在这个颜色
                       /* S[j].state[i] = -now;
                        S[j].choice--;
                        S[j].restrain--;*/
                        if (S[j].choice == 1) { //可选颜色只有一种，且剩的这个颜色就是这个颜色
                            goto BACK;           ///直接回溯
                        } else {   //剩下颜色数>1，说明这个颜色可以选
                            S[j].state[i] = -now;   //下一个节点不能再选这个颜色了
                            S[j].choice--;         //选择颜色数--
                            S[j].restrain++;       ///约束++
                        }
                    }
                }
                if (isNew)
                    ss = DFS(S, MRV_DH(S), count + 1, used + 1);
                else
                    ss = DFS(S, MRV_DH(S), count + 1, used);

                BACK:
                for (int k = 1; k <= map2[now][0]; ++k) {
                    int j = map2[now][k];
                    if (S[j].state[i] == -now) {  //不可选的话，直接回退
                        S[j].choice++;
                        S[j].restrain++;
                        S[j].state[i] = 1;
                    }
                }
                S[now].color = 0;       //回退,表示当前节点不能选这个颜色
                if (isNew) {           //如果是新出现的颜色
                    s += ss * (COLOR - used);    ///颜色轮寻
                    sum += ss * (COLOR - used - 1);
                    break;
                }
                s += ss;                 ///goto作用域到这？？
            }
        }
        if (sum > 1000000000) {
            End = clock();
            cout << End - Start << endl;
            exit(1);
        } else
            return s;
    }
}

int DFS_1(Vertex *S, int now, int count, int used) {
    if (count == VERTEX) //到达叶子,找到一个着色方案
    {
        sum += S[now].choice;

        return S[now].choice;

    } else {
        int s = 0;
        for (int i = 1; i <= COLOR; i++) {
            if (S[now].state[i] == 1) {
                int ss = 0;      ///一种颜色的结果数
                S[now].color = i;
                bool isNew = i > used;    //是不是新出现的颜色
                for (int k = 1; k <= map2[now][0]; ++k) {
                    int j = map2[now][k];
                    if (S[j].color == 0 && S[j].state[i] == 1) { //下一个节点没涂色并且可以选现在这个颜色
                        S[j].state[i] = -now;
                        S[j].choice--;
                        S[j].restrain--;
                        ///使用向前探查
                        /*if (S[j].choice == 1) { //可选颜色只有一种，且剩的这个颜色就是这个颜色
                            goto BACK;           ///直接回溯
                        } else {   //剩下颜色数>1，说明这个颜色可以选
                            S[j].state[i] = -now;   //下一个节点不能再选这个颜色了
                            S[j].choice--;         //选择颜色数--
                            S[j].restrain++;       ///约束++
                        }*/
                    }
                }
                if (isNew)
                    ss = DFS(S, MRV_DH(S), count + 1, used + 1);
                else
                    ss = DFS(S, MRV_DH(S), count + 1, used);

                BACK:
              /*  for (int k = 1; k <= map2[now][0]; ++k) {
                    int j = map2[now][k];
                    if (S[j].state[i] == -now) {  //不可选的话，直接回退
                        S[j].choice++;
                        S[j].restrain++;
                        S[j].state[i] = 1;
                    }
                }*/
            //    S[now].color = 0;       //回退,表示当前节点不能选这个颜色
                if (isNew) {           //如果是新出现的颜色
                    s += ss * (COLOR - used);    ///颜色轮寻
                    sum += ss * (COLOR - used - 1);
                    break;
                }
                s += ss;                 ///goto作用域到这？？
            }
        }
        if (sum > 100000000) {
            End = clock();
            cout << End - Start << endl;
            exit(1);
        } else
            return s;
    }
}

int main() {
    Vertex S[VERTEX + 1];
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
        if ((fp = fopen("le450_15b.txt", "r")) == NULL)  //打开文件
        {
            printf("Can not open file!\n");
            exit(1);
        }
    } else if (command == 4) {
        if ((fp = fopen("le450_25a.txt", "r")) == NULL)  //打开文件
        {
            printf("Can not open file!\n");
            exit(1);
        }
    }
    int u, v;
    char ch;
    for (int i = 1; i <= EDGE; i++) {
        fscanf(fp, "%c%d%d\n", &ch, &u, &v);
       // map[u][v] = map[v][u] = 1;
        map2[u][0]++;//地址++
        map2[u][map2[u][0]] = v;
        map2[v][0]++;
        map2[v][map2[v][0]] = u;
        S[u].restrain++;
        S[v].restrain++;
    }


    cout << "开始实验！" << endl;
    fclose(fp);
    Start = clock();
    int a = DFS(S, MRV_DH(S), 1, 0);   ///change


    End = clock();
    cout << "TIME:" <<End - Start <<"ms"<<endl;
    cout << "ANSWER:" << a << endl;
    return 0;
}



