#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>

void color(short x) //�Զ��庯���ݲ����ı���ɫ   
{
	if (x >= 0 && x <= 15)//������0-15�ķ�Χ��ɫ  
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);    //ֻ��һ���������ı�������ɫ   
	else//Ĭ�ϵ���ɫ��ɫ  
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void show_mainpage(int(*a)[12], int(*book)[12],int curx,int cury);
int if_wrong(int(*a)[12], int i, int j, int in);
int main_game(int (*a)[12],int (*book)[12],int tot,int succ) {//����Ϸ������������Ϸ�����⺯��
	int if_save = 1,curx = 1,cury = 1;
	while (1) {

		system("cls");
		show_mainpage(a, book, curx, cury);
		//�˴��ж�����Ƿ��Ѿ�ͨ�ء���ͨ�أ������˳�
		if (tot == succ) {
			printf("\n\n                              ��ϲ���Ѿ��������������������ʦԽ��Խ������~\n");
			if_save = 0;//�浵���

			FILE *fp;
			if ((fp = fopen("if_save.txt", "w")) == NULL) {//���������浵��ʧ
				printf("                              cannot open the file \"if_save.txt\"\n");
				exit(0);
			}
			fprintf(fp, "%d", if_save);
			fclose(fp);
			printf("                              ");
			system("pause");
			system("cls");
			return if_save;
		}
		//�������������Ĳ���
		//���������ѡ�������Ϸ���Ǳ�����Ϸ
		printf("                              ��Ҫ����ʲô����?\n                              1----������Ϸ  2----�����ļ�\n");

		char choice;
		while (1) {//�ж��������ĺϷ���
			choice = getch();
			if (choice != '1' && choice != '2') {
				continue;
			}
			else {
				break;
			}
		}

		//��������Ϸ
		int i, j; char ch;
		//��ʱ���������Ҫ��ʲô���ӽ��в����������Ӧ���ӵ�����
		if (choice == '1') {
			while (1) {
				system("cls");
				show_mainpage(a, book, curx, cury);
				printf("\n                              ���ĸ����ӽ��в�������WASD���ƹ�꣬T������ѡ����\n");
				while ((ch = getch()) != 't') {//chΪ�س�ʱ
					//ֻ��chΪw a s d ʱ����Ч
					//����ƶ�
					switch (ch) {
					case 'w': {//�������
						if (curx > 1) {//���������
							curx--;
						}
						break;
					}
					case 'a': {//����
						if (cury > 1) {//���������
							cury--;
						}
						break;
					}
					case 's': {//����
						if (curx < 9) {//���������
							curx++;
						}
						break;
					}
					case 'd': {//����
						if (cury < 9) {//���������
							cury++;
						}
						break;
					}
					}
					//��ӡ�ƶ���Ľ���
					system("cls");
					show_mainpage(a, book, curx, cury);
					printf("\n                              ���ĸ����ӽ��в�������WASD���ƹ�꣬T������ѡ����\n");
				}
				//�жϴ˴�����ĺϷ���
				i = curx; j = cury;
				if ((i < 1 || i>9 || j < 1 || j>9) || book[i][j] == 0) {//���ø��Ӳ��ܲ���ʱ�����������ѡ��һ��
					printf("                              ������Ӳ��ܲ���Ŷ��������ѡ��\n");
					printf("                              ");
					system("pause");
				}
				else {
					break;
				}
			}
			//����ҵĸ���������ȷ
			//����ø��Ӷ�Ӧ�Ĳ������޸�������ɾ������
			printf("                              ���(%d,%d)����ʲô������\n                              1----�޸��������    2----ɾ���������\n", i, j);

			while (1) {//�ж��������ĺϷ���
				choice = getch();
				if (choice != '1' && choice != '2') {
					continue;
				}
				else {
					break;
				}
			}
			//���޸ĸø����ϵ���
			//����������޸ĳ�ʲô��
			if (choice == '1') {
				while (1) {
					printf("                              ���޸ĳ�ʲô����\n");
					int in; char ch1;
					//�ж�����ĺϷ���
					while (1) {
						
						ch1 = getch();
						//���������ַ�Ϊ���֣���������룬���򲻽���
						if (isdigit(ch1)) {
							in = ch1 - '0';
							break;
						}
					}
					//�жϸø����޸ĳ���һ�����Ƿ���Ϲ���
					if (if_wrong(a,i,j,in)) {//��������Ϲ���ѯ������Ƿ���������
						printf("                               %d ������������Ŷ����������һ����?\n                              1----��   2---��\n",in);
						
						while (1) {//�ж��������ĺϷ���
							choice = getch();
							if (choice != '1' && choice != '2') {
								printf("                              �Ƿ����룡\n");
							}
							else {
								break;
							}
						}

						if (choice == '1') {//�����������
							continue;
						}
						else {//�������������
							break;
						}
					}
					else {//������Ϲ���
						if (a[i][j] == 0) {//������û������ʱ�����tot�Ż�仯
							tot++;
						}
						a[i][j] = in;
						break;
					}
				}
			}
			else {//ɾ���ø����е���
				if (a[i][j] > 0) {//���ø�����ǰ�������ܽ���ɾ��
					a[i][j] = 0;
					tot--;
				}
			}
		}
		//���ڵ�һ��ѡ���У����ѡ���˱�����Ϸ
		else {
			//���б������(����a,book,tot,succ)
			FILE *fp;
			if ((fp = fopen("save.txt", "w")) == NULL) {
				printf("                              cannot open the file \"save.txt\"\n");
				exit(0);
			}

			for (int i = 1; i <= 9; i++) {//����a
				for (int j = 1; j <= 9; j++) {
					fprintf(fp, "%d ", a[i][j]);
					
				}
				fprintf(fp, "\n");
			}
			for (int i = 1; i <= 9; i++) {//����book
				for (int j = 1; j <= 9; j++) {
					fprintf(fp, "%d ", book[i][j]);
				}
				fprintf(fp, "\n");
			}
			fprintf(fp, "%d\n%d", tot, succ);
			if_save = 1;
			fclose(fp);
			printf("                              ����ɹ���\n");
			//printf("\n%d %d", tot, succ);//***
			printf("                              �Ƿ��˳���Ϸ��\n                              1----��    2----��\n");


			while (1) {//�ж��������ĺϷ���
				choice = getch();
				if (choice != '1' && choice != '2') {
					continue;
				}
				else {
					break;
				}
			}
			if (choice == '1') {//�˳���Ϸ
				if ((fp = fopen("if_save.txt", "w")) == NULL) {
					printf("                              cannot open the file \"if_save.txt\"\n");
					exit(0);
				}
				fprintf(fp, "%d", if_save);
				fclose(fp);
				return if_save;
			}
			else {//���˳�
				continue;
			}
			
		}
	}
}

void show_menu(int if_save) {//���˵�����ʾ
	printf("\
                               -------------------------------------------------\n\
                              ||                                               ||\n\
                              ||                   ������Ϸ                    ||\n\
                              ||                        ----By ���Ӻ�          ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                              ||           (��������Ҫ���еĲ�����Ӧ������)    ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n");
	if (if_save) {
		printf("\
                              ||       0--------������Ϸ                       ||\n");
	}
	else {
		printf("\
                              ||                                               ||\n");
	}
	printf("\
                              ||       1--------��ʼ����Ϸ                     ||\n\
                              ||       2--------��ȡ����                       ||\n\
                              ||       3--------��������Ϣ                     ||\n\
                              ||       3--------��������Ϣ                     ||
                              ||       4--------�˳���Ϸ                       ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                               -------------------------------------------------\n ");
}

void select_difficulty(int(*a)[12], int(*book)[12], int *succ) {//��ӡ�Ѷ�ѡ��˵�������ȡ��Ŀ�����µ���Ϸ
	printf("\
                               -------------------------------------------------\n\
                              || ��ѡ����Ϸ���Ѷȣ�                            ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                              || 1----easy                                     ||\n\
                              ||                                               ||\n\
                              || 2----normal                                   ||\n\
                              ||                                               ||\n\
                              || 3----hard                                     ||\n\
                              ||                                               ||\n\
                              || 4----insane                                   ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                               -------------------------------------------------\n\
");
	int choice; char ch1;
	*succ = 0;
	//��������ĺϷ���
	while (1) {
		ch1 = getch();
		if (isdigit(ch1)) {
			if (ch1 >= '1'&&ch1 <= '4') {
				choice = ch1 - '0';
				break;
			}
		}
	}
	switch (choice) {
	case 1: {//easy:��easy�ļ��������ȡ
		FILE *fp;
		if ((fp = fopen("easy.txt", "r")) == NULL) {
			printf("                              cannot open the file \"easy.txt\"\n");
			exit(0);
		}//�õ�a�����book��succ
		fseek(fp, (19 * 9 + 2)*(rand() % 8), 0);//�ļ�ָ�����ָ��ĳһ��Ŀ�ͷ��ʵ���������Ĳ���
		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= 9; j++) {
				fscanf(fp, "%d", &a[i][j]);
				if (a[i][j] == 0) {//�����������
					book[i][j] = 1;
					*succ += 1;
				}
				else {
					book[i][j] = 0;
				}
			}
		}
		break;
	}
	case 2: {//normal
		FILE *fp;
		if ((fp = fopen("normal.txt", "r")) == NULL) {
			printf("                              cannot open the file \"normal.txt\"\n");
			exit(0);
		}//�õ�a�����book��succ
		fseek(fp, (19 * 9 + 2)*(rand() % 8), 0);
		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= 9; j++) {
				fscanf(fp, "%d", &a[i][j]);
				if (a[i][j] == 0) {//�����������
					book[i][j] = 1;
					*succ+=1;
				}
				else {
					book[i][j] = 0;
				}
			}
		}
		break;
	}
	case 3: {//hard
		FILE *fp;
		if ((fp = fopen("hard.txt", "r")) == NULL) {
			printf("                              cannot open the file \"hard.txt\"\n");
			exit(0);
		}//�õ�a�����book��succ
		fseek(fp, (19 * 9 + 2)*(rand() % 8), 0);//�ļ�ָ�����ָ��ĳһ��Ŀ�ͷ��ʵ���������Ĳ���
		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= 9; j++) {
				fscanf(fp, "%d", &a[i][j]);
				if (a[i][j] == 0) {//�����������
					book[i][j] = 1;
					*succ += 1;
				}
				else {
					book[i][j] = 0;
				}
			}
		}
		break;
	}
	case 4: {//insane
		FILE *fp;
		if ((fp = fopen("insane.txt", "r")) == NULL) {
			printf("                              cannot open the file \"insane.txt\"\n");
			exit(0);
		}//�õ�a�����book��succ
		fseek(fp, (19 * 9 + 2)*(rand() % 8), 0);//�ļ�ָ�����ָ��ĳһ��Ŀ�ͷ��ʵ���������Ĳ���
		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= 9; j++) {
				fscanf(fp, "%d", &a[i][j]);
				if (a[i][j] == 0) {//�����������
					book[i][j] = 1;
					*succ += 1;
				}
				else {
					book[i][j] = 0;
				}
			}
		}
		break;
	}
	}
}


void print_guide() {//��ӡ��Ϸ�Ĺ���
	printf("\
                               -------------------------------------------------\n\
                              || ��������                                      ||\n\
                              ||                                               ||\n\
                              ||    ������1, 2, 3...9����ո��У�ʹ��ÿһ������||\n\
                              ||ÿ�С�ÿ�С�ÿ���и�����һ�Ρ�                 ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                              ||    Ψһ��(Unique Solution) :��������(Puzzle)��||\n\
                              ||�����������֣�����ֻ����һ����������򲻱����� ||\n\
                              ||���������⡣                                   ||\n\
                              ||                                               ||\n\
                              ||���ⷽ��                                       ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                              ||�����:                                        ||\n\
                              ||                                               ||\n\
                              ||    ������ȥ�ҵ�Ԫ����Ψһ����ո񣬳�Ϊ����� ||\n\
                              ||�����ֿ���Ψһ�ո��Ϊ�����(Hidden Single)��  ||\n\
                              ||                                               ||\n\
                              ||������ :                                       ||\n\
                              ||                                               ||\n\
                              ||    �ø�λȥ��Ψһ�������֣���Ϊ����������λΨ ||\n\
                              ||һ�������ֳ�ΪΨ���(Naked Single)��           ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                               -------------------------------------------------\n\
");
	printf("                              ");
	system("pause");
	return;
}

void print_info() {//��ӡ�����ߵ���Ϣ
	printf("\
                               -------------------------------------------------\n\
                              || ������ �����Ӻ�                               ||\n\
                              ||                                               ||\n\
                              || ѧ�� : 2017211971                             ||\n\
                              ||                                               ||\n\
                              || �༶ : 2017211504                             ||\n\
                              ||                                               ||\n\
                              || ϣ����λ����ܹ����鵽������Ϸ���ص�������    ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                               -------------------------------------------------\n\
");
	printf("                              ");
	system("pause");
	return ;
}

int if_wrong(int(*a)[12], int i, int j, int in) {//if_wrong�������жϸø���������Ƿ���Ϲ���
	int count[10] = { 0 };//ͳ��ÿ�����ֳ��ֵĴ���
	//�����е����Ƿ�����ظ�
	for (int k = 1; k <= 9; k++) {
		if (a[i][k] > 0) {
			if (k != j) {//���ܽ�(i,j)�е������ϡ�
				count[a[i][k]]++;//ͳ�Ƹ����и������ֵĳ��ִ���
			}
		}
	}
	count[in]++;
	for (int k = 0; k <= 9; k++) {//�����������˶�Σ�˵�����Ϲ���
		if (count[k] > 1) {
			return 1;
		}
	}
	//�����е����Ƿ�����ظ�
	memset(count, 0, sizeof(count));
	for (int k = 1; k <= 9; k++) {
		if (a[k][j] > 0) {
			if (k != i) {//���ܽ�(i,j)�е������ϡ�
				count[a[k][j]]++;//ͳ�Ƹ����и������ֵĳ��ִ���
			}
		}
	}
	count[in]++;
	for (int k = 0; k <= 9; k++) {//�����������˶�Σ�˵�����Ϲ���
		if (count[k] > 1) {
			return 1;
		}
	}
	//���Ź����е����Ƿ�����ظ�
	memset(count, 0, sizeof(count));
	int m0, n0;//ȷ���ø��������ĸ��Ź���
	if (i <= 3) {
		m0 = 1;
	}
	else if (i <= 6) {
		m0 = 4;
	}
	else {
		m0 = 7;
	}
	if (j <= 3) {
		n0 = 1;
	}
	else if (j <= 6) {
		n0 = 4;
	}
	else {
		n0 = 7;
	}

	//ͳ�ƸþŹ����и������ֵĳ��ִ���
	for (int m = m0; m < m0 + 3; m++) {
		for (int n = n0; n < n0 + 3; n++) {
			if (a[m][n] > 0) {
				if (m != i&&n != j) {//���ܽ�(i,j)�е������ϡ�
					count[a[m][n]]++;
				}
			}
		}
	}
	count[in]++;
	for (int k = 0; k <= 9; k++) {//�����������˶�Σ�˵�����Ϲ���
		if (count[k] > 1) {
			return 1;
		}
	}
	//ִ�е��ò���˵�����Ϲ���
	return 0;
}


void show_mainpage(int (*a)[12],int(*book)[12],int curx,int cury) {//��ӡ��Ϸ�е�9*9����
	printf("                                   1   2   3    4   5   6    7   8   9\n");
	for (int i = 0; i <= 18; i++) {
		if (i == 0 || i == 18) {
			printf("                                 ---------------------------------------\n");
		}
		else if (i % 6 == 0) {
			printf("                                ||-------------------------------------||\n                                ||-------------------------------------||\n");
		}
		else if (i % 2 == 0) {
			printf("                                ||-----------||-----------||-----------||\n");
		}
		else {
			printf("                              %d ||", (i + 1) / 2);
			for (int j = 1; j <= 9; j++) {
				//��������i,j�ϣ���ӡ���ķ���
				if ((i + 1) / 2 == curx&&j == cury) {
					printf("[");
				}
				else {
					printf(" ");
				}
				if (a[(i + 1) / 2][j] > 0) {//�˴��жϸø����Ƿ�Ϊ�����ģ��ǵĻ��͸����ּ�����ɫ
					if (book[(i + 1) / 2][j] == 1) {
						color(3);
					}
					//printf(" %d", a[(i + 1) / 2][j]);
					printf("%d", a[(i + 1) / 2][j]);//
					if (book[(i + 1) / 2][j] == 1) {
						color(16);
					}
					if ((i + 1) / 2 == curx&&j == cury) {
						printf("]");
					}
					else {
						printf(" ");
					}
					printf("|");
				}
				else {
					printf(" ");
					if ((i + 1) / 2 == curx&&j == cury) {
						printf("]|");
					}
					else {
						printf(" |");
					}
				}
				if (j % 3 == 0) {
					printf("|");
				}
			}
			printf("\n");
		}
	}
	return;
}

