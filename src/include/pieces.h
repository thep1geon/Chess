#ifndef __PIECES_H
#define __PIECES_H

#include "types.h"
#include <SDL2/SDL_render.h>

typedef enum {
    Basic = 0,
    CyanOutline,
    DangerOutline,
} DrawMode;

typedef enum {
    None = 0,
    PAWN, 
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING,
    HIGHLIGHTED,
} PieceType;

typedef enum {
    NoColor = 0,
    WhitePiece,
    BlackPiece,
} PieceColor;

typedef struct Piece {
    PieceType  type;
    PieceColor color;

    bool       inDanger;

    vec2       gridPos;
    bool       hasMoved;
} Piece;

#define Pawn(x, y, color_)       (Piece){.type = PAWN,          .color = color_,   .gridPos = Vec2(x,y), .hasMoved = false, .inDanger = false}
#define Rook(x, y, color_)       (Piece){.type = ROOK,          .color = color_,   .gridPos = Vec2(x,y), .hasMoved = false, .inDanger = false}
#define Knight(x, y, color_)     (Piece){.type = KNIGHT,        .color = color_,   .gridPos = Vec2(x,y), .hasMoved = false, .inDanger = false}
#define Bishop(x, y, color_)     (Piece){.type = BISHOP,        .color = color_,   .gridPos = Vec2(x,y), .hasMoved = false, .inDanger = false}
#define King(x, y, color_)       (Piece){.type = KING,          .color = color_,   .gridPos = Vec2(x,y), .hasMoved = false, .inDanger = false}
#define Queen(x, y, color_)      (Piece){.type = QUEEN,         .color = color_,   .gridPos = Vec2(x,y), .hasMoved = false, .inDanger = false}
#define Empty(x, y)             (Piece){.type = None,          .color = NoColor, .gridPos = Vec2(x,y), .hasMoved = false, .inDanger = false}
#define HighLight(x, y)         (Piece){.type = HIGHLIGHTED,   .color = NoColor, .gridPos = Vec2(x,y), .hasMoved = false, .inDanger = false}

void drawPiece(SDL_Renderer* renderer, Piece piece, DrawMode mode);
void printPiece(Piece piece);
const char* pieceTypeToString(PieceType type);
const char* pieceColorToString(PieceColor color);

#endif  //__PIECES_H
