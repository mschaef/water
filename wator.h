#define BOARD_WIDTH 600
#define BOARD_HEIGHT 600

#define TILE_SIZE 1

#define FISH_SPAWN 24
#define SHARK_INITIAL_ENERGY 100
#define FISH_MEAL_ENERGY 10
#define SHARK_SPAWN_ENERGY 250

void init();
void update();
void render(SDL_Renderer *renderer);
