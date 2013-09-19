#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"
#include "disp.h"

char *c;

void init() {
    ;
}

void end() {
    ;
}

void getkeyval(char *key, char *val) {
    printf("Enter key: ");
    fgets(key, 1024, stdin);
    c = strchr(key, '\n');
    *c = '\0';
    printf("Enter value: ");
    fgets(val, 1024, stdin);
    c = strchr(val, '\n');
    *c = '\0';
}

void getkey(char *key) {
    printf("Enter key: ");
    fgets(key, 1024, stdin);
    c = strchr(key, '\n');
    *c = '\0';
}

void display(Table *t) {
    unsigned int s = t->size;
    while(s--) {
        if(!t->e[s]) {
            printf("%d: empty\n", s);
        } else if(!t->e[s]->key) {
            printf("%d: dummy\n", s);
        } else {
            printf("%d: %s, %s\n", s, t->e[s]->key, t->e[s]->val);
        }
    }
    printf("\n");
}

void dispval(char *val) {
    printf("Value: %s\n", val);
}

char in() {
    char *str = calloc(3, sizeof(char));
    char c;
    printf("(i)nsert, (d)elete, or (g)et? ");
    fgets(str, 3, stdin);
    c = *str;
    free(str);
    return c;
}
