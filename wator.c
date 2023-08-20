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

               if (rand() % 100 < 2) {
                    set_board(xx, yy, CELL_FISH);
               }
          }
     }
}

static int add_coord(int c, int dc, int limit) {
     int c2 = c + dc;

     if (c2 >= limit) {
          c2 = 0;
     } else if (c2 < 0) {
          c2 = limit - 1;
     }

     return c2;
}

static void rand_direction(int *dx, int *dy) {
     *dx = 0;
     *dy = 0;

     switch(rand() % 4) {
     case 0: *dx = 0; *dy = -1; break;
     case 1: *dx = 1; *dy = 0; break;
     case 2: *dx = 0; *dy = 1; break;
     case 3: *dx = -1; *dy = 1; break;
     }
}

void update() {
     for(int xx = 0; xx < BOARD_WIDTH; xx++) {
          for(int yy = 0; yy < BOARD_HEIGHT; yy++) {
               if (get_board(xx, yy) == CELL_FISH) {
                    int dx, dy;

                    rand_direction(&dx, &dy);

                    int x2 = add_coord(xx, dx, BOARD_WIDTH);
                    int y2 = add_coord(yy, dy, BOARD_HEIGHT);

                    if (get_board(x2, y2) == CELL_EMPTY) {
                         set_board(xx, yy, CELL_EMPTY);
                         set_board(x2, y2, CELL_FISH);
                    }

               }
          }
     }
}

void render(SDL_Renderer *renderer) {
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
