#include <time.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
int const N=1000;
void shuffle(int a[], int n)
{
    int p1;
    int p2;
    int tmp;

    while(n--)
    {
        p1 = rand() % (N );
        p2 = rand() % (N );
        tmp = a[p1];
        a[p1] = a[p2];
        a[p2] = tmp;
    }
}
int main()
{
    int a[N + 1];
    int i;
    srand(time(NULL));
    for(i = 0; i <N; i++)
        a[i] = i+1;
    shuffle(a, 40000);
    int sum=20;
    for (int i = 0; i < sum - 1; i++) //进行sum-1次排序即可，先选出第i大值
	{
		for (int j = 0; j < sum - 1 - i; j++)//将第i大值放在后面，后面的更大值不需要比较了
		{
			if (a[j] > a[j + 1])
			{
				int temp;
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < sum - 1; i++)
        cout<<a[i]<<endl;
    return 0;
}
