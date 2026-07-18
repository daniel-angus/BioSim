#include <stdlib.h>
#include "grid.h"

/**
 * @brief Creates a new grid with the specified width and height.
 * 
 * @param width The width of the grid.
 * @param height The height of the grid.
 * 
 * @return A pointer to the newly created grid, or NULL if the
 *         dimensions are invalid or memory allocation fails.
 */
Grid *grid_create(int width, int height) {

    if (width <= 0 || height <= 0) {
        return NULL;
    }

    Grid *grid = calloc(1, sizeof *grid);
    if (grid == NULL) {
        return NULL;
    }

    grid->width = width;
    grid->height = height;

    grid->cells = calloc(width * height, sizeof *grid->cells);
    if (grid->cells == NULL) {
        grid_destroy(grid); // Clean up partially constructed grid.
        return NULL;
    }

    return grid;
}

/**
 * @brief Frees all memory associated with the grid.
 * 
 * @param grid A pointer to the grid to be destroyed. may be NULL, in which case the function does nothing.
 */
void grid_destroy(Grid *grid) {

    if (grid == NULL) {
        return;
    }
    
    free(grid->cells);
    free(grid);
}