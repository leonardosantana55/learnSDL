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

    for(int i=0; i<field->size_x; i++){
        for(int j=0; j<field->size_y; j++){

            field->on_tile[i][j] = EMPTY;

        }
    }

    for(int i=0; i<ENTETIES_MAX_SNAKES; i++){

        field->snakes_on_field[i] = 0;

    }

}


/******************************************************************************
*Function Description:
Checks the position of snakes and mark their position on the board
will be expanded to include food and walls
maybe add dynamic walls in the future

******************************************************************************/
void Field_Update(Field *field){
    int a = 0;
    int b = 0;

    //resets all status
    for(int i=0; i<field->size_x; i++){
        for(int j=0; j<field->size_y; j++){

            field->on_tile[i][j] = EMPTY;

        }
    }

    //look for snakes position
    for(int i=0; i<ENTETIES_MAX_SNAKES; i++){

        if(field->snakes_on_field[i] != 0){
        
            for(int j=0; j < field->snakes_on_field[i]->size; j++){

                a = field->snakes_on_field[i]->tiles[j].y / field->tile_h;
                b = field->snakes_on_field[i]->tiles[j].x / field->tile_w;

                field->on_tile[a][b] = SNAKE;

            }
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
    
    //make comunication possible betwheen objects
    snake->field = field;

    for(int i=0; i<ENTETIES_MAX_SNAKES; i++){

        if(field->snakes_on_field[i] == 0){
            field->snakes_on_field[i] = snake;
            break;
        }

    }

}


void Snake_Move(Snake *snake, int direction){

    SDL_Rect temp_pre = snake->tiles[1];
    SDL_Rect temp = snake->tiles[0];

    switch(direction){
        //TODO: add colision detection
        //move the head of the snake and copy the previous tile to the old head position and so on

        case RIGHT:
            snake->tiles[0].x += snake->tile_w;
            break;

        case DOWN:
            snake->tiles[0].y += snake->tile_h;
            break;

        case LEFT:
            snake->tiles[0].x -= snake->tile_w;
            break;

        case UP:
            snake->tiles[0].y -= snake->tile_h;
            break;

    }

    //for loop starts on 1 because the head has moved already
    for(int i=1; i<snake->size; i++){

        temp_pre = snake->tiles[i];
        snake->tiles[i] = temp;
        temp = temp_pre;
        temp_pre = snake->tiles[i+1];

    }
}
