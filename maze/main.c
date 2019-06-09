#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "maze.h"

int main() {

  printf("====================== Question 1 ======================\n\n");

  char **maze;
  int height, width;

  printf("Loading simple maze...");
  /* loads the maze from the file "simple.txt" and sets height and width */
  maze = load_maze("simple.txt", &height, &width);
  assert(maze);
  printf(" done (height = %d, width = %d).\n\n", height, width);
  /* For bonus */
  /*
  printf("Printing simple maze:\n");
  print_maze(maze,height,width);
  */
  printf("\n");

  printf("====================== Question 1 ======================\n\n");

  int row = 0, column = 0;
  printf("Finding the entrance:\n");
  find_marker('>', maze, height, width, &row, &column);
  printf("The entrance is at row %d column %d\n\n", row, column);

  printf("Finding the exit:\n");
  find_marker('X', maze, height, width, &row, &column);
  printf("The exit is at row %d column %d\n\n", row, column);

  printf("====================== Question 2 ======================\n\n");

  printf("The move sequence 'EEEEESEENN' is ");
  if (!valid_solution("EEEEESEENN", maze, height, width))
    printf("NOT ");
  printf("a solution to the maze\n\n");

  printf("The move sequence 'EEEEEEEESSSSSS' is ");
  if (!valid_solution("EEEEEEEESSSSSS", maze, height, width))
    printf("NOT ");
  printf("a solution to the maze\n\n");

  printf("The move sequence 'ESSSSSSEEEEEEE' is ");
  if (!valid_solution("ESSSSSSEEEEEEE", maze, height, width))
    printf( "NOT ");
  printf("a solution to the maze\n\n");

  printf("====================== Question 3 ======================\n\n");

  /* an easy example with a known solution */
  printf("A path through the maze from '>' to 'X' is: \n");
  printf("%s\n\n",find_path(maze, height, width, '>', 'X'));

  /* For bonus */
  /*
  printf("The path is shown below:\n");
  print_maze(maze, height, width);
  printf("\n");
  */

  /* an impossible example - should return "no solution" */
  free_maze(maze, height);
  maze = load_maze("simple.txt", &height, &width);
  assert(maze);

  printf("A path through the maze from '>' to 'U' is: \n");
  printf("%s\n\n",find_path(maze, height, width, '>', 'U'));

  /* find the path from the entrance to the middle of the Hatfield House maze */
  free_maze(maze, height);
  maze = load_maze("hatfield.txt", &height, &width);
  assert(maze);

  /* For bonus */
/*
  printf("And now the Hatfield House maze:\n");
  print_maze(maze, height, width);
  printf("\n");
*/
  
  printf("A path through the maze from '>' to 'M' is:\n");
  printf("%s\n\n",find_path(maze, height, width, '>', 'M'));

  /* For bonus */
/*
  printf("The path is shown below:\n");
  print_maze(maze, height, width);
  printf("\n");
*/

  /* find the path from the middle to the exit of the Hatfield House maze */
  free_maze(maze, height);
  maze = load_maze("hatfield.txt", &height, &width);
  assert(maze);

  printf("A path through the maze from 'M' to 'X' is:\n");
  printf("%s\n\n",find_path(maze, height, width, 'M', 'X'));
  
  /* For bonus */
/*
  printf("The path is shown below:\n");
  print_maze(maze, height, width);
  printf("\n");
*/

  printf("======================= The End ========================\n\n");

  return 0;
}
