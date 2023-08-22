#include <stdbool.h>

#include <SDL.h>

#include "wator.h"

void main_loop(SDL_Renderer *renderer) {
     bool quit = false;

     while(!quit)
     {
          SDL_Event e;
          while ( SDL_PollEvent( &e ) != 0 ) {
               switch (e.type) {
               case SDL_QUIT:
					quit = true;
					break;
               }
          }

          SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
          SDL_RenderClear(renderer);

          update();
          render(renderer);

          SDL_RenderPresent(renderer);
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
          SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

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
