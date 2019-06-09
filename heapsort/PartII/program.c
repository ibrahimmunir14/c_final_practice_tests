#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *derived_lookup_table(char *);

int contains(char *, char);

int main(void) {

    char *s = "attack";

    printf("The initial word is: %s\n", s);

    char *table = derived_lookup_table(s);

    printf("Derived lookup table: %s\n\n", table);

    // must free the table since it was allocated memory in heap
    free(table);

    return EXIT_SUCCESS;
}

char *derived_lookup_table(char *s) {

    // malloc the correct size : sizeof gives pointer size
    //char *o_out = malloc(sizeof(s));
    char *o_out = (char *) malloc(strlen(s));

    if (o_out == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // o_end is a pointer, no need for malloc
    //char *o_end = malloc(sizeof(s));
    char *o_end = o_out;

    for (; *s != '\0'; ++s) {
        if (!contains(o_out, *s)) {
            *o_end++ = *s;
        }
    }
    // terminate with a null character
    *o_end = '\0';

    // realloc needs pointer to block to be resized
    //char *out = realloc(out, o_end - o_out + 1);
    char *out = realloc(o_out, o_end - o_out + 1);

    if (out == NULL) {
        perror("realloc");
        exit(EXIT_FAILURE);
    }

    return out;

}


int contains(char *s, char c) {

    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == c) {
            return 1;
        }
    }

    return 0;
}
