#include <ncurses.h>
#include <stdlib.h>
#include "hash.h"

#define DISP 8

Table *t;
char *key, *val;

void initDisp() {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    mvprintw(0, 0, "(i)nsert, (d)elete, or (g)et?");
    mvprintw(1, 0, "Key: ");
    mvprintw(2, 0, "Value: ");
    noecho();
}

void display(Table *t) {
    unsigned int i, j;
    char *key, *val, *col;
    move(3, 0);
    clrtobot();
    for(i = 0; i < t->size / DISP; ++i) {
        for(j = 0; j < (DISP / t->size ? t->size : DISP); ++j) {
            if(!t->e[i*DISP+j]) {
                key = "E";
                val = "-";
                col = "";
            } else if(!t->e[i*DISP+j]->key) {
                key = "D";
                val = "-";
                col = "";
            } else {
                key = t->e[i*DISP+j]->key;
                val = t->e[i*DISP+j]->val;
                col = t->e[i*DISP+j]->col ? "t" : "f";
            }
            mvprintw(j*2+4, i*20, "%d", i*DISP+j);
            mvprintw(j*2+4, i*20+3, "%-15s", key);
            mvprintw(j*2+5, i*20+1, "%s", col);
            mvprintw(j*2+5, i*20+3, "%-15s", val);
        }
    }
    mvprintw(21, 0, "size: %d", t->size);
    mvprintw(21, 10, "entries: %d", t->entries);
}

void set() {
    getstr(key);
    move(2, 7);
    getstr(val);
    hset(t, key, val);
}

void del() {
    getstr(key);
    hdel(t, key);
}

void get() {
    getstr(key);
    val = hget(t, key);
    mvprintw(2, 7, "%s", val);
}

int main(int argc, char **argv) {
    char opt;
    t = makeTable();
    key = calloc(BUFSIZ, sizeof(char));
    val = calloc(BUFSIZ, sizeof(char));
    initDisp();
    while((opt = getch()) != 'q') {
        move(2, 7);
        clrtoeol();
        move(1, 5);
        clrtoeol();
        echo();
        curs_set(2);
        switch(opt) {
            case 'i':
                set(t, key, val);
                break;
            case 'd':
                del(t, key);
                break;
            case 'g':
                get(t, key);
                break;
            default:
                continue;
        }
        noecho();
        curs_set(0);
        display(t);
    }
    freeTable(t);
    clear();
    endwin();
    return 0;
}
