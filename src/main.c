#include <SDL2/SDL_events.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#include "include/pieces.h"
#include "include/types.h"
#include "include/color.h"
#include "include/rect.h"
#include "include/consts.h"
#include "include/gamestate.h"
#include "include/board.h"

// Macros

#define PlacePiece(x, y, type, color) state.pieces[y][x] = type(x, y, color)
#define EmptySquare(x, y)             state.pieces[y][x] = Empty(x, y)

// __Macros

GameState state;

void init(void) {
    // Fill the board with the apporiate colors
    for (i32 y = 0; y < NUM_ROWS; ++y) {
        for (i32 x = 0; x < NUM_COLS; ++x) {
            state.board[y][x] = ((x+y)%2);
            
            if (y == 1) {PlacePiece(x, y, Pawn, BlackPiece);} // Black Pawns
            else if (y == 6) {PlacePiece(x, y, Pawn, WhitePiece);} // White Pawns
            else {EmptySquare(x, y);}

        }
    }
    
    // Place the pieces on the board
    PlacePiece(0, 0, Rook, BlackPiece); // Black pieces
    PlacePiece(1, 0, Knight, BlackPiece);
    PlacePiece(2, 0, Bishop, BlackPiece);
    PlacePiece(3, 0, Queen, BlackPiece);
    PlacePiece(4, 0, King, BlackPiece);
    PlacePiece(5, 0, Bishop, BlackPiece);
    PlacePiece(6, 0, Knight, BlackPiece);
    PlacePiece(7, 0, Rook, BlackPiece);

    PlacePiece(0, 7, Rook, WhitePiece); // White pieces
    PlacePiece(1, 7, Knight, WhitePiece);
    PlacePiece(2, 7, Bishop, WhitePiece);
    PlacePiece(3, 7, Queen, WhitePiece);
    PlacePiece(4, 7, King, WhitePiece);
    PlacePiece(5, 7, Bishop, WhitePiece);
    PlacePiece(6, 7, Knight, WhitePiece);
    PlacePiece(7, 7, Rook, WhitePiece);
}

void display(SDL_Renderer* renderer) {
    for (i32 y = 0; y < NUM_ROWS; ++y) {
        for (i32 x = 0; x < NUM_COLS; ++x) {
            Rect square = {{x * CELL_SIZE, y * CELL_SIZE}, CELL_SIZE, CELL_SIZE, GRAY};
            if (state.board[y][x] == 0) {
                square.color = WHITESMOKE;
            }

            // Draw the square first
            drawFillRect(renderer, square);
            
            Piece piece = state.pieces[y][x];
            if (piece.type == None) {continue;}

            drawPiece(renderer, piece); 
        }
    }
}

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Chess!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event e;
    u32 frameStart, frameTime;
    const u32 frameDelay = 1000/FPS;

    init();
    
    while (!quit) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT: {
                    quit = true;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    i32 x = e.motion.x / CELL_SIZE;
                    i32 y = e.motion.y / CELL_SIZE;

                    if (e.motion.x > 512) {break;} // Let's not excede the chess board or we'll seg fault

                    Piece* p = &state.pieces[y][x]; // We store a reference to the piece so we can modify it later

                    if (state.wasSquarePressed == true) {
                        state.moveBuffer[1] = p;
                        state.wasSquarePressed = false;
                        movePieces(&state);
                        rotateBoard(&state);
                    } else {
                        state.moveBuffer[0] = p;
                        state.wasSquarePressed = true;
                    }
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, ColorParam(BACKGROUND_COLOR));
        SDL_RenderClear(renderer);
        // Start Drawing

        display(renderer);

        // End Drawing
        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
