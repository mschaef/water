#define BOARD_WIDTH 100
#define BOARD_HEIGHT 100

#define TILE_SIZE 2

#define SCREEN_WIDTH    (BOARD_WIDTH * TILE_SIZE)
#define SCREEN_HEIGHT   (BOARD_HEIGHT * TILE_SIZE)

void init();
Uint32 update(Uint32 interval, void* param);
void render(SDL_Renderer *renderer);
