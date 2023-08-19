#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600

void main_loop(SDL_Renderer *renderer) {
     bool quit = false;

     while(!quit)
     {
          SDL_Event e;

          SDL_WaitEvent(&e);

          if(e.type == SDL_QUIT) {
               quit = true;
          }

          SDL_Log("render\n");

          SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

          SDL_RenderClear(renderer);

          SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);

          SDL_FRect box = {20, 20, 80, 80};
          SDL_RenderFillRectF(renderer, &box);


          SDL_RenderPresent(renderer);
     }
}

int main(int argc, char *argv[]) {
     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
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
               main_loop(renderer);

               SDL_DestroyRenderer(renderer);
          }

          SDL_DestroyWindow(window);
     }

     SDL_Quit();


     SDL_Log("end run.\n");
     return 0;
}
