#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
int main()
{
	int i;
	srand(time(NULL));     //ÿ��ִ�����Ӳ�ͬ�����ɲ�ͬ�������
	for (i = 0; i<10; i++)
	{
		printf("%d\n", rand());  //��Ϊִ��̫�죬����һ���ӣ�10�����������ͨ�ģ�����ÿ��ִ���ǲ�ͬ�� 
	}
	system("pause");
	return 0;
}