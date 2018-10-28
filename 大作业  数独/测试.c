#include <stdio.h>
#include "sudoku.h"
#include <stdlib.h>
#include <time.h>

int main() {
	int a[12][12] = { 0 }, t, book[12][12] = { 0 };
	FILE *fp;
	if ((fp = fopen("easy.txt", "r")) == NULL) {
		printf("cannot open the file \"easy.txt\"\n");
		exit(0);
	}
	srand(time(NULL));
	/*
	for (int i = 0; i < rand() % 8; i++) {
		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= 9; j++) {
				fscanf(fp, "%d", &t);
			}
		}
	}
	*/
		fseek(fp, (19 * 9 + 2)*rand() % 8, 0);
		for (int i = 1; i <= 9; i++) {//±£´æa
			for (int j = 1; j <= 9; j++) {
				fscanf(fp, "%d", &a[i][j]);
			}
		}
		show_mainpage(a,book,1,2);
	
	system("pause");
	return 0;
}