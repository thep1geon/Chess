#ifndef __GAMESTATE_H
#define __GAMESTATE_H

#include "types.h"
#include "consts.h"
#include "pieces.h"

typedef struct GameState {
    i32   board[NUM_ROWS][NUM_COLS];

    Piece pieces[NUM_ROWS][NUM_COLS];

    vec2  clickedSquares[2];
    bool  wasSquarePressed;
} GameState;

#endif  //__GAMESTATE_H
