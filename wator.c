#include <SDL.h>

#include "wator.h"

int board[BOARD_WIDTH * BOARD_HEIGHT];

#define CELL_EMPTY 0
#define CELL_FISH 1
#define CELL_SHARK 2

void set_board(int x, int y, int cel) {
     board[x + y * BOARD_WIDTH] = cel;
}

int get_board(int x, int y) {
     return board[x + y * BOARD_WIDTH];
}

void init() {
     for(int xx = 0; xx < BOARD_WIDTH; xx++) {
          for(int yy = 0; yy < BOARD_HEIGHT; yy++) {
               set_board(xx, yy, rand() % 2);
          }
     }
}


Uint32 update(Uint32 interval, void* param) {
     SDL_Log("update\n");

     for(int xx = 0; xx < BOARD_WIDTH; xx++) {
          for(int yy = 0; yy < BOARD_HEIGHT; yy++) {
               if (get_board(xx, yy) == CELL_FISH) {
                    int dx, dy;

                    switch(rand() % 4) {
                    case 0: dx = 0; dy = -1; break;
                    case 1: dx = 1; dy = 0; break;
                    case 2: dx = 0; dy = 1; break;
                    case 3: dx = -1; dy = 1; break;
                    }

                    int x2 = xx + dx;

                    if (x2 >= BOARD_WIDTH) {
                         x2 = 0;
                    } else if (x2 < 0) {
                         x2 = BOARD_WIDTH - 1;
                    }

                    int y2 = yy + dy;

                    if (y2 >= BOARD_HEIGHT) {
                         y2 = 0;
                    } else if (y2 < 0) {
                         y2 = BOARD_HEIGHT - 1;
                    }

                    if (get_board(x2, y2) == CELL_EMPTY) {
                         set_board(xx, yy, CELL_EMPTY);
                         set_board(x2, y2, CELL_FISH);
                    }

               }
          }
     }

     return interval;
}

void render(SDL_Renderer *renderer) {
     SDL_Log("render\n");

     SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
     SDL_RenderClear(renderer);

     for(int xx = 0; xx < BOARD_WIDTH; xx++) {
          for(int yy = 0; yy < BOARD_HEIGHT; yy++) {
               int cel = get_board(xx, yy);

               if (cel == CELL_EMPTY) {
                    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
               } if (cel == CELL_FISH) {
                    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
               } if (cel == CELL_SHARK) {
                    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
               }

               SDL_FRect box;

               box.x = xx * TILE_SIZE;
               box.y = yy * TILE_SIZE;
               box.w = TILE_SIZE;
               box.h = TILE_SIZE;

               SDL_RenderFillRectF(renderer, &box);
          }
     }


     SDL_RenderPresent(renderer);
}
