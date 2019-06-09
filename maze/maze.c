
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
            free_maze(array, rows);
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
    int row, col;
    find_marker('>', maze, height, width, &row, &col);
    while (*path) {
        // make a move
        if (*path == 'N') row--;
        if (*path == 'S') row++;
        if (*path == 'E') col++;
        if (*path == 'W') col--;
        // check where we landed
        if (row < 0 || row >= width) return false;
        if (col < 0 || col >= height) return false;
        if (maze[row][col] == 'X') return true;
        if (maze[row][col] == '|') return false;
        if (maze[row][col] == '+') return false;
        path++;
    }
    return false;
}

char *find_path(char **maze, int height, int width, char start, char end) {
    char *soln = calloc(height * width, sizeof(char));
    int start_row, start_col;
    find_marker(start, maze, height, width, &start_row, &start_col);
    soln[0] = '0';
    bool soln_found = find_path_helper(maze, height, width, start_row, start_col, end, &soln, 1);
    if (soln_found) return &soln[1];
    return "no solution";
}

// row, col indicate current position.
// path is the path we have taken so far including current position.
// path_pos is index of next path element
bool find_path_helper(char **maze, int height, int width, int row, int col, char end, char** path, int path_pos) {
    // check the square we have landed on
    if (maze[row][col] == end) return true;
    if (maze[row][col] == '|') return false;
    if (maze[row][col] == '-') return false;
    if (maze[row][col] == '+') return false;
    // at this point, maze[row][col] is a free space
    maze[row][col] = '+'; // indicate square has been seen to avoid looping back
    if (row > 0 && (*path)[path_pos - 1] != 'S') { // explore North
        (*path)[path_pos] = 'N';
        bool path_found = find_path_helper(maze, height, width, row - 1, col, end, path, path_pos + 1);
        if (path_found) return true;
        (*path)[path_pos] = ' ';
        maze[row-1][col] = '+'; // indicate no path exists from checked square
    }
    if (row < height - 1 && (*path)[path_pos - 1] != 'N') { // explore South
        (*path)[path_pos] = 'S';
        bool path_found = find_path_helper(maze, height, width, row + 1, col, end, path, path_pos + 1);
        if (path_found) return true;
        (*path)[path_pos] = ' ';
        maze[row+1][col] = '+'; // indicate no path exists from checked square
    }
    if (col > 0 && (*path)[path_pos - 1] != 'E') { // explore West
        (*path)[path_pos] = 'W';
        bool path_found = find_path_helper(maze, height, width, row, col - 1, end, path, path_pos + 1);
        if (path_found) return true;
        (*path)[path_pos] = ' ';
        maze[row][col-1] = '+'; // indicate no path exists from checked square
    }
    if (col < width - 1 && (*path)[path_pos - 1] != 'W') { // explore East
        (*path)[path_pos] = 'E';
        bool path_found = find_path_helper(maze, height, width, row, col + 1, end, path, path_pos + 1);
        if (path_found) return true;
        (*path)[path_pos] = ' ';
        maze[row][col+1] = '+'; // indicate no path exists from checked square
    }
    maze[row][col] = ' '; // reset square to a free space
    return false;
}

void free_maze(char **maze, int rows) {
    if (maze) {
        for (int i = 0; i < rows; i++) {
            if (maze[i]) free(maze[i]);
        }
    }
    free(maze);
}