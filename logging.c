#include <stdlib.h>
#include <stdio.h>

struct map {
    char** keys;
    int** values;
    int num_pairs;
    int key_width;
};

typedef struct map map;

map new_map() {
    int num_pairs = 8;
    int key_width = 100;
    char** keys = (char**)malloc(num_pairs*sizeof(char*));
    for (int i=0; i<num_pairs; ++i) {
        char* key = (char*)malloc(key_width*sizeof(char));
        keys[i] = key;
    }
    int** values = (int**)malloc(num_pairs*sizeof(int*));
    for (int i=0; i<num_pairs; i++) {
        int* value = (int *)malloc(sizeof(int));
        values[i] = value;
    }
    map m = {keys, values, num_pairs, key_width};
    return m;
}

void map_to_string() {
    char** result;
    int num_strings = 0;
    // sprintf();
}

int main() {
    //map m = new_map();
    //printf("%d", 1);
    return 0;
}
