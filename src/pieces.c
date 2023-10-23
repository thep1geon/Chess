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
    switch (piece.type) {
        case PAWN: {
            for (i32 y = 0; y < PIECE_HEIGHT; ++y) {
                for (i32 x = 0; x < PIECE_WIDTH; ++x) {
                    Color background_color = (((i32)piece.gridPos.x + (i32)piece.gridPos.y)%2) ? WHITESMOKE : GRAY;
                    Rect rect = {Vec2(x * PIECE_WIDTH + piece.gridPos.x * 64, y * PIECE_HEIGHT + piece.gridPos.y * 64), PIECE_WIDTH, PIECE_HEIGHT, background_color};
                    if (piece.color == WhitePiece && white_pawn[y][x] == 1) {
                        rect.color = BLACK;
                    } else if (piece.color == BlackPiece && black_pawn[y][x] == 1) {
                        rect.color = BLACK;
                    }
                    drawFillRect(renderer, rect);
                }
            }
        }
        break;
        case ROOK: {
            for (i32 y = 0; y < PIECE_HEIGHT; ++y) {
                for (i32 x = 0; x < PIECE_WIDTH; ++x) {
                    Color background_color = (((i32)piece.gridPos.x + (i32)piece.gridPos.y)%2) ? WHITESMOKE : GRAY;
                    Rect rect = {Vec2(x * PIECE_WIDTH + piece.gridPos.x * 64, y * PIECE_HEIGHT + piece.gridPos.y * 64), PIECE_WIDTH, PIECE_HEIGHT, background_color};
                    if (piece.color == WhitePiece && white_rook[y][x] == 1) {
                        rect.color = BLACK;
                    } else if (piece.color == BlackPiece && black_rook[y][x] == 1) {
                        rect.color = BLACK;
                    }
                    drawFillRect(renderer, rect);
                }
            }
        }
        break;
        case KNIGHT: {
            for (i32 y = 0; y < 8; ++y) {
                for (i32 x = 0; x < 8; ++x) {
                    Color background_color = (((i32)piece.gridPos.x + (i32)piece.gridPos.y)%2) ? WHITESMOKE : GRAY;
                    Rect rect = {Vec2(x * 8 + piece.gridPos.x * 64, y * 8 + piece.gridPos.y * 64), 8, 8, background_color};
                    if (piece.color == WhitePiece && white_knight[y][x] == 1) {
                        rect.color = BLACK;
                    } else if (piece.color == BlackPiece && black_knight[y][x] == 1) {
                        rect.color = BLACK;
                    }
                    drawFillRect(renderer, rect);
                }
            }
        }
        break;
        case BISHOP: {
            for (i32 y = 0; y < 8; ++y) {
                for (i32 x = 0; x < 8; ++x) {
                    Color background_color = (((i32)piece.gridPos.x + (i32)piece.gridPos.y)%2) ? WHITESMOKE : GRAY;
                    Rect rect = {Vec2(x * 8 + piece.gridPos.x * 64, y * 8 + piece.gridPos.y * 64), 8, 8, background_color};
                    if (piece.color == WhitePiece && white_bishop[y][x] == 1) {
                        rect.color = BLACK;
                    } else if (piece.color == BlackPiece && black_bishop[y][x] == 1) {
                        rect.color = BLACK;
                    }
                    drawFillRect(renderer, rect);
                }
            }
        }
        break;
        case QUEEN: {
            for (i32 y = 0; y < 8; ++y) {
                for (i32 x = 0; x < 8; ++x) {
                    Color background_color = (((i32)piece.gridPos.x + (i32)piece.gridPos.y)%2) ? WHITESMOKE : GRAY;
                    Rect rect = {Vec2(x * 8 + piece.gridPos.x * 64, y * 8 + piece.gridPos.y * 64), 8, 8, background_color};
                    if (piece.color == WhitePiece && white_queen[y][x] == 1) {
                        rect.color = BLACK;
                    } else if (piece.color == BlackPiece && black_queen[y][x] == 1) {
                        rect.color = BLACK;
                    }
                    drawFillRect(renderer, rect);
                }
            }
        }
        break;
        case KING: {
            for (i32 y = 0; y < 8; ++y) {
                for (i32 x = 0; x < 8; ++x) {
                    Color background_color = (((i32)piece.gridPos.x + (i32)piece.gridPos.y)%2) ? WHITESMOKE : GRAY;
                    Rect rect = {Vec2(x * 8 + piece.gridPos.x * 64, y * 8 + piece.gridPos.y * 64), 8, 8, background_color};
                    if (piece.color == WhitePiece && white_king[y][x] == 1) {
                        rect.color = BLACK;
                    } else if (piece.color == BlackPiece && black_king[y][x] == 1) {
                        rect.color = BLACK;
                    }
                    drawFillRect(renderer, rect);
                }
            }
        }
        break;
        default: {
            puts("How did we get here?");
            exit(EXIT_FAILURE);
        }
    }
}

char* pieceTypeToString(PieceType type) {
    switch (type) {
        case PAWN: return "Pawn";
        case ROOK: return "Rook";
        case BISHOP: return "Bishop";
        case KNIGHT: return "Knight";
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
