#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
int main()
{
	int i;
	srand(time(NULL));     //每次执行种子不同，生成不同的随机数
	for (i = 0; i<10; i++)
	{
		printf("%d\n", rand());  //因为执行太快，不到一秒钟，10个随机数是相通的，但是每次执行是不同的 
	}
	system("pause");
	return 0;
}