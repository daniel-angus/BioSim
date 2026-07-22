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
#include <stdbool.h>

#include "grid.h"
#include "liferule.h"
#include "renderer.h"

int main(void) {
    const int grid_width_cells = 100;
    const int grid_height_cells = 100;
    const int cell_size = 8;
    const int FPS = 20;

    Grid *grid = grid_create(
        grid_width_cells,
        grid_height_cells
    );

    if (grid == NULL) {
        fprintf(stderr, "Failed to create grid\n");
        return 1;
    }

    LifeRule rule;

    printf("Parsing rule...\n");
    if (!rule_parse("B3/S23", &rule)) {
        fprintf(stderr, "Failed to parse life rule.\n");
        renderer_shutdown();
        grid_destroy(grid);
        return 1;
    }
    printf("Rule parsed successfully.\n");

    /*
     * A simple glider.
     */
    grid_set(grid, 51, 50, 1);
    grid_set(grid, 52, 51, 1);
    grid_set(grid, 50, 52, 1);
    grid_set(grid, 51, 52, 1);
    grid_set(grid, 52, 52, 1);

    printf("Initialising renderer...\n");
    if (!renderer_init(
            grid_width_cells * cell_size,
            grid_height_cells * cell_size,
            cell_size)) {
        fprintf(stderr, "Renderer initialisation failed.\n");
        grid_destroy(grid);
        return 1;
    }
    printf("Renderer initialised successfully.\n");

    bool quit = false;
    bool playing = false;

    while (!quit) {
        RendererEvent event = renderer_handle_events();


        switch (event.type) {
            case RENDERER_EVENT_FAIL: {
                quit = true;
                fprintf(stderr, "Failed to render event.\n");
                break;
            }
            case RENDERER_EVENT_QUIT: {
                quit = true;
                break;
            }
            case RENDERER_EVENT_STEP: {
                if (!grid_step(grid, &rule)) {
                    quit = true;
                }
                break;
            }
            case RENDERER_EVENT_TOGGLE_PLAY: {
                playing = !playing;
                break;
            }
            case RENDERER_EVENT_CLICK: {
                int value;

                if (grid_get(grid, event.x, event.y, &value)) {
                    if (!grid_set(grid, event.x, event.y, !value)) {
                        quit = true;
                    }
                }
                break;
            }
            case RENDERER_EVENT_RULE_CONWAY: {
                if (!rule_parse("B3/S23", &rule)) {
                    quit = true;
                }
                break;
            }
            case RENDERER_EVENT_RULE_HIGHLIFE: {
                if (!rule_parse("B36/S23", &rule)) {
                    quit = true;
                }
                break;
            }
            case RENDERER_EVENT_RULE_SEEDS: {
                if (!rule_parse("B2/S", &rule)) {
                    quit = true;
                }
                break;
            }
            case RENDERER_EVENT_RULE_CORAL: {
                if (!rule_parse("B3/S45678", &rule)) {
                    quit = true;
                }
                break;
            }
            case RENDERER_EVENT_NONE: {
                break;
            }
        }

        if (quit) {
            break;
        }

        if (playing) {
            if (!grid_step(grid, &rule)) {
                break;
            }
        }

         if (!renderer_draw(grid)) {
            break;
        }

        unsigned int frame_delay = 1000 / FPS;
        renderer_delay(frame_delay);
    }

    renderer_shutdown();
    grid_destroy(grid);
    printf("Renderer closed successfully.\n");

    return 0;
}
