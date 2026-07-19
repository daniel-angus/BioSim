#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_timer.h>

#include "renderer.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static int cell_size = 0;

int renderer_init(int width, int height, int requested_cell_size)
{
    if (width <= 0 || height <= 0 || requested_cell_size <= 0) {
        return 0;
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 0;
    }

    if (!SDL_CreateWindowAndRenderer(
            "BioSim — Game of Life",
            width,
            height,
            0,
            &window,
            &renderer)) {
        fprintf(stderr,
                "SDL_CreateWindowAndRenderer failed: %s\n",
                SDL_GetError());

        SDL_Quit();
        return 0;
    }

    cell_size = requested_cell_size;
    return 1;
}

int renderer_should_close(void)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            return 1;
        }
    }

    return 0;
}

void renderer_delay(unsigned int milliseconds)
{
    SDL_Delay(milliseconds);
}

int renderer_draw(const Grid *grid)
{
    if (grid == NULL || renderer == NULL) {
        return 0;
    }

    /* White background: dead cells. */
    if (!SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255)) {
        return 0;
    }

    if (!SDL_RenderClear(renderer)) {
        return 0;
    }

     /* Very faint grey grid lines. */
    if (!SDL_SetRenderDrawColor(renderer, 225, 225, 225, 255)) {
        return 0;
    }

    int width_pixels = grid_width(grid) * cell_size;
    int height_pixels = grid_height(grid) * cell_size;

    for (int x = 0; x <= grid_width(grid); ++x) {
        float pixel_x = (float)(x * cell_size);

        if (!SDL_RenderLine(
                renderer,
                pixel_x,
                0.0f,
                pixel_x,
                (float)height_pixels)) {
            return 0;
        }
    }

    for (int y = 0; y <= grid_height(grid); ++y) {

        float pixel_y = (float)(y * cell_size);

        if (!SDL_RenderLine(
                renderer,
                0.0f,
                pixel_y,
                (float)width_pixels,
                pixel_y)) {
            return 0;
        }
    }

    /* Black rectangles: living cells. */
    if (!SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255)) {
        return 0;
    }

    for (int y = 0; y < grid_height(grid); ++y) {
        for (int x = 0; x < grid_width(grid); ++x) {
            int value;

            if (!grid_get(grid, x, y, &value)) {
                return 0;
            }

            if (value == 0) {
                continue;
            }

            SDL_FRect cell = {
                .x = (float)(x * cell_size),
                .y = (float)(y * cell_size),
                .w = (float)cell_size,
                .h = (float)cell_size
            };

            if (!SDL_RenderFillRect(renderer, &cell)) {
                return 0;
            }
        }
    }

    SDL_RenderPresent(renderer);
    return 1;
}

void renderer_shutdown(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    renderer = NULL;
    window = NULL;
    cell_size = 0;

    SDL_Quit();
}