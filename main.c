#include <stdlib.h>
#include "hash.h"
#include "disp.h"

Table *t;
char *key, *val;

int main(int argc, char **argv) {
    char opt;
    t = makeTable();
    key = calloc(1024, sizeof(char));
    val = calloc(1024, sizeof(char));
    init();
    while((opt = in()) != 'q') {
        switch(opt) {
            case 'i':
                getkeyval(key, val);
                hset(t, key, val);
                display(t);
                break;
            case 'd':
                getkey(key);
                hdel(t, key);
                display(t);
                break;
            case 'g':
                getkey(key);
                dispval(hget(t, key));
                break;
            default:
                continue;
        }
    }
    freeTable(t);
    end();
    return 0;
}
