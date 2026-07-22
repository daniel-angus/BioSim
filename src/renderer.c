#include <stdio.h>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "renderer.h"

#define PANEL_WIDTH 300
#define PANEL_PADDING 20
#define BUTTON_HEIGHT 50
#define BUTTON_WIDTH (PANEL_WIDTH - 2 * PANEL_PADDING)
#define BUTTON_GAP 10

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static TTF_Font *font = NULL;

static int cell_size = 0;
static int grid_pixel_width = 0;
static int grid_pixel_height = 0;

typedef struct {
    SDL_FRect rect;
    const char *text;
    bool selected;
    RendererEventType event;
} Button;

static Button buttons[] = {
    {
        .text = "Conway (B3/S23)",
        .selected = true,
        .event = RENDERER_EVENT_RULE_CONWAY
    },
    {
        .text = "HighLife (B36/S23)",
        .event = RENDERER_EVENT_RULE_HIGHLIFE
    },
    {
        .text = "Seeds (B2/S)",
        .event = RENDERER_EVENT_RULE_SEEDS
    },
    {
        .text = "Coral (B3/S45678)",
        .event = RENDERER_EVENT_RULE_CORAL
    }
};
#define BUTTON_COUNT ((int)(sizeof buttons / sizeof buttons[0])) 

int renderer_init(int width, int height, int requested_cell_size) {
    if (width <= 0 || height <= 0 || requested_cell_size <= 0) {
        return 0;
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 0;
    }

    if (!TTF_Init()) {
        fprintf(stderr, "TTF_Init failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    font = TTF_OpenFont("assets/SFNS.ttf", 20);

    if (font == NULL) {
        fprintf(stderr, "TTF_OpenFont failed: %s\n", SDL_GetError());
        return 0;
    }

    // file level variable assignment
    grid_pixel_width = width;
    grid_pixel_height = height;
    cell_size = requested_cell_size;

    if (!SDL_CreateWindowAndRenderer(
            "BioSim — 2D Cellular Automata",
            (width + PANEL_WIDTH),
            height,
            0,
            &window,
            &renderer)) {
        fprintf(stderr,
                "SDL_CreateWindowAndRenderer failed: %s\n",
                SDL_GetError());
        
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    for (int i = 0; i < BUTTON_COUNT; ++i) {
        buttons[i].rect = (SDL_FRect) {
            .x = (float)(width + PANEL_PADDING),
            .y = (float)(PANEL_PADDING + i * (BUTTON_HEIGHT + BUTTON_GAP)),
            .w = (float)BUTTON_WIDTH,
            .h = (float)BUTTON_HEIGHT
        };
    }
    return 1;
}

static int draw_text(const char *text, float x, float y, SDL_Color colour) {
    SDL_Surface *surface =
        TTF_RenderText_Blended(font, text, 0, colour);

    if (surface == NULL) {
        fprintf(
            stderr,
            "TTF_RenderText_Blended failed: %s\n",
            SDL_GetError()
        );
        return 0;
    }

    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(renderer, surface);

    if (texture == NULL) {
        fprintf(
            stderr,
            "SDL_CreateTextureFromSurface failed: %s\n",
            SDL_GetError()
        );
        SDL_DestroySurface(surface);
        return 0;
    }

    SDL_FRect destination = {
        .x = x,
        .y = y,
        .w = (float)surface->w,
        .h = (float)surface->h
    };

    SDL_DestroySurface(surface);

    if (!SDL_RenderTexture(
            renderer,
            texture,
            NULL,
            &destination)) {
        SDL_DestroyTexture(texture);
        return 0;
    }

    SDL_DestroyTexture(texture);
    return 1;
}

static int draw_control_panel(int window_width, int window_height) {

    SDL_FRect panel = {
        .x = (float)window_width,
        .y = 0.0f,
        .w = (float)PANEL_WIDTH,
        .h = (float)window_height
    };

    SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
    SDL_RenderFillRect(renderer, &panel);

    SDL_Color white = {
        .r = 255,
        .g = 255,
        .b = 255,
        .a = 255
    };

    for (int i = 0; i < BUTTON_COUNT; ++i) {
        if (buttons[i].selected) {
            SDL_SetRenderDrawColor(renderer, 70, 120, 255, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        }

        if (!SDL_RenderFillRect(renderer, &buttons[i].rect)) {
            return 0;
        }

        if (!draw_text(
                buttons[i].text,
                buttons[i].rect.x + 15.0f,
                buttons[i].rect.y + 13.0f,
                white)) {
            return 0;
        }
    }

    return 1;
}

static RendererEvent make_event(RendererEventType type) {
    return (RendererEvent) {
        .type = type,
        // sentinel values
        .x = -1,
        .y = -1
    };
}

static bool point_in_rect(int x, int y, const SDL_FRect *rect) {
    return x >= rect->x &&
           x < rect->x + rect->w &&
           y >= rect->y &&
           y < rect->y + rect->h;
}

RendererEvent renderer_handle_events() {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        // shutdown event
        if (event.type == SDL_EVENT_QUIT) {
            return make_event(RENDERER_EVENT_QUIT);
        }

        // click event
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
            event.button.button == SDL_BUTTON_LEFT) {

            int mouse_x = (int)event.button.x;
            int mouse_y = (int)event.button.y;

            /* Panel clicks only */
            if (mouse_x >= grid_pixel_width) {
                for (int i = 0; i < BUTTON_COUNT; ++i) {
                    if (point_in_rect(mouse_x, mouse_y, &buttons[i].rect)) {
                        for (int j = 0; j < BUTTON_COUNT; ++j) {
                            buttons[j].selected = false;
                        }

                        buttons[i].selected = true;

                        return make_event(buttons[i].event);
                    }
                }

                return make_event(RENDERER_EVENT_NONE);
            }

            /* Grid clicks only */
            if (mouse_x >= 0 &&
                mouse_x < grid_pixel_width &&
                mouse_y >= 0 &&
                mouse_y < grid_pixel_height) {

                RendererEvent click_event = make_event(RENDERER_EVENT_CLICK);

                click_event.x = mouse_x / cell_size;
                click_event.y = mouse_y / cell_size;

                return click_event;
            }
        }

        // step event
        if (event.type == SDL_EVENT_KEY_DOWN &&
            event.key.key == SDLK_S &&
            !event.key.repeat) {
            return make_event(RENDERER_EVENT_STEP);
        }

        // play/pause event
        if (event.type == SDL_EVENT_KEY_DOWN &&
            event.key.key == SDLK_SPACE &&
            !event.key.repeat) {
            return make_event(RENDERER_EVENT_TOGGLE_PLAY);
        }

        // other events go here
    }

    return make_event(RENDERER_EVENT_NONE);
}

void renderer_delay(unsigned int milliseconds) {
    SDL_Delay(milliseconds);
}

int renderer_draw(const Grid *grid) {
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

    if (!draw_control_panel(width_pixels, height_pixels)) {
        return 0;
    }

    SDL_RenderPresent(renderer);
    return 1;
}

void renderer_shutdown(void) {
    if (font != NULL) {
        TTF_CloseFont(font);
        font = NULL;
    }
    TTF_Quit();

    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (window != NULL) {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    cell_size = 0;

    SDL_Quit();
}