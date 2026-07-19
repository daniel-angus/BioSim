/*
 * ============================================================================
 *  BioSim
 *  A Cellular Automata Framework for Computational Biology
 * ============================================================================
 *
 *  Author      : Daniel Angus AMIMA
 *  Repository  : https://github.com/jumblecat/BioSim
 *  License     : MIT
 *  Version     : 0.1.0
 *  Created     : July 2026
 *      
 * ----------------------------------------------------------------------------
 *
 *  The project aims to provide a modular, extensible simulation engine capable
 *  of modelling a wide range of biological phenomena, including:
 *
 *      > Tumour growth
 *      > Viral infection
 *      > Bacterial colonies
 *      > Wound healing
 *      > Stem cell differentiation
 *      > Immune response
 *
 *  The core engine is completely model-agnostic. Biological models are
 *  implemented as independent modules defining their own cell types, state
 *  variables, and update rules.
 *
 *  Long-term goals include:
 *
 *      > Diffusion of signalling molecules and nutrients
 *      > Stochastic cell behaviour
 *      > Parallel execution
 *      > 3D simulations
 *      > Parameter fitting
 *      > Real-time visualisation
 *      > Python bindings for analysis
 *
 *  The project is intended both as an educational resource for mathematical
 *  biology and as a foundation for more advanced computational biology
 *  simulations.
 *
 * ----------------------------------------------------------------------------
 */

#include <stdio.h>
#include "grid.h"

int main(void) {

    Grid *grid = grid_create(10, 10);
    if (grid == NULL) {
        fprintf(stderr, "Failed to create grid\n");
        return 1;
    }

    printf("%d\n", grid->width);
    printf("%d\n", grid->height);

    grid_fill(grid, 1);
    grid_print(grid);

    grid_destroy(grid);

    return 0;
}