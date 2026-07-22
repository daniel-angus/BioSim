#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "grid.h"
struct Grid {
    int width;
    int height;

    int *cells;
};

Grid *grid_create(int width, int height) {
    if (width <= 0 || height <= 0) {
        return NULL;
    }

    if ((size_t)width > SIZE_MAX / (size_t)height) {
        return NULL;
    }

    size_t cell_count = (size_t)width * (size_t)height;

    Grid *grid = calloc(1, sizeof *grid);
    if (grid == NULL) {
        return NULL;
    }

    grid->width = width;
    grid->height = height;

    grid->cells = calloc(cell_count, sizeof *grid->cells);
    if (grid->cells == NULL) {
        grid_destroy(grid);
        return NULL;
    }

    return grid;
}

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
static size_t grid_index(const Grid *grid, int x, int y) {
    return (size_t)y * grid->width + x;
}

int grid_set(Grid *grid, int x, int y, int value) {
    if (grid == NULL || x < 0 || x >= grid->width || y < 0 || y >= grid->height) {
        return 0;
    }

    grid->cells[grid_index(grid, x, y)] = value;
    return 1;
}

int grid_get(const Grid *grid, int x, int y, int *value) {
    if (grid == NULL || x < 0 || x >= grid->width || y < 0 || y >= grid->height || value == NULL) {
        return 0;
    }

    *value = grid->cells[grid_index(grid, x, y)];
    return 1;
}

int grid_fill(Grid *grid, int value) {
    if (grid == NULL) {
        return 0;
    }

    size_t cell_count = (size_t)grid->width * grid->height;

    for (size_t i = 0; i < cell_count; ++i) {
        grid->cells[i] = value;
    }

    return 1;
}

int grid_clear(Grid *grid) {
    return grid_fill(grid, 0);
}   

int grid_width(const Grid *grid) {
    if (grid == NULL) {
        return -1; // Return -1 to indicate an error.
    }
    return grid->width;
}

int grid_height(const Grid *grid) {
    if (grid == NULL) {
        return -1; // Return -1 to indicate an error.
    }
    return grid->height;
}

Grid *grid_copy(const Grid *grid) {
    if (grid == NULL) {
        return NULL;
    }

    Grid *copy = grid_create(grid->width, grid->height);
    if (copy == NULL) {
        return NULL;
    }

    size_t cell_count = (size_t)grid->width * (size_t)grid->height;

    memcpy(copy->cells,
           grid->cells,
           cell_count * sizeof *grid->cells);

    return copy;
}

int grid_copy_into(Grid *destination, const Grid *source) {
    if (destination == NULL || source == NULL) {
        return 0;
    }

    if (destination->width != source->width ||
        destination->height != source->height) {
        return 0;
    }

    size_t cell_count =
        (size_t)source->width * (size_t)source->height;

    memcpy(
        destination->cells,
        source->cells,
        cell_count * sizeof *source->cells
    );

    return 1;
}

int grid_print(const Grid *grid) {
    if (grid == NULL) {
        return 0;
    }

    for (int y = 0; y < grid->height; ++y) {
        for (int x = 0; x < grid->width; ++x) {
            printf("%d%s",
                   grid->cells[grid_index(grid, x, y)],
                   x == grid->width - 1 ? "" : " ");
        }

        putchar('\n');
    }

    return 1;
}

int grid_count_neighbours(const Grid *grid, int x, int y) {
    int count = 0;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <=1 ; dy++) {

            if (dx==0 && dy ==0) {
                continue;
            }

            int nx = x + dx;
            int ny = y + dy;

            int value;

            if (grid_get(grid, nx, ny, &value) && value == 1) {
                count++;
            }
        }
    }

    return count;
}

int grid_step(Grid *grid, const LifeRule *rule) {

    if (grid == NULL || rule == NULL) {
        return 0;
    }

    Grid *next = grid_create(grid_width(grid), grid_height(grid));

    if (next == NULL) {
        return 0;
    }

    for (int x = 0; x < grid_width(grid); x++) {
        for (int y = 0; y < grid_height(grid); y++) {
            int neighbours = grid_count_neighbours(grid, x, y);
            int current_value;
            int next_value;

            if (!grid_get(grid, x, y, &current_value)) {
                grid_destroy(next);
                return 0;
            }

            if (current_value != 0) {
                next_value = rule->survive[neighbours];
            } else {
                next_value = rule->birth[neighbours];
            }

            if (!grid_set(next, x, y, next_value)) {
                grid_destroy(next);
                return 0;
            }
        }
    }

    if (!grid_copy_into(grid, next)) {
        grid_destroy(next);
        return 0;
    }

    grid_destroy(next);
    return 1;

}