#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>

#define BOARD_WIDTH 100
#define BOARD_HEIGHT 100

#define TILE_SIZE 2

#define SCREEN_WIDTH    (BOARD_WIDTH * TILE_SIZE)
#define SCREEN_HEIGHT   (BOARD_HEIGHT * TILE_SIZE)

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

void main_loop(SDL_Renderer *renderer) {
     bool quit = false;

     while(!quit)
     {
          SDL_Event e;

          SDL_WaitEvent(&e);

          if(e.type == SDL_QUIT) {
               quit = true;
          }

          render(renderer);
     }
}

int main(int argc, char *argv[]) {
     init();

     if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
          SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL could not be initialized! SDL_Error: %s\n", SDL_GetError());
          return 0;
     }

     SDL_Window *window = SDL_CreateWindow("Wator",
                                           SDL_WINDOWPOS_UNDEFINED,
                                           SDL_WINDOWPOS_UNDEFINED,
                                           SCREEN_WIDTH, SCREEN_HEIGHT,
                                           SDL_WINDOW_SHOWN);

     if (!window) {
          SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
     } else {
          SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

          if(!renderer) {
               SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
          } else {
               SDL_TimerID updateTid = SDL_AddTimer(1000, update, NULL);

               if (!updateTid) {
                    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Update timer could not be created! SDL_Error: %s\n", SDL_GetError());
               } else {
                    main_loop(renderer);
               }

               SDL_DestroyRenderer(renderer);
          }

          SDL_DestroyWindow(window);
     }

     SDL_Quit();


     SDL_Log("end run.\n");
     return 0;
}
