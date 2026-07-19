#ifndef RENDERER_H
#define RENDERER_H

#include "grid.h"
void renderer_delay(unsigned int milliseconds);

int renderer_init(int width, int height, int cell_size);

int renderer_should_close(void);

int renderer_draw(const Grid *grid);

void renderer_shutdown(void);

#endif /* RENDERER_H */