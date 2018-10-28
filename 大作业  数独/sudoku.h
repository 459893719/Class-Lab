#ifndef __SUDOKU_H__
#define __SUDOKU_H__

void show_mainpage(int(*a)[12], int(*book)[12],int curx,int cury);
int if_wrong(int(*a)[12], int i, int j, int in);
int main_game(int(*a)[12], int(*book)[12], int tot, int succ);
void show_menu(int if_save);
void select_difficulty(int(*a)[12], int(*book)[12], int *succ);
void print_guide();
void print_info();


#endif
