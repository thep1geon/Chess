#include <SDL2/SDL_render.h>
#include <stdio.h>

#include "include/board.h"
#include "include/color.h"
#include "include/gamestate.h"
#include "include/pieces.h"
#include "include/rect.h"
#include "include/types.h"
#include "include/consts.h"

#include "include/sprites.h"


void drawPiece(SDL_Renderer* renderer, Piece piece, DrawMode mode) {
    // We need to find out which sprite we need to draw
    i32 (*sprite)[PIECE_WIDTH];  
    switch (piece.type) { 
        case PAWN: 
            if (piece.color == BlackPiece) {sprite = (i32(*)[PIECE_WIDTH])Sprite_BlackPawn;} 
            else {sprite = (i32(*)[PIECE_WIDTH])Sprite_WhitePawn;} 
            break; 
        case ROOK: 
            if (piece.color == BlackPiece) {sprite = (i32(*)[PIECE_WIDTH])Sprite_BlackRook;} 
            else {sprite = (i32(*)[PIECE_WIDTH])Sprite_WhiteRook;}
            break;
        case KNIGHT:
            if (piece.color == BlackPiece) {sprite = (i32(*)[PIECE_WIDTH])Sprite_BlackKnight;}
            else {sprite = (i32(*)[PIECE_WIDTH])Sprite_WhiteKnight;}
            break;
        case BISHOP:
            if (piece.color == BlackPiece) {sprite = (i32(*)[PIECE_WIDTH])Sprite_BlackBishop;}
            else {sprite = (i32(*)[PIECE_WIDTH])Sprite_WhiteBishop;}
            break;
        case QUEEN:
            if (piece.color == BlackPiece) {sprite = (i32(*)[PIECE_WIDTH])Sprite_BlackQueen;}
            else {sprite = (i32(*)[PIECE_WIDTH])Sprite_WhiteQueen;}
            break;
        case KING:
            if (piece.color == BlackPiece) {sprite = (i32(*)[PIECE_WIDTH])Sprite_BlackKing;}
            else {sprite = (i32(*)[PIECE_WIDTH])Sprite_WhiteKing;}
            break;
        case HIGHLIGHTED:
            sprite = (i32(*)[PIECE_WIDTH])Sprite_Highlighted;
            break;
        default: sprite = NULL;
    };

    if (sprite == NULL) {
        return;  // No sprite for this piece
    }

    for (i32 y = 0; y < PIECE_HEIGHT; ++y) {
        for (i32 x = 0; x < PIECE_WIDTH; ++x) {
            Color backgroundColor = (((i32)piece.gridPos.x + (i32)piece.gridPos.y) % 2) == 0 ? BOARD_COLOR_2 : BOARD_COLOR_1;

            Rect rect = {
                Vec2(x * ((f32)CELL_SIZE / PIECE_WIDTH) + piece.gridPos.x * CELL_SIZE, 
                     y * ((f32)CELL_SIZE / PIECE_HEIGHT) + piece.gridPos.y * CELL_SIZE),  // Position
                CELL_SIZE / PIECE_WIDTH,  // Width
                CELL_SIZE / PIECE_HEIGHT, // Height
                sprite[y][x] == 1 ? BLACK : backgroundColor // Color
            };

            if (mode == CyanOutline && sprite[y][x] == 2) {rect.color = CYAN;}
            else if (mode == DangerOutline && sprite[y][x] == 2) {rect.color = DARKRED;}

            drawFillRect(renderer, rect);
        }
    }
}

const char* pieceTypeToString(PieceType type) {
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
const char* pieceColorToString(PieceColor color) {
    return (color == BlackPiece) ? "Black" : "White";
}

void printPiece(Piece piece) {
    printf("Piece: {Type: %s, Color: %s, Pos: {x: %d, y: %d}}\n", 
           pieceTypeToString(piece.type), 
           pieceColorToString(piece.color),
           (i32) piece.gridPos.x,
           (i32) piece.gridPos.y);
}
