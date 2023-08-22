#include <SDL.h>

// See https://beltoforion.de/en/wator/ for rules

#include "wator.h"

int board[BOARD_WIDTH * BOARD_HEIGHT];

#define CELL_EMPTY 0
#define CELL_FISH 1
#define CELL_SHARK 2

#define CELL_TYPE 0xFF

int cell_type(int cel) {
     return cel & CELL_TYPE;
}

int fish_age(int cel) {
     return cel >> 8;
}

int make_fish(int age) {
     return (age << 8) | CELL_FISH;
}

int make_shark(int energy) {
     return (energy << 8) | CELL_SHARK;
}

int shark_energy(int cel) {
     return cel >> 8;
}

#define FISH_SPAWN 12

#define SHARK_INITIAL_ENERGY 100
#define FISH_MEAL_ENERGY 10

#define SHARK_SPAWN_ENERGY 250

void set_board(int x, int y, int cel) {
     board[x + y * BOARD_WIDTH] = cel;
}

int get_board(int x, int y) {
     return board[x + y * BOARD_WIDTH];
}

void init() {
     for(int xx = 0; xx < BOARD_WIDTH; xx++) {
          for(int yy = 0; yy < BOARD_HEIGHT; yy++) {
               int r = rand() % 1000;

               if (r < 5) {
                    set_board(xx, yy, make_fish(0));
               } else if (r < 6) {
                    set_board(xx, yy, make_shark(SHARK_INITIAL_ENERGY));
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
     case 3: *dx = -1; *dy = 0; break;
     }
}

void update() {
     for(int xx = 0; xx < BOARD_WIDTH; xx++) {
          for(int yy = 0; yy < BOARD_HEIGHT; yy++) {
               int cel = get_board(xx, yy);

               int dx, dy;
               rand_direction(&dx, &dy);

               int x2 = add_coord(xx, dx, BOARD_WIDTH);
               int y2 = add_coord(yy, dy, BOARD_HEIGHT);

               int cel2 = get_board(x2, y2);

               if (cell_type(cel) == CELL_FISH) {
                    int age = fish_age(cel);

                    if (get_board(x2, y2) == CELL_EMPTY) {
                         if (age >= FISH_SPAWN) {
                              set_board(xx, yy, make_fish(0));
                              set_board(x2, y2, make_fish(0));
                         } else {
                              set_board(xx, yy, CELL_EMPTY);
                              set_board(x2, y2, make_fish(age + 1));
                         }
                    }

               } else if (cell_type(cel) == CELL_SHARK) {

                    int energy = shark_energy(cel);

                    if (cell_type(cel2) == CELL_EMPTY) {

                         if (energy > SHARK_SPAWN_ENERGY) {
                              set_board(xx, yy, make_shark(energy /2));
                              set_board(x2, y2, make_shark(energy /2));

                         } else if (energy > 1) {
                              set_board(xx, yy, CELL_EMPTY);
                              set_board(x2, y2, make_shark(energy - 1));

                         } else {
                              set_board(xx, yy, CELL_EMPTY);
                         }


                    } else if (cell_type(cel2) == CELL_FISH) {
                         set_board(xx, yy, CELL_EMPTY);
                         set_board(x2, y2, make_shark(energy + FISH_MEAL_ENERGY));

                    } else {
                         if (energy > 1) {
                              set_board(xx, yy, make_shark(energy - 1));
                         } else {
                              set_board(xx, yy, CELL_EMPTY);
                         }
                    }

               }
          }
     }
}

void render(SDL_Renderer *renderer) {
     for(int xx = 0; xx < BOARD_WIDTH; xx++) {
          for(int yy = 0; yy < BOARD_HEIGHT; yy++) {
               int cel = get_board(xx, yy);

               int t = cell_type(cel);

               if (t == CELL_EMPTY) {
                    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
               } if (t == CELL_FISH) {
                    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
               } if (t == CELL_SHARK) {
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
}
