//To build a Snake-like game, you need to understand and implement several key data structures and algorithms. Here’s a structured overview:
//Data Structures
//Linked List:
//Use a linked list to represent the snake's body. Each segment of the snake can be a node in the linked list, allowing for efficient growth and movement. This structure makes it easy to add new segments when the snake eats food and remove the tail segment when it moves13.
//Queue:
//A queue can also be used to manage the snake's segments. You can enqueue new segments at the head and dequeue from the tail, which simplifies the logic for moving the snake and managing its length24.
//2D Array/Grid:
//Implementing a 2D array can help represent the game board. Each cell in the array can hold information about whether it contains food, is empty, or is occupied by a segment of the snake56.
//Cell Class:
//Create a Cell class to represent each point on the board, storing its state (empty, food, or part of the snake). This class can also include methods to manage interactions with food and walls3.
//Algorithms
//Movement Logic:
//Implement algorithms to handle user input for changing the snake's direction. The movement should update the position of the head based on its current direction and manage tail movement accordingly4.
//Collision Detection:
//Write functions to detect collisions with walls or the snake’s own body, which will end the game if detected34.
//Food Generation:
//Create algorithms for randomly placing food on the grid and ensuring it does not overlap with the snake's body45.
//Game Loop:
//Establish a game loop that continuously updates the game state, processes user input, checks for collisions, and renders the game graphics.
//Scoring System:
//Implement a scoring system that increases as the snake eats food, providing feedback to players on their performance


#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

// its a breeze building this program on linux or windows 
#ifdef _WIN32
#define XMAIN WinMain
#elif __linux__
#define XMAIN main
#endif


//Global variables
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
SDL_Window* gWindow = NULL;
SDL_Surface* gWindow_surface = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

bool initSDL(){
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else{
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else{
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL ){
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else{
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) ){
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                else{
                    //Get window surface
                    gWindow_surface = SDL_GetWindowSurface( gWindow );
                }
            }
        }
    }

    return success;
}


SDL_Texture* loadTexture(char* file_path){
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(file_path);
    if(loadedSurface == NULL){
        printf( "Unable to load image %s! SDL_image Error: %s\n", file_path, IMG_GetError() );
    }
    else{
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", file_path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}


bool loadMedia(char* file_path, SDL_Surface** surface){
    bool success = true;

    SDL_Surface* temp_surface = NULL;
    temp_surface = IMG_Load(file_path);

    if( temp_surface == NULL ){
        printf( "Unable to load image %s! SDL_image Error: %s\n", file_path, IMG_GetError() );
    }
    else{
        // this is used for optimization
        *surface = SDL_ConvertSurface(temp_surface, gWindow_surface->format, 0);
        SDL_FreeSurface(temp_surface);

        if(*surface == NULL){
            printf( "Unable to load image %s! SDL Error: %s\n",
            file_path, SDL_GetError() );
            success = false;
        }
    }

    return success;
}


void eventLogicQuit(SDL_Event* e, bool* quit){
    if(e->type == SDL_QUIT){
        *quit = true;
    }

}


void eventLogicKeyPrint(SDL_Event* e){
    if(e->type == SDL_TEXTINPUT){
        printf("%s\n", e->text.text);
    }
}


void closeSDL(){
    //Dealocate Surface
    SDL_FreeSurface(gWindow_surface);
    gWindow_surface = NULL;

    //Destroy renderer
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    //Destroy texture
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow_surface = NULL;

    //Quit SDL Subsystems
    SDL_Quit();
}


void initBoard(int board_size_x, int board_size_y, SDL_Rect board[static board_size_x][board_size_y]){
    // All the other cells are based on the starting position of a1
    int cell_x = 0;
    int cell_y = 0;
    int cell_w = SCREEN_WIDTH / board_size_x;
    int cell_h = SCREEN_HEIGHT / board_size_y;
    SDL_Rect a1 = {cell_x - cell_w, cell_y - cell_h, cell_w, cell_h};

    for(int i=0; i<board_size_x; i++){
        for(int j=0; j<board_size_y; j++){
            board[i][j].x = a1.x + (a1.w * (j+1));
            board[i][j].y = a1.y + (a1.h * (i+1));
            board[i][j].w = a1.w;
            board[i][j].h = a1.h;

        }
    }
}


void renderBoard(int board_size_x, int board_size_y, SDL_Rect board[static board_size_x][board_size_y]){
    for(int i=0; i<board_size_x; i++){
        for(int j=0; j<board_size_y; j++){
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderFillRect(gRenderer, &board[i][j]);
            SDL_SetRenderDrawColor(gRenderer, 0xF0, 0xF0, 0xF0, 0xF0);
            SDL_RenderDrawRect(gRenderer, &board[i][j]);
        }
    }
}

//TODO: before i can create a snake i need a field where i can put it. create a struct for the board

//typedef struct _Snake{
//
//    SDL_Rect body[10];
//
//    SDL_Rect board[][];
//
//    int min_size;
//    int current_size;
//    int max_size;
//
//    int start_pos_x;
//    int start_pos_y;
//
//    int min_speed;
//    int max_speed;
//} Snake;
//
//
//void initSnake(Snake *snake, SDL_Rect board){
//
//    int cell_x = 0;
//    int cell_y = 0;
//    int cell_w = SCREEN_WIDTH / board_size_x;
//    int cell_h = SCREEN_HEIGHT / board_size_y;
//
//    
//    snake->min_size = 3;
//    int current_size = min_size;
//    snake->max_size = sizeof(snake->body) / sizeof(snake->body[0]);
//
//    snake->start_pos_x = 3;
//    snake->start_pos_y = 3;
//
//    int min_speed = 3;
//    int max_speed = 3;
//
//}
//
//void renderSnake(Snake *snake){
//    
//    for (int i=0; i<snake->current_size; i++){
//        
//    }
//}

int XMAIN(){
    initSDL();
    SDL_Event e;

    // init board
    int board_size_x = 50;
    int board_size_y = 50;
    SDL_Rect board[board_size_x][board_size_y] = {};
    initBoard(board_size_x, board_size_y, board);


    // main loop
    bool quit = false;
    while(!quit){

        // event logic loop
        while(SDL_PollEvent(&e)){
            eventLogicQuit(&e, &quit);
            eventLogicKeyPrint(&e);
        }

        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
        SDL_RenderClear( gRenderer );


        // render game elements
        renderBoard(board_size_x, board_size_y, board);


        //Update screen
        SDL_RenderPresent( gRenderer );
    }

    closeSDL();
    return 0;
}


// TODO: testar modificar os parametros da função initBoard e renderBoard pra receberem ponteiros em
// vez de array
