#include "include/board.h"
#include "include/consts.h"
#include "include/gamestate.h"
#include "include/pieces.h"
#include "include/types.h"


void rotateBoard(GameState* state) {
    // Swap the pieces vertically
    for (i32 y = 0; y < NUM_ROWS / 2; ++y) {
        for (i32 x = 0; x < NUM_COLS; ++x) {
            Piece** pieceA    = (Piece**) &state->pieces[y][x];
            Piece** pieceB    = (Piece**) &state->pieces[NUM_ROWS - y - 1][x];
            Piece*  pieceTemp = *pieceA;

            *pieceA = *pieceB;
            *pieceB = pieceTemp;
        }
    }

    // Swap the pieces horizontally
    for (i32 y = 0; y < NUM_ROWS; ++y) {
        for (i32 x = 0; x < NUM_COLS / 2; ++x) {
            Piece** pieceA    = (Piece**) &state->pieces[y][x];
            Piece** pieceB    = (Piece**) &state->pieces[y][NUM_COLS - x - 1];
            Piece*  pieceTemp = *pieceA;

            *pieceA = *pieceB;
            *pieceB = pieceTemp;
        }
    }
}

void movePieces(GameState* state) {
    Piece* srcPiece  = pieceAt(state, Vec2Param(state->clickedSquares[0]));
    Piece* destPiece = pieceAt(state, Vec2Param(state->clickedSquares[1]));

    destPiece->color = srcPiece->color;
    destPiece->type = srcPiece->type;
    destPiece->hasMoved = true;

    srcPiece->type = None;
    srcPiece->color = NoColor;
    srcPiece->hasMoved = false;
}

void movePiece(GameState* state, i32 x1, i32 y1, i32 x2, i32 y2) {
    Piece* srcPiece  = pieceAt(state, x1, y1);
    Piece* destPiece = pieceAt(state, x2, y2);

    destPiece->color = srcPiece->color;
    destPiece->type = srcPiece->type;
    destPiece->hasMoved = true;

    srcPiece->type = None;
    srcPiece->color = NoColor;
    srcPiece->hasMoved = false;
}

Piece* pieceAt(GameState* state, i32 x, i32 y) {
    return &state->pieces[y][x];
}
