#include "include/board.h"
#include "include/consts.h"
#include "include/gamestate.h"


void rotateBoard(GameState* state) {
    for (i32 y = 0; y < NUM_ROWS / 2; ++y) {
        for (i32 x = 0; x < NUM_COLS; ++x) {
            Piece** pieceA = (Piece**) &state->pieces[y][x];
            Piece** pieceB = (Piece**) &state->pieces[NUM_ROWS - y - 1][x];
            Piece*  pieceTemp = *pieceA;

            *pieceA = *pieceB;
            *pieceB = pieceTemp;
        }
    }

    for (i32 y = 0; y < NUM_ROWS; ++y) {
        for (i32 x = 0; x < NUM_COLS / 2; ++x) {
            Piece** pieceA = (Piece**) &state->pieces[y][x];
            Piece** pieceB = (Piece**) &state->pieces[y][NUM_COLS - x - 1];
            Piece*  pieceTemp = *pieceA;

            *pieceA = *pieceB;
            *pieceB = pieceTemp;
        }
    }
}

void movePieces(GameState* state) {
    state->moveBuffer[1]->color = state->moveBuffer[0]->color; 
    state->moveBuffer[1]->type = state->moveBuffer[0]->type; 

    state->moveBuffer[0]->color = BlackPiece;
    state->moveBuffer[0]->type = None;

    // Clear the moveBuffer
    state->moveBuffer[0] = NULL;
    state->moveBuffer[1] = NULL;
}
