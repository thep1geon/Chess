#include <SDL2/SDL_render.h>
#include <stdio.h>

#include "include/color.h"
#include "include/pieces.h"
#include "include/rect.h"
#include "include/types.h"

#define PIECE_WIDTH  8
#define PIECE_HEIGHT 8

i32 black_pawn[PIECE_HEIGHT][PIECE_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

i32 white_pawn[PIECE_HEIGHT][PIECE_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

i32 black_rook[PIECE_HEIGHT][PIECE_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

i32 white_rook[PIECE_HEIGHT][PIECE_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

i32 black_knight[PIECE_HEIGHT][PIECE_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

i32 white_knight[PIECE_HEIGHT][PIECE_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

i32 black_bishop[PIECE_HEIGHT][PIECE_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

i32 white_bishop[PIECE_HEIGHT][PIECE_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

i32 black_king[PIECE_HEIGHT][PIECE_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

i32 white_king[PIECE_HEIGHT][PIECE_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

i32 black_queen[PIECE_HEIGHT][PIECE_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

i32 white_queen[PIECE_HEIGHT][PIECE_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

void drawPiece(SDL_Renderer* renderer, Piece piece) {
    if (piece.type == None) {
        return;  // No piece to draw
    }

    i32 (*glyph)[PIECE_WIDTH]; 

    switch (piece.type) {
        case PAWN:
            if (piece.color == BlackPiece) {glyph = (i32(*)[PIECE_WIDTH])black_pawn;}
            else {glyph = (i32(*)[PIECE_WIDTH])white_pawn;}
            break;
        case ROOK:
            if (piece.color == BlackPiece) {glyph = (i32(*)[PIECE_WIDTH])black_rook;}
            else {glyph = (i32(*)[PIECE_WIDTH])white_rook;}
            break;
        case KNIGHT:
            if (piece.color == BlackPiece) {glyph = (i32(*)[PIECE_WIDTH])black_knight;}
            else {glyph = (i32(*)[PIECE_WIDTH])white_knight;}
            break;
        case BISHOP:
            if (piece.color == BlackPiece) {glyph = (i32(*)[PIECE_WIDTH])black_bishop;}
            else {glyph = (i32(*)[PIECE_WIDTH])white_bishop;}
            break;
        case QUEEN:
            if (piece.color == BlackPiece) {glyph = (i32(*)[PIECE_WIDTH])black_queen;}
            else {glyph = (i32(*)[PIECE_WIDTH])white_queen;}
            break;
        case KING:
            if (piece.color == BlackPiece) {glyph = (i32(*)[PIECE_WIDTH])black_king;}
            else {glyph = (i32(*)[PIECE_WIDTH])white_king;}
            break;
        default: glyph = NULL;
    };

    if (glyph == NULL) {
        return;  // No glyph for this piece
    }

    for (i32 y = 0; y < PIECE_HEIGHT; ++y) {
        for (i32 x = 0; x < PIECE_WIDTH; ++x) {
            Color backgroundColor = (((i32)piece.gridPos.x + (i32)piece.gridPos.y) % 2) ? WHITESMOKE : GRAY;

            Rect rect = {
                Vec2(x * (64.0 / PIECE_WIDTH) + piece.gridPos.x * 64, y * (64.0 / PIECE_HEIGHT) + piece.gridPos.y * 64),  // Position
                64.0 / PIECE_WIDTH,  // Width
                64.0 / PIECE_HEIGHT, // Height
                glyph[y][x] == 1 ? BLACK : backgroundColor // Color
            };

            drawFillRect(renderer, rect);
        }
    }
}

char* pieceTypeToString(PieceType type) {
    switch (type) {
        case PAWN: return "Pawn";
        case ROOK: return "Rook";
        case KNIGHT: return "Knight";
        case BISHOP: return "Bishop";
        case KING: return "King";
        case QUEEN: return "Queen";
        case None: return "Empty";
        default: return "How **did** we get here?";
    }
}
char* pieceColorToString(PieceColor color) {
    return (color == BlackPiece) ? "Black" : "White";
}

void printPiece(Piece piece) {
    printf("Piece: Type: %s, Color: %s, Pos: {x: %d, y: %d}}\n", 
           pieceTypeToString(piece.type), 
           pieceColorToString(piece.color),
           (i32) piece.gridPos.x,
           (i32) piece.gridPos.y);
}
