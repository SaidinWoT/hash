#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"

#define SIZE 8
#define LOAD 0.45
#define COLLIDE(i,s) (((5 * i) + 1) % s)

void hset(Table *t, char *k, char *v);

Table *halloc(unsigned int size) {
    Table *t = malloc(sizeof(Table));
    t->size = size;
    t->load = LOAD;
    t->entries = 0;
    t->e = calloc(size, sizeof(Entry *));
    return t;
}

void hresize(unsigned int size, Table *t) {
    Entry **e = t->e;
    unsigned int s = t->size;
    t->size = size;
    t->entries = 0;
    t->e = calloc(size, sizeof(Entry *));
    while(s--) {
        if(e[s]) {
            hset(t, e[s]->key, e[s]->val);
        }
    }
}

unsigned int hash(const char *k) {
    // http://www.cse.yorku.ca/~oz/hash.html
    unsigned int hash = 0;
    for(; *k; ++k) { 
        hash = (hash << 5 + hash) ^ *k; 
        //hash(i) = hash(i-1) * 33 ^ str[i]
    } 
    return hash; 
} 

unsigned int _get_index_by_key(Table *t, char *k) {
    unsigned int i = hash(k) % t->size;
    while(t->e[i] && strcmp(t->e[i]->key, k)) {
        t->e[i]->col = true;
        i = COLLIDE(i,t->size);
    }
    return i;
}

char *hget(Table *t, char *k) {
    Entry *e = t->e[_get_index_by_key(t, k)];
    return (e && e->val) ? e->val : "";
}

void hset(Table *t, char *k, char *v) {
    Entry *e;
    unsigned int i = _get_index_by_key(t, k);
    if(!t->e[i]) {
        t->e[i] = calloc(1, sizeof(Entry));
    };
    e = t->e[i];
    if(!e->key) {
        e->key = calloc(BUFSIZ, sizeof(char));
        e->val = calloc(BUFSIZ, sizeof(char));
        strcpy(e->key, k);
        ++t->entries;
    }
    strcpy(e->val, v);
    if(t->entries / (double)t->size > t->load) {
        hresize(t->size * 2, t);
    }
}

void hdel(Table *t, char *k) {
    unsigned int i = _get_index_by_key(t, k);
    Entry *e, *f;
    e = f = t->e[i];
    char *key, *val;
    if(t->e[i] && !strcmp(t->e[i]->key, k)) {
        --t->entries;
        t->e[i] = NULL;
        if(t->size > SIZE && t->entries / (double)(t->size / 2) < t->load) {
            hresize(t->size / 2, t);
        } else {
            while(e->col) {
                i = COLLIDE(i,t->size);
                if(!t->e[i]) {
                    break;
                }
                e = t->e[i];
                t->e[i] = NULL;
                hset(t, e->key, e->val);
                --t->entries;
            }
        }
        free(f->key);
        free(f->val);
        free(f);
    }
}

Table *makeTable() {
    return halloc(SIZE);
}

void freeTable(Table *t) {
    while(t->size--) {
        if(t->e[t->size]) {
            free(t->e[t->size]->key);
            free(t->e[t->size]->val);
        }
        free(t->e[t->size]);
    }
    free(t->e);
    free(t);
}
