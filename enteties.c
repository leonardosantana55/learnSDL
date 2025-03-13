#include "enteties.h"


void Field_Init(Field *field, int size_x, int size_y){
    
    field->size_x = size_x;
    field->size_y = size_y;

    field->tile_x = 0; //starting position
    field->tile_y = 0; //starting position
    field->tile_w = 16;
    field->tile_h = 16;
    SDL_Rect a1 = {
        field->tile_x - field->tile_w, 
        field->tile_y - field->tile_h, 
        field->tile_w,
        field->tile_h
        };


    for(int i=0; i<size_x; i++){
        for(int j=0; j<size_y; j++){

            field->tiles[i][j].x = a1.x + (a1.w * (j+1));
            field->tiles[i][j].y = a1.y + (a1.h * (i+1));
            field->tiles[i][j].w = a1.w;
            field->tiles[i][j].h = a1.h;

        }
    }

}


void Snake_Init(Snake *snake, Field *field){
    
    snake->size = 3;
    snake->max_size = 10;
    snake->speed = 3;

    snake->tile_x = field->tiles[field->size_x/2][field->size_x/2].x;    // the position of the snake depends on the coordinates of the field tiles
    snake->tile_y = field->tiles[field->size_y/2][field->size_y/2].y;
    snake->tile_w = field->tile_w;
    snake->tile_h = field->tile_h;

    for(int i=0; i<snake->size; i++){

        snake->tiles[i].x = snake->tile_x - (snake->tile_w * i);
        snake->tiles[i].y = snake->tile_y;
        snake->tiles[i].w = snake->tile_w;
        snake->tiles[i].h = snake->tile_h;

    }

}


void Snake_Move(Snake *snake){
    
    for(int i=0; i<snake->size; i++){
        snake->tiles[i].x += snake->tile_w;
    }
}
