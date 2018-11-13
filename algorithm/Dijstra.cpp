/*图论与网络最优化算法书中的Dijkstra算法步骤：
S：具有永久标号的顶点集；
l(v):v的标记；
f(v):v的父亲，用以确定最短路径（链）；
输入加权图的带权邻接矩阵Wn*n=(w(u,v))n*n.
1) l(v)赋值0，任意v不等于v0，l（v）等于无穷大，S加入v0，u=v0；
2) 任意v属于s1=V-S，若l(v)>l(u)+w(u,v),则l(v)=l(u)+w(u,v),f(v)=u；
3) 设v*是使l(v)取最小值的s1中的顶点，S中加入v*，u=v*；
4) 若S1不为空，转2)，否则，停止*/ 
#include <iostream>  
#include <vector>  
#include <stack>  

using namespace std;
int k = INT_MAX;//INT_MAX=2147483647
int map[6][6] = 
{    //采用邻接定义有向图，用k=INT_MAX代替无穷大定义不相连两点  
	{ 0,	50,		k,		40,		25,		10 },
	{ 50,	0,		15,		20,		k,		25 },
	{ k,	15,		0,		10,		20,		k },
	{ 40,	20,		10,		0,		10,		25 },
	{25,	k ,		20,		10,		0,		55},
	{ 10,	25,		k,		 25,	55,		0 }
};
//定义Dijkstra函数
void Dijkstra(
	const int Vertex,    //节点数目
	const int startVertex,    //源节点
	int(map)[6][6],            //有向图邻接矩阵
	int *distance,            //各个节点到达源节点的距离
	int *prevVertex)           //各个节点的父亲节点
{
	vector<bool> S;                 //是否已经在S集合中  
	S.reserve(0);					//初始化默认存储为0
	S.assign(Vertex, false);   //初始化，所有的节点都不在S集合中  
	
	//初始化distance和prevVertex数组
	for (int i = 0; i < Vertex; ++i)
	{
		distance[i] = map[startVertex][i];
		if (map[startVertex][i] < k)
			prevVertex[i] = startVertex;
		else
			prevVertex[i] = -1;       //表示还不知道父亲节点是什么  
	}
	prevVertex[startVertex] = -1;

	//用贪心算法处理不在S集合中的每一个节点
	S[startVertex] = true;          //开始节点放入S集合中  
	int u = startVertex;			//定义u为开始节点
	//这里循环从1开始是因为开始节点已经存放在S中了，还有numOfVertex-1个节点要处理
	for (int i = 1; i < Vertex; i++)       
	{
		//选择distance最小的一个节点
		int nextVertex = u;
		int tempDistance = k;
		for (int j = 0; j < Vertex; ++j)
		{	
			//寻找不在S集合中的distance最小的节点
			if ((S[j] == false) && (distance[j] < tempDistance))  
			{
				nextVertex = j;
				tempDistance = distance[j];
			}
		}
		//将找到的不在S集合中的distance最小的节点放入S集合中
		S[nextVertex] = true;  
		u = nextVertex;//下一次寻找的开始节点  

		//更新distance
		for (int j = 0; j < Vertex; j++)
		{
			if (S[j] == false && map[u][j] < INT_MAX)
			{
				int temp = distance[u] + map[u][j];
				if (temp < distance[j])
				{
					distance[j] = temp;
					prevVertex[j] = u;
				}
			}
		}
	}
}

int main(int argc, const char * argv[])
{
	int distance[6];
	int preVertex[6];
	int final[6];
	for (int i = 0; i < 6; ++i)
	{
		//输出i为起点的结果
		Dijkstra(6, i, map, distance, preVertex);
		for (int j = 0; j < 6; ++j)
		{
			int index = j;
			stack<int> trace;
			while (preVertex[index] != -1)//将父亲点依次压入栈中
			{
				trace.push(preVertex[index]);
				index = preVertex[index];
			}
			cout << "以"<<i<<"开始到"<<j<<"的最短路径是：";
			while (!trace.empty()) 
			{
				cout << trace.top() << "--";
				trace.pop();
			}
			cout << j;
			cout << "\t\t距离是：" << distance[j] << endl;
		}
		int total = 0;
		for (int j = 0; j < 6; ++j)
		{
			total += distance[j];
		}
		cout << "以" << i << "开始到其他所有地方的最短路径之和是："<<total;
		final[i] = total;
		cout << endl<<endl;
	}
	system("pause");
	return 0;
}