#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

char *createCommand(size_t size) {
    char *cmd = (char *) malloc(size * sizeof(char));
    if (cmd == NULL) {
        perror("malloc failed.");
        exit(EXIT_FAILURE);
    }
    return cmd;
}

char **createCommands(int n) {
    char** cmds = (char **) calloc(n, sizeof(char *));
    if (cmds == NULL) {
        perror("malloc failed.");
        exit(EXIT_FAILURE);
    }
    return cmds;
}

char *getCommand(size_t size) {
    printf("> ");
    fflush(stdout);
    char *cmd = createCommand(size);
    fgets(cmd, size, stdin);
    int i = 0;
    for (; cmd[i] != '\n'; i++);
    cmd[i] = '\0';
    fflush(stdin);
    return cmd;
}

char **getCommands(int n, size_t size) {
    char **cmds = createCommands(n);
    for (int i = 0; i < n; i++) {
        char *cmd = getCommand(size);
        cmds[i] = cmd;
    }
    return cmds;
}

void printCommands(char **commands, int n) {
    assert (commands != NULL);
    for (int i = 0; i < n; i++) {
        assert (commands[i] != NULL);
        printf("%s\n", commands[i]);
    }
}

void freeCommands(char **commands, int n) {
    assert (commands != NULL);
    for (int i = 0; i < n; i++) {
        assert (commands[i] != NULL);
        free(commands[i]);
    }
    free(commands);
}

int stringLength(char *string) {
    int size = 0;
    while (*(string++) != '\0') {
        size++;
    }
    return ++size;
}

char *stringCat(char *string1, char *string2) {
    char *result = malloc(sizeof(char) * (stringLength(string1) + stringLength(string2) - 1));
    char *ptr = result;
    while (*string1 != '\0') {
        *(ptr++) = *(string1++);
    }
    while (*string2 != '\0') {
        *(ptr++) = *(string2++);
    }
    *ptr = '\0';
    return result;
}

void printCommandLengths(char **commands, int n) {
    assert (commands != NULL);
    for (int i = 0; i < n; i++) {
        assert (commands[i] != NULL);
        printf("(Length %i) %s\n", stringLength(commands[i]), commands[i]);
    }
}

void printCommandConcat(char **commands, int n) {
    assert (commands != NULL);
    char *result = commands[0];
    for (int i = 1; i < n; i++) {
        assert (commands[i] != NULL);
        result = stringCat(result, commands[i]);
    }
    printf("%s", result);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        perror("Incorrect number of arguments.");
        return EXIT_FAILURE;
    }
    int numCommands = atoi(argv[1]);
    if (numCommands < 3) {
        perror("Number of commands must be 3 or more.");
        return EXIT_FAILURE;
    }
    int commandSize = atoi(argv[2]);
    if (commandSize < 50) {
        perror("Maximum size of command must be 50 or more.");
        return EXIT_FAILURE;
    }
    char **cmds = getCommands(numCommands, commandSize);
    printf("\n");
    printCommands(cmds, numCommands);
    printf("\n");
    printCommandLengths(cmds, numCommands);
    printf("\n");
    printCommandConcat(cmds, numCommands);
    freeCommands(cmds, numCommands);
}