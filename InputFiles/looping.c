#include<stdio.h>
int main()
{
	int i, j;
	for(i = 0; i < 10; i = i + 1)
	{
		for(j = 10; j > 0; j = j - 2)
		{
			printf("i : %d j : %d",i,j);
		}
	}
}
