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
 * @param grid A pointer to the grid to be destroyed. May be NULL, in which case the function does nothing.
 */
void grid_destroy(Grid *grid) {

    if (grid == NULL) {
        return;
    }
    
    free(grid->cells);
    free(grid);
}

/**
 * @brief Calculates the index of a cell in the grid based on its coordinates.
 * 
 * @param grid The grid containing the cell.
 * @param x The x-coordinate of the cell.
 * @param y The y-coordinate of the cell.
 * @return The index of the cell in the grid's internal array.
 */
static size_t grid_index(const Grid *grid, int x, int y)
{
    return (size_t)y * grid->width + x;
}

/**
 * @brief Sets the value of a cell in the grid.
 * 
 * @param grid The grid containing the cell.
 * @param x The x-coordinate of the cell.
 * @param y The y-coordinate of the cell.
 * @param value The value to set.
 * @return 1 if the operation was successful, 0 otherwise.
 */
int grid_set(Grid *grid, int x, int y, int value) {

    if (grid == NULL || x < 0 || x >= grid->width || y < 0 || y >= grid->height) {
        return 0;
    }

    grid->cells[grid_index(grid, x, y)] = value;
    return 1;
}

/**
 * @brief Gets the value of a cell in the grid.
 * 
 * @param grid The grid containing the cell.
 * @param x The x-coordinate of the cell.
 * @param y The y-coordinate of the cell.
 * @param value A pointer to store the retrieved value.
 * @return 1 if the operation was successful, 0 otherwise.
 */
int grid_get(const Grid *grid, int x, int y, int *value) {

    if (grid == NULL || x < 0 || x >= grid->width || y < 0 || y >= grid->height || value == NULL) {
        return 0;
    }

    *value = grid->cells[grid_index(grid, x, y)];
    return 1;
}