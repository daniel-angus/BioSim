#ifndef GRID_H

    #define GRID_H

    typedef struct Grid {

        int width;
        int height;

        int *cells;

    } Grid;

    /**
     * @brief Creates a new grid with the specified width and height.
     * 
     * @param width The width of the grid.
     * @param height The height of the grid.
     * 
     * @return A pointer to the newly created grid, or NULL if the
     *         dimensions are invalid or memory allocation fails.
     */
    Grid *grid_create(int width, int height);

    /**
     * @brief Frees all memory associated with the grid.
     * 
     * @param grid A pointer to the grid to be destroyed. May be NULL, in which case the function does nothing.
     */
    void grid_destroy(Grid *grid);

    int grid_set(Grid *grid, int x, int y, int value);

    int grid_get(const Grid *grid, int x, int y, int *value);

    int grid_fill(Grid *grid, int value);

    int grid_clear(Grid *grid);

    int grid_width(const Grid *grid);

    int grid_height(const Grid *grid);

    Grid *grid_copy(const Grid *grid);

    int grid_print(const Grid *grid);


#endif /* GRID_H */