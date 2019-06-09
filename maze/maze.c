
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "maze.h"

char **load_maze(const char *filename, int *height, int *width) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("file open error in load_maze");
        exit(EXIT_FAILURE);
    }
    get_dimensions(file, height, width);
    char **maze = allocate_2D_array(*height, *width + 1);
    populate_2D_array(file, maze, *height, *width + 1);
    return maze;
}
void get_dimensions(FILE *file, int *height, int *width) {
    fseek(file, 0, SEEK_SET);
    *height = *width = 0;
    char chr = getc(file);
    while (chr != EOF) {
        if (*height == 0 && chr != '\0') { (*width)++; }
        if (chr == '\n') { (*height)++; }
        chr = getc(file);
    }
}
char **allocate_2D_array(int rows, int columns) {
    char **array = (char **) malloc(rows * sizeof(char *));
    if (!array) {
        perror("malloc failed in allocate_2D_array");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; i++) {
        array[i] = (char *) malloc(columns * sizeof(char));
        if (!array[i]) {
            perror("malloc failed in allocate_2D_array");
            freeMaze(array, rows);
            exit(EXIT_FAILURE);
        }
    }
    return array;
}
void populate_2D_array(FILE *file, char **array, int rows, int columns) {
    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < rows; i++) {
        fgets(array[i], columns, file);
    }
}

bool find_marker(char ch, char **maze, int height, int width, int *row, int *column) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (maze[i][j] == ch) {
                *row = i;
                *column = j;
                return true;
            }
        }
    }
    *row = *column = -1;
    return false;
}
bool valid_solution(const char *path, char **maze, int height, int width) {
    return NULL;
}
char *find_path(char **maze, int height, int width, char start, char end) {
    return NULL;
}

void freeMaze(char **maze, int rows) {
    if (maze) {
        for (int i = 0; i < rows; i++) {
            if (maze[i]) free(maze[i]);
        }
    }
    free(maze);
}