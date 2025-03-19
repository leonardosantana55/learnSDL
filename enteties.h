#ifndef ENTETIES
#define ENTETIES
#define ENTETIES_SIZE 128
#define ENTETIES_MAX_SNAKES 4

#include <SDL2/SDL.h>

enum Direction {RIGHT, DOWN, LEFT, UP};

enum Entetie_name {EMPTY, SNAKE, FOOD, WALL};

typedef struct Field_{

    int size_x;
    int size_y;

    int tile_x;
    int tile_y;
    int tile_w;
    int tile_h;

    SDL_Rect tiles[ENTETIES_SIZE][ENTETIES_SIZE];

    //describe what enteti is on each tile
    int on_tile[ENTETIES_SIZE][ENTETIES_SIZE];

    //hold the address for each snake inside the field
    struct Snake_ *snakes_on_field[ENTETIES_MAX_SNAKES];

} Field;

typedef struct Snake_{
    
    int size;
    int max_size;
    int speed;

    int tile_x; // starting position
    int tile_y; // starting position
    int tile_w;
    int tile_h;

    SDL_Rect tiles[ENTETIES_SIZE];
    Field *field;

} Snake;

void Field_Init(Field *field, int size_x, int size_y);

void Field_Update(Field *field);

void Snake_Init(Snake *snake, Field *field);

void Snake_Move(Snake *snake, int direction);


#endif
