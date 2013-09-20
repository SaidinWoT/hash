#define TESTING
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

#define ASSERT(condition, error_msg) if(!(condition)) { printf("Error: %s\n", error_msg); return false; }
#define TEST(test_name) ASSERT(test_name(), #test_name " failed.")

void assert(bool condition, const char* error_msg) {
  if(!condition) {
    printf("Error: %s\n", error_msg);
  }
}


bool test_hash_distribution() {
    //no idea how to add a 'condition' for whether this test passes or fails
    int bucket_count = 8;
    int * buckets = calloc(bucket_count, sizeof(int));
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
      buckets[hash(key)%bucket_count]++;
      total++;
    }
    for(i = 0 ; i < bucket_count ; i++){
      printf("%2i: %4i  (%10f%%)\n", i, buckets[i], buckets[i]*100.0/total);
    }
    return true;
}

bool test_duplicate_insert_overrides() {
    Table * t = makeTable();
    hset(t, "Key", "A");
    hset(t, "Key", "B");
    char* returned = hget(t, "Key");
    ASSERT(returned != 0, "Table returned null on duplicate insert");
    ASSERT(returned[0] != 'A', "Table returned old value on duplicate insert");
    ASSERT(returned[0] == 'B', "Table returned wrong value on duplicate insert");
    freeTable(t); 
    return true;
}

bool test_remove() {
    Table * t = makeTable();
    hset(t, "Key", "A");

    char *returned = hget(t, "Key");

    ASSERT(returned != 0, "Table returned null after setting");

    hdel(t, "Key");
    
    returned = hget(t, "Key");
    //missing key returns empty string?
    ASSERT(returned[0] == 0, "Table returned non-null");

    return true;
}

int main(int argc, char **argv) {
    test_hash_distribution();
    TEST(test_duplicate_insert_overrides);
    TEST(test_remove);
    printf("All tests passed!\n");
}
