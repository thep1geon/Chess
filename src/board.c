#include "include/board.h"
#include "include/consts.h"
#include "include/gamestate.h"
#include "include/pieces.h"
#include "include/types.h"
#include <math.h>
#include <stdlib.h>

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

    state->pieces[y1][x2] = Empty(x1, y1);
}

bool validMove(GameState* state, Piece piece, vec2 toPos) {
    if (pieceAt(state, toPos.x, toPos.y)->color == piece.color) {
        return false; // Cannot move to a square with your own piece
    }

    i32 dx = abs((i32)toPos.x - (i32)piece.gridPos.x);
    i32 dy = abs((i32)toPos.y - (i32)piece.gridPos.y);

    switch (piece.type) {
        case PAWN: {
            i32 direction = -1;
            if (dx == 0) {
                // Moving forward
                if (toPos.y == piece.gridPos.y + direction) {
                    return pieceAt(state, Vec2Param(toPos))->type == None;
                }
                // Moving forward two squares on the first move
                else if (piece.gridPos.y == 6 && toPos.y == piece.gridPos.y + 2 * direction) {
                    return pieceAt(state, toPos.x, toPos.y)->type == None &&
                           pieceAt(state, piece.gridPos.x, piece.gridPos.y + direction)->type == None;
                }
            } else if (dx == 1 && toPos.y == piece.gridPos.y + direction) {
                // Capturing diagonally
                return pieceAt(state, toPos.x, toPos.y)->type != None;
            }
            return false;
        }

        case KNIGHT: {
            return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
        }

        case ROOK: {
            if (dx == 0 || dy == 0) {
                // Either horizontal or vertical movement, but not both
                vec2 dir = Vec2((dx != 0) ? (toPos.x > piece.gridPos.x) ? 1 : -1 : 0,
                                (dy != 0) ? (toPos.y > piece.gridPos.y) ? 1 : -1 : 0);

                i32 spaces = (dx != 0) ? dx : dy;

                for (i32 i = 1; i < spaces; ++i) {
                    i32 x = piece.gridPos.x + i * dir.x;
                    i32 y = piece.gridPos.y + i * dir.y;

                    if (!isSquareEmpty(state, x, y) && pieceAt(state, x, y)->type != HIGHLIGHTED) {
                        return false;
                    }
                }

                return true; // Valid rook move
            }

            return false;
        }

        case BISHOP: {
            if (dx == dy) {
                i32 xDir = (toPos.x > piece.gridPos.x) ? 1 : -1;
                i32 yDir = (toPos.y > piece.gridPos.y) ? 1 : -1;
                i32 spaces = dx;
                for (i32 i = 1; i < spaces; ++i) {
                    i32 x = piece.gridPos.x + i * xDir;
                    i32 y = piece.gridPos.y + i * yDir;
                    if (!isSquareEmpty(state, x, y) && pieceAt(state, x, y)->type != HIGHLIGHTED) {
                        return false;
                    }
                }
                return true; // Valid bishop move
            }
            return false;
        }

        case QUEEN: {
            if (dx == 0 || dy == 0) {
                // Queen's move is like a rook
                // Validate as a rook move
                i32 xDir = (dx == 0) ? 0 : (toPos.x > piece.gridPos.x) ? 1 : -1;
                i32 yDir = (dy == 0) ? 0 : (toPos.y > piece.gridPos.y) ? 1 : -1;
                i32 spaces = (dx != 0) ? dx : dy;
                for (i32 i = 1; i < spaces; ++i) {
                    i32 x = piece.gridPos.x + i * xDir;
                    i32 y = piece.gridPos.y + i * yDir;
                    if (!isSquareEmpty(state, x, y) && pieceAt(state, x, y)->type != HIGHLIGHTED) {
                        return false;
                    }
                }
                return true; // Valid queen move
            } else if (dx == dy) {
                // Queen's move is like a bishop
                // Validate as a bishop move
                i32 xDir = (toPos.x > piece.gridPos.x) ? 1 : -1;
                i32 yDir = (toPos.y > piece.gridPos.y) ? 1 : -1;
                i32 spaces = dx;
                for (i32 i = 1; i < spaces; ++i) {
                    i32 x = piece.gridPos.x + i * xDir;
                    i32 y = piece.gridPos.y + i * yDir;
                    if (!isSquareEmpty(state, x, y) && pieceAt(state, x, y)->type != HIGHLIGHTED) {
                        return false;
                    }
                }
                return true; // Valid queen move
            }
            return false;
        }

        case KING: {
            if (dx <= 1 && dy <= 1) {
                return true; // Valid king move (within 1 square in any direction)
            }
            return false;
        }

        default:
            return false; // Unsupported piece type
    }
}

void highlightSquare(GameState* state, i32 x, i32 y) {
    state->pieces[y][x] = HighLight(x, y);
}

void highlightLegalMoves(GameState* state, Piece piece) {
    for (i32 y = 0; y < NUM_ROWS; ++y) {
        for (i32 x = 0; x < NUM_COLS; ++x) {
            if (!validMove(state, piece, Vec2(x, y))) {
                continue;;
            }

            if (isSquareEmpty(state, x, y)) {
                state->pieces[y][x] = HighLight(x, y);
            } else {
                state->pieces[y][x].inDanger = true;
            }
        }
    }
}

void unhighlightLegalMoves(GameState* state) {
    for (i32 y = 0; y < NUM_ROWS; ++y) {
        for (i32 x = 0; x < NUM_COLS; ++x) {
            if (pieceAt(state, x, y)->type == HIGHLIGHTED) {
                state->pieces[y][x] = Empty(x, y);
            } else if (!isSquareEmpty(state, x, y)) {
                pieceAt(state, x, y)->inDanger = false;
            }
        }
    }
}

Piece* pieceAt(GameState* state, i32 x, i32 y) {
    return &state->pieces[y][x];
}

bool isSquareEmpty(GameState* state, i32 x, i32 y) {
    return (*state).pieces[y][x].type == None; 
}
