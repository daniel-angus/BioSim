#ifndef RENDERER_H
#define RENDERER_H

#include "grid.h"

typedef enum {
    RENDERER_EVENT_FAIL,
    RENDERER_EVENT_QUIT,
    RENDERER_EVENT_NONE,
    RENDERER_EVENT_STEP,
    RENDERER_EVENT_TOGGLE_PLAY,
    RENDERER_EVENT_CLICK
} RendererEventType;

typedef struct {
    RendererEventType type;
    int x;
    int y;
    // other values for events here (event handler needs sentinels)
} RendererEvent;

void renderer_delay(unsigned int milliseconds);

int renderer_init(int width, int height, int cell_size);

RendererEvent renderer_handle_events(void);

int renderer_draw(const Grid *grid);

void renderer_shutdown(void);

#endif /* RENDERER_H */