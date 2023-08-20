#include <stdbool.h>

#include <SDL.h>

#include "wator.h"

Uint32 renderEvent;

void send_render_event() {
     SDL_Event event;
     SDL_memset(&event, 0, sizeof(event));
     event.type = renderEvent;
     SDL_PushEvent(&event);
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

Uint32 invoke_update(Uint32 interval, void* param) {
     update();
     send_render_event();

     return interval;
}

int main(int argc, char *argv[]) {
     init();

     if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
          SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL could not be initialized! SDL_Error: %s\n", SDL_GetError());
          return 0;
     }

     renderEvent = SDL_RegisterEvents(1);

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
               SDL_TimerID updateTid = SDL_AddTimer(100, invoke_update, NULL);

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
