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
    int bucket_count = 16;
    int * buckets = calloc(bucket_count, sizeof(int));
    char key [4];
    key[3] = 0;
    int total=0;
    unsigned int i;
    for(i = 0; i <= 4096 ; i ++) {
      key[0]=rand()%95+32;
      key[1]=rand()%95+32;
      key[2]=rand()%95+32;
      buckets[hash(key)%bucket_count]++;
    }
    for(i = 0 ; i < bucket_count ; i++) {
      double error = buckets[i]-256;
      error = error * 12 / (bucket_count * bucket_count - 1 );
      error = error < 0? -error: error;
      printf("%2i: %4i  (deviation: %10f)\n", i, buckets[i], error);
      ASSERT(error < 2, "error above acceptable threshold (standard deviation >= 2)")
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
