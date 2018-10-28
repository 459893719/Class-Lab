/*#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"
#include <time.h>

int a[12][12], b[10][10], c[4][4][10],n;

void jieti(int ti[10][12], int ti2[10][12], int x, int y)
{
	if (x == 10)
	{
		n = n + 1;
		show_mainpage(ti);
		return;
	}
	int i, j = 0;
	if (ti2[x][y] == 0)
	{
		for (i = 1; i <= 9; i++)
		{
			if (a[x][i] == 0 && b[y][i] == 0 && c[(x - 1) / 3 + 1][(y - 1) / 3 + 1][i] == 0)
			{
				j = 1;
				ti[x][y] = i;
				a[x][i] = 1;
				b[y][i] = 1;
				c[(x - 1) / 3 + 1][(y - 1) / 3 + 1][i] = 1;
				if (y != 9)
				{
					jieti(ti, ti2, x, y + 1);
				}
				if (y == 9)
				{
					jieti(ti, ti2, x + 1, 1);
				}
				a[x][i] = 0;
				b[y][i] = 0;
				c[(x - 1) / 3 + 1][(y - 1) / 3 + 1][i] = 0;
			}
		}
		if (j == 0)return;

	}
	else
	{
		if (y != 9)
		{
			jieti(ti, ti2, x, y + 1);
		}
		if (y == 9)
		{
			jieti(ti, ti2, x + 1, 1);
		}
	}
}

int main()
{
	int ti[12][12] = { 0 }, ti2[12][12] = { 0 }, i, j;
	for (i = 1; i <= 9; i++)
	{
		for (j = 1; j <= 9; j++)
		{
			if (ti[i][j] != 0)
			{
				a[i][ti[i][j]] = 1;
				b[j][ti[i][j]] = 1;
				c[(i - 1) / 3 + 1][(j - 1) / 3 + 1][ti[i][j]] = 1;
			}
		}
	}
	FILE *fp;
	if ((fp = fopen("normal.txt", "r")) == NULL) {
		printf("cannot open the file \"hard.txt\"\n");
		exit(0);
	}
	srand(time(NULL));
	
	fseek(fp, (19 * 9 + 2) * 2, 0);
	for (int i = 1; i <= 9; i++) {//±£´æa
		for (int j = 1; j <= 9; j++) {
			fscanf(fp, "%d", &ti[i][j]);
			if (ti[i][j] == 0) {
				ti2[i][j] = 0;
			}
			else {
				ti2[i][j] = 1;
			}
		}
	}
	show_mainpage(ti);
	putchar('\n');
	jieti(ti, ti2, 1, 1);
	return 0;
}*/

#include<stdio.h>
#include<stdlib.h>
#include"sudoku.h"
int a[10][10], b[10][10], c[4][4][10], n;
/*void print(int ti[10][10])
{
	int i, j;
	for (j = 1; j <= 9; j++)
	{
		printf("-------------------\n");
		for (i = 1; i <= 9; i++)
		{
			printf("|%d", ti[j][i]);
		}
		printf("|\n");
	}
	printf("-------------------\n");
	printf("\n");
}*/
void jieti(int ti[12][12], int ti2[12][12], int x, int y)
{
	if (x == 10)
	{
		n = n + 1;
		show_mainpage(ti);
		return;
	}
	int i, j = 0;
	if (ti2[x][y] == 0)
	{
		for (i = 1; i <= 9; i++)
		{
			if (a[x][i] == 0 && b[y][i] == 0 && c[(x - 1) / 3 + 1][(y - 1) / 3 + 1][i] == 0)
			{
				j = 1;
				ti[x][y] = i;
				a[x][i] = 1;
				b[y][i] = 1;
				c[(x - 1) / 3 + 1][(y - 1) / 3 + 1][i] = 1;
				if (y != 9)
				{
					jieti(ti, ti2, x, y + 1);
				}
				if (y == 9)
				{
					jieti(ti, ti2, x + 1, 1);
				}
				a[x][i] = 0;
				b[y][i] = 0;
				c[(x - 1) / 3 + 1][(y - 1) / 3 + 1][i] = 0;
			}
		}
		if (j == 0)return;

	}
	else
	{
		if (y != 9)
		{
			jieti(ti, ti2, x, y + 1);
		}
		if (y == 9)
		{
			jieti(ti, ti2, x + 1, 1);
		}
	}
}
int main()
{
	int ti[12][12] = {0}, ti2[12][12] = {0}, i, j;
	FILE *fp;
	if ((fp = fopen("insane.txt", "r")) == NULL) {
		printf("cannot open the file \"hard.txt\"\n");
		exit(0);
	}
	srand(time(NULL));
	fseek(fp, (19 * 9 + 2) * 6, 0);
	for (int i = 1; i <= 9; i++) {//±£´æa
		for (int j = 1; j <= 9; j++) {
			fscanf(fp, "%d", &ti[i][j]);
			ti2[i][j] = ti[i][j];
		}
	}
	for (i = 1; i <= 9; i++)
	{
		for (j = 1; j <= 9; j++)
		{
			if (ti[i][j] != 0)
			{
				a[i][ti[i][j]] = 1;
				b[j][ti[i][j]] = 1;
				c[(i - 1) / 3 + 1][(j - 1) / 3 + 1][ti[i][j]] = 1;
			}
		}
	}
	show_mainpage(ti);
	putchar('\n');
	jieti(ti, ti2, 1, 1);
	printf("%d", n);
	system("pause");
	return 0;
}
