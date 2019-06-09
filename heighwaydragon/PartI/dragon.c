#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "image.h"
#include "dragon.h"
#include <assert.h>

/* x, y: coordinates of turtle */
static long x, y;

/* When drawing a pixel to the image, x and y must be divided by this value.
 * This enables both the dragon curve and twin dragon to rendered without
 * clipping.
 */
static long scale;

/* drawn_pixels: the length of the path travelled. */
static long drawn_pixels;

/* direction: the current direction of the turtle. */
static vector_t direction;

/* Helper Function: performs an inplace rotation on a vector.
 * clockWise is 1 if CW rotation, - if CCW rotation.
 * rotNum is the number of times to rotate, each rotation is 45 degrees. */
static vector_t directions[8] = {{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
static void rotateVector(vector_t *vector, int clockWise, int rotNum) {
    int pos = 0;
    while (directions[pos].dx != vector->dx || directions[pos].dy != vector->dy) {
        pos++;
    }
    int index = clockWise ? (((pos-rotNum) % 8) + 8) % 8 : (((pos+rotNum) % 8) + 8) % 8;
    vector->dx = directions[index].dx;
    vector->dy = directions[index].dy;
}

/* Returns a vector that describes the initial direction of the turtle. Each
 * iteration corresponds to a 45 degree rotation of the turtle anti-clockwise.  */
vector_t starting_direction(int total_iterations)
{
  vector_t dir;
  dir.dx = 1;
  dir.dy = 0;
  rotateVector(&dir, 0, total_iterations);
  printf("Starting Direction for %i iterations: %i, %i\n\n", total_iterations, dir.dx, dir.dy);
  return dir;
}

/* Draws a pixel to dst at location (x, y). The pixel intensity is chosen as a
 * function of image size and the number of pixels drawn.
 *
 * The gray level changes over entire size of path; the pixel value oscillates
 * along the path to give some contrast between segments close to each other
 * spatially.
 */
void draw_greyscale(image_t *dst,long x, long y)
{
	assert(x < dst->width && y < dst->height);
	int level = LEVEL * drawn_pixels / (dst->height * dst->height);
	//assert(level >= 0 && level < LEVEL);
	uint8_t value;
	switch (level) {
	    case 0:
	        value = 100;
	        break;
	    case 1:
	        value = 120;
	        break;
	    case 2:
	        value = 150;
	        break;
	    case 3:
	        value = 180;
	        break;
	    case 4:
	        value = 200;
	        break;
	    default:
	        value = 255;
	}
	set_pixel(dst, x, y, value);
}
/* Iterates though the characters of str, recusively calling string_iteration()
 * until rules have been applied iterations times, or no rule is applicable.
 * and update the image.
 */
void string_iteration(image_t *dst, const char *str, int iterations)
{
    printf("str: %s, iter: %i\n", str, iterations);
    if (iterations <= 0) return;
    while (*str) { printf("   %c ", *str);
        if (*str == '+') { printf("rotated ccw\n", *str);
            rotateVector(&direction, 0, 2);
        } else if (*str == '-') { printf("rotated cw\n");
            rotateVector(&direction, 1, 2);
        } else if (*str == 'F') { printf("drew pixel\n");
            drawn_pixels++;
            draw_greyscale(dst, x / scale, y / scale);
            x += direction.dx;
            y += direction.dy;
        } else if (*str == 'X') { printf("recursing\n->\n");
            string_iteration(dst, "X+YF+", iterations - 1); printf("<-\n");
        } else if (*str == 'Y') { printf("recursing\n->\n");
            string_iteration(dst, "-FX-Y", iterations - 1); printf("<-\n");
        }
        str++;
    }

}

/* Creates an image of requested size, calls starting_direction() to compute
 * initial turtle direction then calls string_iteration() to construct the
 * image. The constructed image is saved to a file in the output directory.
 */
void dragon(long size, int total_iterations)
{
    image_t **img = malloc(sizeof(image_t *));
    image_error_t res = init_image(img, size * 1.5, size, GRAY, DEPTH);
    if (res != IMG_OK) {
        image_print_error(res);
        exit(EXIT_FAILURE);
    }
    x = size / 3;
    y = size / 3;
    scale = 1;
    direction = starting_direction(total_iterations);
    drawn_pixels = 0;
    string_iteration(*img, "FX", total_iterations);
    image_error_t res2 = image_write("output/jurassicdragon.pgm", *img, PGM_FORMAT);
    if (res2 != IMG_OK) {
        image_print_error(res2);
        exit(EXIT_FAILURE);
    }
    image_free(*img);
    free(img);
}

/* The main function. When called with an argument, this should be considered
 * the number of iterations to execute. Otherwise, it is assumed to be 9. Image
 * size is computed from the number of iterations then dragon() is used to
 * generate the dragon image. */
int main(int argc, char **argv)
{
    // rotation testing
    vector_t dir = {1, 0};
    rotateVector(&dir, 1, 1);
    assert(dir.dx == 1 && dir.dy == -1);
    rotateVector(&dir, 1, 1);
    assert(dir.dx == 0 && dir.dy == -1);
    rotateVector(&dir, 1, 1);
    assert(dir.dx == -1 && dir.dy == -1);
    rotateVector(&dir, 1, 1);
    assert(dir.dx == -1 && dir.dy == 0);
    rotateVector(&dir, 1, 1);
    assert(dir.dx == -1 && dir.dy == 1);
    rotateVector(&dir, 1, 1);
    assert(dir.dx == 0 && dir.dy == 1);
    rotateVector(&dir, 1, 1);
    assert(dir.dx == 1 && dir.dy == 1);
    rotateVector(&dir, 1, 1);
    assert(dir.dx == 1 && dir.dy == 0);
    rotateVector(&dir, 0, 3);
    rotateVector(&dir, 1, 5);
    rotateVector(&dir, 0, 2);
    assert(dir.dx == 1 && dir.dy == 0);

    //int num_iter = (argc == 2) ? atoi(argv[1]) : 9;
    //dragon(1 << num_iter, 2 * num_iter);
    dragon(pow(2, 7), 12);


}
