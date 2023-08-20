#include <SDL.h>

#include "wator.h"

int board[BOARD_WIDTH * BOARD_HEIGHT];

void init() {
     for(int ii = 0; ii < BOARD_WIDTH * BOARD_HEIGHT; ii++) {
          board[ii] = rand() % 3;
     }
}

Uint32 update(Uint32 interval, void* param) {
     SDL_Log("update");

     return interval;
}

void render(SDL_Renderer *renderer) {
     SDL_Log("render\n");

     SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
     SDL_RenderClear(renderer);

     for(int xx = 0; xx < BOARD_WIDTH; xx++) {
          for(int yy = 0; yy < BOARD_HEIGHT; yy++) {
               int cel = board[xx + yy * BOARD_WIDTH];

               if (cel == 0) {
                    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
               } if (cel == 1) {
                    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
               } if (cel == 2) {
                    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
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
