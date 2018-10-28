#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>

void color(short x) //自定义函根据参数改变颜色   
{
	if (x >= 0 && x <= 15)//参数在0-15的范围颜色  
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);    //只有一个参数，改变字体颜色   
	else//默认的颜色白色  
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void show_mainpage(int(*a)[12], int(*book)[12],int curx,int cury);
int if_wrong(int(*a)[12], int i, int j, int in);
int main_game(int (*a)[12],int (*book)[12],int tot,int succ) {//主游戏函数，运行游戏的主题函数
	int if_save = 1,curx = 1,cury = 1;
	while (1) {

		system("cls");
		show_mainpage(a, book, curx, cury);
		//此处判断玩家是否已经通关。若通关，则函数退出
		if (tot == succ) {
			printf("\n\n                              恭喜你已经解出来这个数独！距离大师越来越近了呢~\n");
			if_save = 0;//存档清除

			FILE *fp;
			if ((fp = fopen("if_save.txt", "w")) == NULL) {//解出数独后存档消失
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
		//进行数独基本的操作
		//首先让玩家选择继续游戏还是保存游戏
		printf("                              您要进行什么操作?\n                              1----继续游戏  2----保存文件\n");

		char choice;
		while (1) {//判断这次输入的合法性
			choice = getch();
			if (choice != '1' && choice != '2') {
				continue;
			}
			else {
				break;
			}
		}

		//若进行游戏
		int i, j; char ch;
		//此时让玩家输入要对什么格子进行操作，输入对应格子的坐标
		if (choice == '1') {
			while (1) {
				system("cls");
				show_mainpage(a, book, curx, cury);
				printf("\n                              对哪个格子进行操作？（WASD控制光标，T键即可选定）\n");
				while ((ch = getch()) != 't') {//ch为回车时
					//只有ch为w a s d 时才有效
					//光标移动
					switch (ch) {
					case 'w': {//光标上移
						if (curx > 1) {//如果不出界
							curx--;
						}
						break;
					}
					case 'a': {//左移
						if (cury > 1) {//如果不出界
							cury--;
						}
						break;
					}
					case 's': {//下移
						if (curx < 9) {//如果不出界
							curx++;
						}
						break;
					}
					case 'd': {//右移
						if (cury < 9) {//如果不出界
							cury++;
						}
						break;
					}
					}
					//打印移动后的界面
					system("cls");
					show_mainpage(a, book, curx, cury);
					printf("\n                              对哪个格子进行操作？（WASD控制光标，T键即可选定）\n");
				}
				//判断此次输入的合法性
				i = curx; j = cury;
				if ((i < 1 || i>9 || j < 1 || j>9) || book[i][j] == 0) {//若该格子不能操作时，提醒玩家再选择一次
					printf("                              这个格子不能操作哦，请重新选择。\n");
					printf("                              ");
					system("pause");
				}
				else {
					break;
				}
			}
			//若玩家的格子输入正确
			//输入该格子对应的操作（修改数还是删除数）
			printf("                              想对(%d,%d)进行什么操作？\n                              1----修改上面的数    2----删除里面的数\n", i, j);

			while (1) {//判断这次输入的合法性
				choice = getch();
				if (choice != '1' && choice != '2') {
					continue;
				}
				else {
					break;
				}
			}
			//若修改该格子上的数
			//让玩家输入修改成什么数
			if (choice == '1') {
				while (1) {
					printf("                              想修改成什么数？\n");
					int in; char ch1;
					//判断输入的合法性
					while (1) {
						
						ch1 = getch();
						//如果输入的字符为数字，则接受输入，否则不接收
						if (isdigit(ch1)) {
							in = ch1 - '0';
							break;
						}
					}
					//判断该格子修改成这一个数是否符合规则
					if (if_wrong(a,i,j,in)) {//如果不符合规则，询问玩家是否重新输入
						printf("                               %d 不能填在这里哦，重新输入一个吗?\n                              1----是   2---否\n",in);
						
						while (1) {//判断这次输入的合法性
							choice = getch();
							if (choice != '1' && choice != '2') {
								printf("                              非法输入！\n");
							}
							else {
								break;
							}
						}

						if (choice == '1') {//如果想重新输
							continue;
						}
						else {//如果不想重新输
							break;
						}
					}
					else {//如果符合规则
						if (a[i][j] == 0) {//格子中没有数的时候添加tot才会变化
							tot++;
						}
						a[i][j] = in;
						break;
					}
				}
			}
			else {//删除该格子中的数
				if (a[i][j] > 0) {//若该格子以前有数才能进行删除
					a[i][j] = 0;
					tot--;
				}
			}
		}
		//若在第一个选择中，玩家选择了保存游戏
		else {
			//进行保存操作(保存a,book,tot,succ)
			FILE *fp;
			if ((fp = fopen("save.txt", "w")) == NULL) {
				printf("                              cannot open the file \"save.txt\"\n");
				exit(0);
			}

			for (int i = 1; i <= 9; i++) {//保存a
				for (int j = 1; j <= 9; j++) {
					fprintf(fp, "%d ", a[i][j]);
					
				}
				fprintf(fp, "\n");
			}
			for (int i = 1; i <= 9; i++) {//保存book
				for (int j = 1; j <= 9; j++) {
					fprintf(fp, "%d ", book[i][j]);
				}
				fprintf(fp, "\n");
			}
			fprintf(fp, "%d\n%d", tot, succ);
			if_save = 1;
			fclose(fp);
			printf("                              保存成功！\n");
			//printf("\n%d %d", tot, succ);//***
			printf("                              是否退出游戏？\n                              1----是    2----否\n");


			while (1) {//判断这次输入的合法性
				choice = getch();
				if (choice != '1' && choice != '2') {
					continue;
				}
				else {
					break;
				}
			}
			if (choice == '1') {//退出游戏
				if ((fp = fopen("if_save.txt", "w")) == NULL) {
					printf("                              cannot open the file \"if_save.txt\"\n");
					exit(0);
				}
				fprintf(fp, "%d", if_save);
				fclose(fp);
				return if_save;
			}
			else {//不退出
				continue;
			}
			
		}
	}
}

void show_menu(int if_save) {//主菜单的显示
	printf("\
                               -------------------------------------------------\n\
                              ||                                               ||\n\
                              ||                   数独游戏                    ||\n\
                              ||                        ----By 刘子豪          ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                              ||           (请输入想要进行的操作对应的数字)    ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n");
	if (if_save) {
		printf("\
                              ||       0--------继续游戏                       ||\n");
	}
	else {
		printf("\
                              ||                                               ||\n");
	}
	printf("\
                              ||       1--------开始新游戏                     ||\n\
                              ||       2--------获取帮助                       ||\n\
                              ||       3--------制作者信息                     ||\n\
                              ||       3--------制作者信息                     ||
                              ||       4--------退出游戏                       ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                               -------------------------------------------------\n ");
}

void select_difficulty(int(*a)[12], int(*book)[12], int *succ) {//打印难度选择菜单，并抽取题目进行新的游戏
	printf("\
                               -------------------------------------------------\n\
                              || 请选择游戏的难度：                            ||\n\
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
	//检验输入的合法性
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
	case 1: {//easy:从easy文件里随机读取
		FILE *fp;
		if ((fp = fopen("easy.txt", "r")) == NULL) {
			printf("                              cannot open the file \"easy.txt\"\n");
			exit(0);
		}//得到a，求出book和succ
		fseek(fp, (19 * 9 + 2)*(rand() % 8), 0);//文件指针随机指到某一题的开头，实现随机抽题的操作
		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= 9; j++) {
				fscanf(fp, "%d", &a[i][j]);
				if (a[i][j] == 0) {//该区域可填数
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
		}//得到a，求出book和succ
		fseek(fp, (19 * 9 + 2)*(rand() % 8), 0);
		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= 9; j++) {
				fscanf(fp, "%d", &a[i][j]);
				if (a[i][j] == 0) {//该区域可填数
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
		}//得到a，求出book和succ
		fseek(fp, (19 * 9 + 2)*(rand() % 8), 0);//文件指针随机指到某一题的开头，实现随机抽题的操作
		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= 9; j++) {
				fscanf(fp, "%d", &a[i][j]);
				if (a[i][j] == 0) {//该区域可填数
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
		}//得到a，求出book和succ
		fseek(fp, (19 * 9 + 2)*(rand() % 8), 0);//文件指针随机指到某一题的开头，实现随机抽题的操作
		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= 9; j++) {
				fscanf(fp, "%d", &a[i][j]);
				if (a[i][j] == 0) {//该区域可填数
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


void print_guide() {//打印游戏的规则
	printf("\
                               -------------------------------------------------\n\
                              || 数独规则                                      ||\n\
                              ||                                               ||\n\
                              ||    将数字1, 2, 3...9填入空格中，使得每一数字在||\n\
                              ||每行、每列、每宫中各出现一次。                 ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                              ||    唯一解(Unique Solution) :数独谜题(Puzzle)按||\n\
                              ||规则填制数字，必须只能有一个结果，否则不被承认 ||\n\
                              ||是数独谜题。                                   ||\n\
                              ||                                               ||\n\
                              ||解题方法                                       ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                              ||摒除法:                                        ||\n\
                              ||                                               ||\n\
                              ||    用数字去找单元格内唯一可填空格，称为摒除法 ||\n\
                              ||，数字可填唯一空格成为摒除解(Hidden Single)。  ||\n\
                              ||                                               ||\n\
                              ||余数法 :                                       ||\n\
                              ||                                               ||\n\
                              ||    用格位去找唯一可填数字，称为余数法，格位唯 ||\n\
                              ||一可填数字成为唯余解(Naked Single)。           ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                               -------------------------------------------------\n\
");
	printf("                              ");
	system("pause");
	return;
}

void print_info() {//打印制作者的信息
	printf("\
                               -------------------------------------------------\n\
                              || 制作者 ：刘子豪                               ||\n\
                              ||                                               ||\n\
                              || 学号 : 2017211971                             ||\n\
                              ||                                               ||\n\
                              || 班级 : 2017211504                             ||\n\
                              ||                                               ||\n\
                              || 希望各位玩家能够体验到数独游戏独特的魅力！    ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                              ||                                               ||\n\
                               -------------------------------------------------\n\
");
	printf("                              ");
	system("pause");
	return ;
}

int if_wrong(int(*a)[12], int i, int j, int in) {//if_wrong函数：判断该格子填的数是否符合规则
	int count[10] = { 0 };//统计每个数字出现的次数
	//看该行的数是否存在重复
	for (int k = 1; k <= 9; k++) {
		if (a[i][k] > 0) {
			if (k != j) {//不能将(i,j)中的数算上。
				count[a[i][k]]++;//统计该行中各个数字的出现次数
			}
		}
	}
	count[in]++;
	for (int k = 0; k <= 9; k++) {//若有数出现了多次，说明不合规则
		if (count[k] > 1) {
			return 1;
		}
	}
	//看该列的数是否存在重复
	memset(count, 0, sizeof(count));
	for (int k = 1; k <= 9; k++) {
		if (a[k][j] > 0) {
			if (k != i) {//不能将(i,j)中的数算上。
				count[a[k][j]]++;//统计该行中各个数字的出现次数
			}
		}
	}
	count[in]++;
	for (int k = 0; k <= 9; k++) {//若有数出现了多次，说明不合规则
		if (count[k] > 1) {
			return 1;
		}
	}
	//看九宫格中的数是否存在重复
	memset(count, 0, sizeof(count));
	int m0, n0;//确定该格子属于哪个九宫格
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

	//统计该九宫格中各个数字的出现次数
	for (int m = m0; m < m0 + 3; m++) {
		for (int n = n0; n < n0 + 3; n++) {
			if (a[m][n] > 0) {
				if (m != i&&n != j) {//不能将(i,j)中的数算上。
					count[a[m][n]]++;
				}
			}
		}
	}
	count[in]++;
	for (int k = 0; k <= 9; k++) {//若有数出现了多次，说明不合规则
		if (count[k] > 1) {
			return 1;
		}
	}
	//执行到该步，说明符合规则
	return 0;
}


void show_mainpage(int (*a)[12],int(*book)[12],int curx,int cury) {//打印游戏中的9*9棋盘
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
				//如果光标在i,j上，打印光标的符号
				if ((i + 1) / 2 == curx&&j == cury) {
					printf("[");
				}
				else {
					printf(" ");
				}
				if (a[(i + 1) / 2][j] > 0) {//此处判断该格子是否为玩家填的，是的话就给数字加上颜色
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

