#ifndef GRID_H

    #define GRID_H

    typedef struct Grid {

        int width;
        int height;

        int *cells;

    } Grid;

    Grid *grid_create(int width, int height);

    void grid_destroy(Grid *grid);

    int grid_set(Grid *grid, int x, int y, int value);

    int grid_get(const Grid *grid, int x, int y, int *value);

    int grid_fill(Grid *grid, int value);

    int grid_clear(Grid *grid);

    int grid_width(const Grid *grid);

    int grid_height(const Grid *grid);

#endif /* GRID_H */