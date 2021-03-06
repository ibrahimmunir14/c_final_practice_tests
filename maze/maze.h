#ifndef MAZE_H
#define MAZE_H

const bool SIMPLE_PRINT = false;

char **load_maze(const char *filename, int *height, int *width);
void get_dimensions(FILE *file, int *height, int *width);
char **allocate_2D_array(int rows, int columns);
void populate_2D_array(FILE *file, char **array, int rows, int columns);
bool find_marker(char ch, char **maze, int height, int width, int *row, int *column);
bool valid_solution(const char *path, char **maze, int height, int width);
char *find_path(char **maze, int height, int width, char start, char end);
bool find_path_helper(char **maze, int height, int width, int row, int col, char end, char** path, int path_pos);
void free_maze(char **maze, int rows);
void print_maze(char **maze, int height, int width);

#endif