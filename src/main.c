#include <SDL2/SDL_events.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#include "include/pieces.h"
#include "include/types.h"
#include "include/color.h"
#include "include/rect.h"

// Constants
#define SCREEN_WIDTH     700
#define SCREEN_HEIGHT    512

#define CELL_SIZE        64
#define NUM_ROWS         8
#define NUM_COLS         8

#define GRID_WIDTH       (SCREEN_WIDTH / CELL_SIZE)
#define GRID_HEIGHT      (SCREEN_HEIGHT / CELL_SIZE)

#define FPS              60
#define BACKGROUND_COLOR BLACK
// __Constants

typedef struct GameState {
    i32 board[NUM_ROWS][NUM_COLS];
    Piece pieces[NUM_ROWS][NUM_COLS];
    Piece* swap_buffer[2];
    bool square_pressed;
} GameState;

GameState state;

void move_pieces(void) {
    state.swap_buffer[1]->color = state.swap_buffer[0]->color; 
    state.swap_buffer[1]->type = state.swap_buffer[0]->type; 

    state.swap_buffer[0]->color = WhitePiece;
    state.swap_buffer[0]->type = None;

    // Clear the swap_buffer
    state.swap_buffer[0] = NULL;
    state.swap_buffer[1] = NULL;
}

void init(void) {
    // Fill the board with the apporiate colors
    for (i32 y = 0; y < NUM_ROWS; ++y) {
        for (i32 x = 0; x < NUM_COLS; ++x) {
            state.board[y][x] = ((x+y)%2);
            
            if (y == 1) {state.pieces[y][x] = Pawn(x, y, BlackPiece);} // Black Pawns
            else if (y == 6) {state.pieces[y][x] = Pawn(x, y, WhitePiece);} // White Pawns
            else {state.pieces[y][x] = Empty(x, y);}

        }
    }
    
    state.pieces[0][0] = Rook(0, 0, BlackPiece); // Black pieces
    state.pieces[0][1] = Knight(1, 0, BlackPiece);
    state.pieces[0][2] = Bishop(2, 0, BlackPiece);
    state.pieces[0][3] = Queen(3, 0, BlackPiece);
    state.pieces[0][4] = King(4, 0, BlackPiece);
    state.pieces[0][5] = Bishop(5, 0, BlackPiece);
    state.pieces[0][6] = Knight(6, 0, BlackPiece);
    state.pieces[0][7] = Rook(7, 0, BlackPiece);

    state.pieces[7][0] = Rook(0, 7, WhitePiece); // White pieces
    state.pieces[7][1] = Knight(1, 7, WhitePiece);
    state.pieces[7][2] = Bishop(2, 7, WhitePiece);
    state.pieces[7][3] = Queen(3, 7, WhitePiece);
    state.pieces[7][4] = King(4, 7, WhitePiece);
    state.pieces[7][5] = Bishop(5, 7, WhitePiece);
    state.pieces[7][6] = Knight(6, 7, WhitePiece);
    state.pieces[7][7] = Rook(7, 7, WhitePiece);
}

void display(SDL_Renderer* renderer) {
    for (i32 y = 0; y < NUM_ROWS; ++y) {
        for (i32 x = 0; x < NUM_COLS; ++x) {
            Rect square = {{x * CELL_SIZE, y * CELL_SIZE}, CELL_SIZE, CELL_SIZE, GRAY};
            if (state.board[y][x] == 1) {
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

                    if (e.motion.x > 512) {break;}

                    Piece* p = &state.pieces[y][x];

                    if (state.square_pressed == true) {
                        state.swap_buffer[1] = p;
                        state.square_pressed = false;
                        move_pieces();
                    } else {
                        state.swap_buffer[0] = p;
                        state.square_pressed = true;
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
