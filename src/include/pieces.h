#ifndef __PIECES_H
#define __PIECES_H

#include "types.h"
#include <SDL2/SDL_render.h>

typedef enum {
    None = 0,
    PAWN, 
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING,
} PieceType;

typedef enum {
    NoColor = 0,
    WhitePiece,
    BlackPiece,
} PieceColor;

typedef struct Piece {
    PieceType  type;
    PieceColor color;
    vec2       gridPos;
    bool       hasMoved;
} Piece;

#define Pawn(x, y, color)   (Piece){PAWN,   color,   Vec2(x,y), .hasMoved = false}
#define Rook(x, y, color)   (Piece){ROOK,   color,   Vec2(x,y), .hasMoved = false}
#define Knight(x, y, color) (Piece){KNIGHT, color,   Vec2(x,y), .hasMoved = false}
#define Bishop(x, y, color) (Piece){BISHOP, color,   Vec2(x,y), .hasMoved = false}
#define King(x, y, color)   (Piece){KING,   color,   Vec2(x,y), .hasMoved = false}
#define Queen(x, y, color)  (Piece){QUEEN,  color,   Vec2(x,y), .hasMoved = false}
#define Empty(x, y)         (Piece){None,   NoColor, Vec2(x,y), .hasMoved = false}

void drawPiece(SDL_Renderer* renderer, Piece piece, bool drawOutline);
void printPiece(Piece piece);
const char* pieceTypeToString(PieceType type);
const char* pieceColorToString(PieceColor color);

#endif  //__PIECES_H
