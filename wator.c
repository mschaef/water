#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600

int main(int argc, char *argv[]) {

     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
          printf("SDL could not be initialized!\n"
                 "SDL_Error: %s\n", SDL_GetError());
          return 0;
     }

     SDL_Window *window = SDL_CreateWindow("Wator",
                                           SDL_WINDOWPOS_UNDEFINED,
                                           SDL_WINDOWPOS_UNDEFINED,
                                           SCREEN_WIDTH, SCREEN_HEIGHT,
                                           SDL_WINDOW_SHOWN);
     if (!window) {
          printf("Window could not be created!\n"
                 "SDL_Error: %s\n", SDL_GetError());
     } else {
          SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

          if(!renderer) {
               printf("Renderer could not be created!\n"
                      "SDL_Error: %s\n", SDL_GetError());
          } else {
            bool quit = false;

            while(!quit)
            {
                SDL_Event e;

                SDL_WaitEvent(&e);

                if(e.type == SDL_QUIT) {
                    quit = true;
                }

                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                SDL_RenderClear(renderer);


                // rendering goes here

                SDL_RenderPresent(renderer);
            }

            SDL_DestroyRenderer(renderer);
        }

        SDL_DestroyWindow(window);
    }

    SDL_Quit();


    printf("end run.\n");
    return 0;
}
