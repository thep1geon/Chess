#ifndef __PIECES_H
#define __PIECES_H

#include "types.h"
#include <SDL2/SDL_render.h>

typedef enum {
    None = 0,
    PAWN, // While uppercase is black
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING,
} PieceType;

typedef bool PieceColor;
#define WhitePiece 1
#define BlackPiece 0

typedef struct Piece {
    PieceType type;
    PieceColor color;
    vec2 gridPos;
} Piece;

#define Pawn(x, y, color)   (Piece){PAWN, color, Vec2(x,y)}
#define Rook(x, y, color)   (Piece){ROOK, color, Vec2(x,y)}
#define Knight(x, y, color) (Piece){KNIGHT, color, Vec2(x,y)}
#define Bishop(x, y, color) (Piece){BISHOP, color, Vec2(x,y)}
#define King(x, y, color)   (Piece){KING, color, Vec2(x,y)}
#define Queen(x, y, color)  (Piece){QUEEN, color, Vec2(x,y)}
#define Empty(x, y)         (Piece){None, 0, Vec2(x,y)}

void drawPiece(SDL_Renderer* renderer, Piece piece);
void printPiece(Piece piece);
char* pieceTypeToString(PieceType type);
char* pieceColorToString(PieceColor color);

#endif  //__PIECES_H
