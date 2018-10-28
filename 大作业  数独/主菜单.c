#include <stdio.h>
#include "sudoku.h"
#include <stdlib.h>
#include <conio.h>

int main() {
	int a[12][12] = { 0 }, book[12][12] = { 0 }, if_save, tot, succ;//if_save��ʾ��Ϸ�Ƿ��п����еĴ浵
	FILE *fp;
	while (1) {
		//����if_save��ֵ
		if ((fp = fopen("if_save.txt", "r")) == NULL) {
			printf("                              cannot open the file \"if_save.txt\"\n");
			exit(0);
		}
		fscanf(fp, "%d", &if_save);
		fclose(fp);

		system("cls");
		show_menu(if_save);//����if_save��ֵȷ���Ƿ��м�����Ϸ��ѡ��
		char choice;
		//����Ƿ��зǷ�����
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
		case '0': {//��������Ϸ
			//��save�ļ��ж�ȡa[][]��book[][]��tot��succ
			if (if_save == 1) {//ֻ�����д浵�ļ�ʱ���ܽ��иò���
				if ((fp = fopen("save.txt", "r")) == NULL) {
					printf("                              cannot open the file \"save.txt\"\n");
					exit(0);
				}
				for (int i = 1; i <= 9; i++) {//����a
					for (int j = 1; j <= 9; j++) {
						fscanf(fp, "%d", &a[i][j]);
						//printf("%d ", a[i][j]);//*********************
					}
					//printf("\n");//
				}
				for (int i = 1; i <= 9; i++) {//����book
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
		case '1': {//����ʼ����Ϸ
			system("cls");
			int succ;
			select_difficulty(a, book, &succ);//�Ѷ�ѡ�񣬽���Ӧ����Ŀ��Ϣ����a,book,succ

			if_save = main_game(a, book, 0, succ);
			break;
		}
		case '2': {//�����Ҫ�����Ϸ�İ���
			system("cls");
			print_guide();//��ӡ��Ϸ�Ĺ���
			break;
		}
		case '3': {//����������
			system("cls");
			print_info();//��ӡ�����ߵ���Ϣ
			break;
		}
		case '4': {//���˳���Ϸ
			//��if_save�����ļ���
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
