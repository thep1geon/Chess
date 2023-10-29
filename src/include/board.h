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
void movePiece(GameState* state, i32 x1, i32 y1, i32 x2, i32 y2);

bool validMove(GameState* state, Piece piece, vec2 toPos);

void highlightSquare(GameState* state, i32 x, i32 y);
void highlightLegalMoves(GameState* state, Piece piece);
void unhighlightLegalMoves(GameState* state);

Piece* pieceAt(GameState* state, i32 x, i32 y);
bool isSquareEmpty(GameState* state, i32 x, i32 y);


#endif  //__BOARD_H
