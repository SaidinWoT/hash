#include <ncurses.h>
#include "hash.h"
#include "disp.h"

#define DISP 8

void init() {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    mvprintw(0, 0, "(i)nsert, (d)elete, or (g)et?");
    mvprintw(1, 0, "Key: ");
    mvprintw(2, 0, "Value: ");
    noecho();
}

void end() {
    clear();
    endwin();
}

char in() {
    curs_set(0);
    noecho();
    char c = getch();
    move(1, 5);
    clrtoeol();
    move(2, 7);
    clrtoeol();
    return c;
}

void display(Table *t) {
    unsigned int i, j;
    char *key, *val, *col;
    move(3, 0);
    clrtobot();
    for(i = 0; i < t->size / DISP; ++i) {
        for(j = 0; j < (DISP / t->size ? t->size : DISP); ++j) {
            key = (t->e[i*DISP+j]) ? t->e[i*DISP+j]->key : "E";
            val = (t->e[i*DISP+j]) ? t->e[i*DISP+j]->val : "-";
            col = (t->e[i*DISP+j]) ? (t->e[i*DISP+j]->col ? "t" : "f") : "";
            mvprintw(j*2+4, i*20, "%d", i*DISP+j);
            mvprintw(j*2+4, i*20+3, "%-15s", key);
            mvprintw(j*2+5, i*20+1, "%s", col);
            mvprintw(j*2+5, i*20+3, "%-15s", val);
        }
    }
    mvprintw(21, 0, "size: %d", t->size);
    mvprintw(21, 10, "entries: %d", t->entries);
}

void dispval(char *val) {
    mvprintw(2, 7, "%s", val);
}

void getkeyval(char *key, char *val) {
    echo();
    curs_set(1);
    move(1, 5);
    getstr(key);
    move(2, 7);
    getstr(val);
}

void getkey(char *key) {
    echo();
    curs_set(1);
    move(1, 5);
    getstr(key);
}
