#ifndef __BOARD_H
#define  __BOARD_H

#include "pieces.h"
#include "types.h"
#include "consts.h"
#include "gamestate.h"

// Rotate the board for the next player. This way the player's whose turn it is,
// has their pieces on the bottom of the screen
void rotateBoard(GameState* state);

// Swaps the two pieces in the GameState's swap buffer
void movePieces(GameState* state);

#endif  //__BOARD_H
