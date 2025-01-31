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

enum AllImages{
    IMAGEM_DEFAULT,
    IMAGEM_UP,
    IMAGEM_DOWN,
    IMAGEM_TOTAL
};

char *image_name[IMAGEM_TOTAL] = {
"hello.bmp",
"hello_up.bmp",
"hello_down.bmp"
};


//Global variables
const int SCREEN_WIDTH = 640*2;
const int SCREEN_HEIGHT = 480*2;
SDL_Window* gwindow = NULL;
SDL_Surface* gwindow_surface = NULL;
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
        gwindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gwindow == NULL ){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else{
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gwindow, -1, SDL_RENDERER_ACCELERATED );
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
                    gwindow_surface = SDL_GetWindowSurface( gwindow );
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
        *surface = SDL_ConvertSurface(temp_surface, gwindow_surface->format, 0);
        SDL_FreeSurface(temp_surface);

        if(*surface == NULL){
            printf( "Unable to load image %s! SDL Error: %s\n",
            file_path, SDL_GetError() );
            success = false;
        }
    }

    return success;
}


void eventLogicImageLoad(SDL_Event* e, SDL_Surface** surface){
    if( e->type == SDL_KEYDOWN ){
        //Select surfaces based on key press
        switch( e->key.keysym.sym ){
            case SDLK_UP:
            loadMedia(image_name[IMAGEM_UP], surface);
            break;

            case SDLK_DOWN:
            loadMedia(image_name[IMAGEM_DOWN], surface);
            break;

            default:
            loadMedia(image_name[IMAGEM_DEFAULT], surface);
            break;

        }

    }

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
//    SDL_FreeSurface(*surface);
//    *surface = NULL;

    //Destroy window
    SDL_DestroyWindow(gwindow);
    gwindow_surface = NULL;

    //Quit SDL Subsystems
    SDL_Quit();
}


int XMAIN(){
    initSDL();
    SDL_Event e;

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

        //Render texture
        //Render texture to screen
        gTexture = loadTexture(image_name[IMAGEM_DEFAULT]);
        SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );

        //Render red filled quad
        SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );        
        SDL_RenderFillRect( gRenderer, &fillRect );

        //Viewport
//        SDL_Rect topleft_viewport = {0, 0, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2};
//        SDL_RenderSetViewport(gRenderer, &topleft_viewport);

        //Render green outlined quad
        SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );        
        SDL_RenderDrawRect( gRenderer, &outlineRect );

        //Draw blue horizontal line
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );        
        SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
        SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, SCREEN_WIDTH / 2);
        //Update screen
        SDL_RenderPresent( gRenderer );
    }

    closeSDL();
    return 0;
}

//Todo: create an function to handle the event logic
//TODO acabar com todas as variáveis globais
