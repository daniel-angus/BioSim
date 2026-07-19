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

    /**
     * @brief Sets the value of a cell in the grid.
     * 
     * @param grid The grid containing the cell.
     * @param x The x-coordinate of the cell.
     * @param y The y-coordinate of the cell.
     * @param value The value to set.
     * @return 1 if the operation was successful, 0 otherwise.
     */
    int grid_set(Grid *grid, int x, int y, int value);

    /**
     * @brief Gets the value of a cell in the grid.
     * 
     * @param grid The grid containing the cell.
     * @param x The x-coordinate of the cell.
     * @param y The y-coordinate of the cell.
     * @param value A pointer to store the retrieved value.
     * @return 1 if the operation was successful, 0 otherwise.
     */
    int grid_get(const Grid *grid, int x, int y, int *value);

    /**
     * @brief Fills the entire grid with a specified value.
     * 
     * @param grid The grid to be filled.
     * @param value The value to fill the grid with.
     * @return 1 if the operation was successful, 0 otherwise.
     */
    int grid_fill(Grid *grid, int value);

    /**
     * @brief Clears the grid by filling it with zeros.
     * 
     * @param grid The grid to be cleared.
     * @return 1 if the operation was successful, 0 otherwise.
     */
    int grid_clear(Grid *grid);

    /**
     * @brief Returns the width of the grid.
     * 
     * @param grid The grid for which to return the width. 
     * @return The width of the grid, or -1 if the grid is NULL.
     */
    int grid_width(const Grid *grid);

    /**
     * @brief Returns the height of the grid.
     * 
     * @param grid The grid for which to return the height.
     * @return The height of the grid, or -1 if the grid is NULL.
     */
    int grid_height(const Grid *grid);

    /**
     * @brief Creates a copy of the given grid. 
     * 
     * @param grid The grid to be copied.
     * @return Grid* A pointer to the newly created copy of the grid, or NULL if the input grid is NULL or memory allocation fails. 
     */
    Grid *grid_copy(const Grid *grid);

    /**
     * @brief Prints the grid to the standard output.
     * 
     * @param grid The grid to be printed.
     * @return 1 if the operation was successful, 0 otherwise.
     */
    int grid_print(const Grid *grid);

#endif /* GRID_H */