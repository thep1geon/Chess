#ifndef __SHAPES_H
#define __SHAPES_H

#include <SDL2/SDL.h>

#include "./color.h"
#include "./types.h"

typedef struct {
    vec2 topLeft;
    i32 width, height;
    Color color;
} Rect;

Rect newRect(vec2 topLeft, i32 width, i32 height, Color color);
void drawFillRect(SDL_Renderer* renderer, Rect rect);

#endif  //__SHAPES_H
