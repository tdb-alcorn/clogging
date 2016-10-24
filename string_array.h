/**
 * Defines the string array type which stores an array of strings in
 * consecutive blocks of memory. It is mutable: you can set items in it and
 * you can append to it. String_array's automatically handle increasing their
 * memory capacity.
 */

#include <stdlib.h>
#include <stdio.h>

char* null_ptr;  /* Using a global null_ptr reference like this is probably a
                    terrible idea. But I don't know how else to do it. The
                    null_ptr has to be declared outside the scope of a function
                    because otherwise it refers to stack memory instead of heap
                    memory and the address isn't 0x0, it's something other crazy
                    thing that gdb can't even print...

                    Probably the right thing to do is to not directly return
                    pointers from any functions but instead to mutate arguments,
                    and return an enum indicating success or failure.
                 */

struct string_array {
    char** strings;
    int length;
    int capacity;
};

typedef struct string_array string_array;

string_array* new_string_array() {
    int length = 0;
    int capacity = 8;
    char** strings = (char**)malloc(capacity*sizeof(char*));
    string_array* s = (string_array*)malloc(sizeof(string_array));
    s->strings = strings;
    s->length = length;
    s->capacity = capacity;
    return s;
}

void free_string_array(string_array* sa) {
    free(sa->strings);
    free(sa);
}

void grow(string_array* sa) {
    int old_capacity = sa->capacity;
    sa->capacity = 2*old_capacity;
    char** new_strings = (char**)malloc(sa->capacity*sizeof(char*));
    for (int i=0; i<sa->length; ++i) {
        new_strings[i] = sa->strings[i];
    }
    sa->strings = new_strings;
}

/**
 * Adds a string pointer to the string_array, doubling its capacity if
 * necessary.
 */
void append(string_array* sa, char* string) {
    if (sa->length == sa->capacity) {
        grow(sa);
    }
    sa->strings[sa->length] = string;
    sa->length++;
}

/**
 * Gets a pointer to the ith string, or returns a null pointer if i is out of
 * bounds.
 */
char* get(string_array* sa, int i) {
    if (i<sa->length && i>=0) {
        return sa->strings[i];
    }
    return null_ptr;
}

/**
 * Sets the ith string pointer and returns it if successful, or returns a null
 * pointer if i is out of bounds.
 */
char* set(string_array* sa, int i, char* val) {
    if (i<sa->length && i>=0) {
        sa->strings[i] = val;
        return val;
    }
    return null_ptr;
}

void print(string_array* sa) {
    for (int i=0; i<sa->length; ++i) {
        printf(sa->strings[i], " %s ");
    }
}

#ifdef TEST  /* Really this should check for whether TEST=string_array
                because I may use the TEST macro as a flag in other files that
                depend on this and then these tests will get added to the
                compiled output and there will be two main()s and I will be sad.
             */

void test(char* name, int prop) {
    if (prop) {
        printf(".");
        return;
    }
    printf("X\nTest failed: %s\n", name);
}


int main() {
    string_array* sa = new_string_array();
    test("new string_array has length 0", sa->length == 0);
    test("new string_array has capacity 8", sa->capacity == 8);

    char* foo_ptr = "foo";
    append(sa, foo_ptr);
    char* bar_ptr = "bar";
    append(sa, bar_ptr);
    test("sa[0] == foo", sa->strings[0] == foo_ptr);
    test("sa[1] == bar", sa->strings[1] == bar_ptr);

    for (int i=0; i<10; i++) {
        append(sa, "appended");
    }
    test("append increases length", sa->length == 12);
    test("append increase capacity", sa->capacity == 16);

    char* result;
    result = set(sa, 3, foo_ptr);
    test("set returns pointer to string", result == foo_ptr);
    test("set mutates string_array", sa->strings[3] == foo_ptr);

    test("basic get works", get(sa, 1) == bar_ptr);
    test("get works after growing string_array", get(sa, 11) != null_ptr);
    test("getting out of bounds returns null_pointer", get(sa, 100) ==
            null_ptr);

    int length = sa->length;
    result = set(sa, 15, foo_ptr);
    test("setting out of bounds returns null pointer", result == null_ptr);
    test("setting out of bounds does not mutate string_array", length ==
            sa->length);

    // cleanup
    free_string_array(sa);
    // final newline for shiny clean ouput
    printf("\n");
}

#else
int main() {
    printf("TEST not defined");
}

#endif /* TEST */
