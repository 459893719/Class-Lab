#include <stdio.h>
#include "sudoku.h"
#include <stdlib.h>
#include <conio.h>

int main() {
	int a[12][12] = { 0 }, book[12][12] = { 0 }, if_save, tot, succ;//if_save表示游戏是否有可运行的存档
	FILE *fp;
	while (1) {
		//读入if_save的值
		if ((fp = fopen("if_save.txt", "r")) == NULL) {
			printf("                              cannot open the file \"if_save.txt\"\n");
			exit(0);
		}
		fscanf(fp, "%d", &if_save);
		fclose(fp);

		system("cls");
		show_menu(if_save);//根据if_save的值确定是否有继续游戏的选项
		char choice;
		//检测是否有非法输入
		while (1) {
			choice = getch();
			if (choice < '0' || choice>'4' || (if_save == 0 && choice == '0')) {
				continue;
			}
			else {
				break;
			}
		}
		switch (choice) {
		case '0': {//若继续游戏
			//从save文件中读取a[][]和book[][]和tot和succ
			if (if_save == 1) {//只有在有存档文件时才能进行该操作
				if ((fp = fopen("save.txt", "r")) == NULL) {
					printf("                              cannot open the file \"save.txt\"\n");
					exit(0);
				}
				for (int i = 1; i <= 9; i++) {//保存a
					for (int j = 1; j <= 9; j++) {
						fscanf(fp, "%d", &a[i][j]);
						//printf("%d ", a[i][j]);//*********************
					}
					//printf("\n");//
				}
				for (int i = 1; i <= 9; i++) {//保存book
					for (int j = 1; j <= 9; j++) {
						fscanf(fp, "%d", &book[i][j]);
						//printf("%d ", book[i][j]);//
					}
					//printf("\n");//
				}
				int tot = 0, succ = 0;
				fseek(fp, 2, 1);
				fscanf(fp, "%d", &tot);
				fscanf(fp, "%d", &succ);
				//printf("%d %d\n", tot, succ);//
				//system("pause");//
				if_save = main_game(a, book, tot, succ);
			}
			break;
		}
		case '1': {//若开始新游戏
			system("cls");
			int succ;
			select_difficulty(a, book, &succ);//难度选择，将对应的题目信息赋给a,book,succ

			if_save = main_game(a, book, 0, succ);
			break;
		}
		case '2': {//若玩家要获得游戏的帮助
			system("cls");
			print_guide();//打印游戏的规则
			break;
		}
		case '3': {//关于制作者
			system("cls");
			print_info();//打印制作者的信息
			break;
		}
		case '4': {//若退出游戏
			//将if_save传进文件中
			if ((fp = fopen("if_save.txt", "w")) == NULL) {
				printf("                              cannot open the file \"if_save.txt\"\n");
				exit(0);
			}
			fprintf(fp, "%d", if_save);
			fclose(fp);
			return 0;
		}
		}
	}
	return 0;
}
