#ifndef __HASH
#define __HASH

#include <stdbool.h>

typedef struct _entry {
    char *key;
    char *val;
    bool col;
} Entry;

typedef struct _table {
    Entry **e;
    float load;
    unsigned int size, entries;
} Table;

Table *makeTable();
void freeTable(Table *);

void hset(Table *t, char *key, char *value);
void hdel(Table *t, char *key);
char *hget(Table *t, char *key);

#ifdef TESTING
unsigned int hash(const char *k);
#endif /* !TESTING */
#endif /* !__HASH */
