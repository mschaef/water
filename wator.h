#define BOARD_WIDTH 600
#define BOARD_HEIGHT 600

#define TILE_SIZE 1

#define SCREEN_WIDTH    (BOARD_WIDTH * TILE_SIZE)
#define SCREEN_HEIGHT   (BOARD_HEIGHT * TILE_SIZE)

void init();
void update();
void render(SDL_Renderer *renderer);
