#ifndef GRID_H

    #define GRID_H

    typedef struct Grid {

        int width;
        int height;

        int *cells;

    } Grid;

    Grid *grid_create(int width, int height);

    void grid_destroy(Grid *grid);

#endif /* GRID_H */