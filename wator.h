#define BOARD_WIDTH 200
#define BOARD_HEIGHT 200

#define TILE_SIZE 2

#define SCREEN_WIDTH    (BOARD_WIDTH * TILE_SIZE)
#define SCREEN_HEIGHT   (BOARD_HEIGHT * TILE_SIZE)

void init();
void update();
void render(SDL_Renderer *renderer);
