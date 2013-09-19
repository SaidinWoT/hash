#ifndef __HASH
#define __HASH

#include <stdbool.h>

typedef struct _entry {
    char *key;
    char *val;
    bool col;
} Entry;

typedef struct _table {
    unsigned int size, entries;
    float load;
    Entry **e;
} Table;

Table *makeTable();
void freeTable(Table *);

void hset(Table *t, char *key, char *value);
void hdel(Table *t, char *key);
char *hget(Table *t, char *key);

#endif /* !__HASH */
