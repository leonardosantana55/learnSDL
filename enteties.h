#ifndef ENTETIES
#define ENTETIES

#include <SDL2/SDL.h>


typedef struct Field_{

    int size_x;
    int size_y;

    int tile_x;
    int tile_y;
    int tile_w;
    int tile_h;

    SDL_Rect tiles[128][128];

} Field;

typedef struct Snake_{
    
    int size;
    int max_size;
    int speed;

    int tile_x; // starting position
    int tile_y; // starting position
    int tile_w;
    int tile_h;

    SDL_Rect tiles[16];

} Snake;

void Field_Init(Field *field, int size_x, int size_y);

void Snake_Init(Snake *snake, Field *field);


#endif
