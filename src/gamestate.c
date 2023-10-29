#include "include/gamestate.h"
#include "include/pieces.h"

void switchPlayer(GameState* state) {
    if (state->currentPlayer == WhitePiece) {
        state->currentPlayer = BlackPiece;
    } else if (state->currentPlayer == BlackPiece) {
        state->currentPlayer = WhitePiece;
    }
}
