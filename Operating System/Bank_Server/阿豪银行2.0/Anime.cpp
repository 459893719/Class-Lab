#include "Anime.h"
#include <stdio.h>

void anime1(IMAGE* people, int clothes) {
    char s[25];
    sprintf(s, "./images/customer%d3.jpg", clothes);
    loadimage(people, s, 26, 48, true);
    int y0 = HEIGHT - CELL * 3 - PEOPLE_HEIGHT + 4;
    BeginBatchDraw();
    for (int x = -CELL; x <= CELL*3; x++) {
        putimage(x, y0, people);
        FlushBatchDraw();
        Sleep(7);
    }
    EndBatchDraw();

    s[18] = '2';
    loadimage(people, s, 26, 48, true);
    putimage(CELL * 3, y0, people);
    Sleep(1000);
}

void anime2(IMAGE* people, int clothes) {
    int y0 = HEIGHT - CELL * 3 - PEOPLE_HEIGHT + 4;
    char s[25];
    sprintf(s, "./images/customer%d3.jpg", clothes);
    loadimage(people, s, 26, 48, true);
    putimage(CELL * 3, y0, people);

    BeginBatchDraw();
    for (int x = CELL*3; x <= CELL * 28; x++) {
        putimage(x, y0, people);
        FlushBatchDraw();
        Sleep(7);
    }
    EndBatchDraw();
}

void anime3(IMAGE* people, int number, int clothes) {
    char s[25];
    sprintf(s, "./images/customer%d1.jpg", clothes);
    int y0 = HEIGHT - CELL * 10 - PEOPLE_HEIGHT - 8;
    loadimage(people, s, 26, 48, true);
    BeginBatchDraw();
    for (int x = CELL * 28; x >= CELL * (6 * number - 2); x--) {
        putimage(x, y0, people);
        FlushBatchDraw();
        Sleep(7);
    }
    EndBatchDraw();
    s[18] = '2';
    loadimage(people, s, 26, 48, true);
    int x0 = CELL * (6 * number - 2);
    BeginBatchDraw();
    for (int y = y0; y >= HEIGHT - CELL * 13 - PEOPLE_HEIGHT; y--) {
        putimage(x0, y, people);
        FlushBatchDraw();
        Sleep(7);
    }
    EndBatchDraw();
}

void anime4(IMAGE* people, int number, int clothes) {
    int x0 = CELL * (6 * number - 2);
    int y0 = HEIGHT - CELL * 10 - PEOPLE_HEIGHT - 8;
    char s[25];
    sprintf(s, "./images/customer%d0.jpg", clothes);
    loadimage(people, s, 26, 48, true);

    BeginBatchDraw();
    for (int y = HEIGHT - CELL * 13 - PEOPLE_HEIGHT; y <= y0; y++) {
        putimage(x0, y, people);
        FlushBatchDraw();
        Sleep(7);
    }
    EndBatchDraw();

    s[18] = '1';
    loadimage(people, s, 26, 48, true);
    BeginBatchDraw();
    for (int x = x0; x >= -CELL; x--) {
        putimage(x, y0, people);
        FlushBatchDraw();
        Sleep(7);
    }
    EndBatchDraw();
}


