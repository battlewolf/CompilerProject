#include<stdio.h>
int main()
{
	int n, i, j;
	scanf("%d",&n);
	printf("\nThe number is %d",n);
	i = 0;
	while(i < 3)
	{
		i = i + 1;
		j = 0;
		while(j < 3)
		{
			j = j + 1;
			printf("\nNested while");
		}
	}
}
