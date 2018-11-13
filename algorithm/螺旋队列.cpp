
#include <stdio.h>
#include<iostream>
#define  max(a,b)   ((a)<(b)?(b):(a))
#define abs(a)         ((a)>0?(a):-(a))
int  foo(int x, int y);
using namespace std;
int  foo(int x, int y)
{
	int v;
	int t = max(abs(x), abs(y));//当前坐标所在圈
	int max_value = (2 * t + 1)*(2 * t + 1);//当前圈上最大值
	if (x == -t)//左边
	{
		v = max_value + (3 * x - y);
	}
	else if (y == -t)//上边
	{
		v = max_value + (x + y);
	}
	else if (y == t)//下边
	{
		v = max_value + (-5 * y - x);
	}
	else//右边
		v = max_value + (-7 * x + y);
	return v;
}
void  main()
{
	int x, y, temp;
	for (y = -4; y <= 4; y++)
	{
		for (x = -4; x <= 4; x++)
		{
			temp = foo(x, y);
			if (temp / 10 == 0)
			{
				cout << temp << "  ";
			}
			else
				cout << temp << " ";
		}
		cout << endl;
	}
	cin >> x;
	cin >> y;
	cout << foo(x, y);
	system("pause");
}