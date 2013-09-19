#define TESTING
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

void test_hash_distribution() {
    int * buckets = calloc(16, sizeof(int));
    char key [3];
    key[2] = 0;
    key[0] = 65;
    int total=0;
    unsigned char i;
    unsigned char j;
    for(j = 32; j <= 127 ; j ++)
    for(i = 32; i <= 127 ; i ++){
      key[0]=i;
      key[1]=j;
      buckets[hash(key)%16]++;
      total++;
    }
    for(i = 0 ; i < 16 ; i++){
      printf("%2i: %4i  (%10f%%)\n", i, buckets[i], buckets[i]*100.0/total);
    }
}

int main(int argc, char **argv) {
    test_hash_distribution();
}
