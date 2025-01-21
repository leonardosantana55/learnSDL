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
SDL_Surface* gimage_surface = NULL;


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
            //Get window surface
            gwindow_surface = SDL_GetWindowSurface( gwindow );
        }
    }

    return success;
}


bool loadMedia(char* name, SDL_Surface** surface){
    bool success = true;

    SDL_Surface* temp_surface = SDL_LoadBMP(name);

    *surface = SDL_ConvertSurface(temp_surface, gwindow_surface->format, 0);
    
    SDL_FreeSurface(temp_surface);

    if(surface == NULL){
        printf( "Unable to load image %s! SDL Error: %s\n",
        name, SDL_GetError() );
        success = false;
    }
    return success;
}

// Acho que a maneira correta de organizar a lógica de eventos é recebendo como parametro
// o objeto que será modificado pelo evento. E talvez a flag quit deve estar em um função
//separada.

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


//void keyPressEventLogic(SDL_Event* e, bool* quit){
//    while(SDL_PollEvent(e)){
//        if(e->type == SDL_TEXTINPUT){
//            printf("%s\n", e->text.text);
//        }
//
//        if( e->type == SDL_KEYDOWN ){
//            //Select surfaces based on key press
//            switch( e->key.keysym.sym ){
//                case SDLK_UP:
//                loadMedia(image_name[IMAGEM_UP]);
//                break;
//
//                case SDLK_DOWN:
//                loadMedia(image_name[IMAGEM_DOWN]);
//                break;
//
//                default:
//                loadMedia(image_name[IMAGEM_DEFAULT]);
//                break;
//
//            }
//
//        }
//
//        if(e->type == SDL_QUIT){
//            *quit = true;
//        }
//
//    }
//
//}


void closeSDL(){
    //Dealocate Surface
    SDL_FreeSurface(gimage_surface);
    gimage_surface = NULL;

    //Destroy window
    SDL_DestroyWindow(gwindow);
    gwindow_surface = NULL;

    //Quit SDL Subsystems
    SDL_Quit();
}


int XMAIN(){
    initSDL();
    SDL_Event e;
    SDL_Surface* image_surface = NULL;

    // main loop
    bool quit = false;
    while(!quit){
//        keyPressEventLogic(&e, &quit);
        // event logic loop
        while(SDL_PollEvent(&e)){
            eventLogicQuit(&e, &quit);
            eventLogicImageLoad(&e, &image_surface);
            eventLogicKeyPrint(&e);
            }

//        loadMedia(image_name[IMAGEM_DEFAULT], image_surface);

        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = SCREEN_WIDTH;
        stretchRect.h = SCREEN_HEIGHT;
        printf("%s", image_surface);
        SDL_BlitScaled(image_surface, NULL, gwindow_surface, &stretchRect);
        SDL_UpdateWindowSurface(gwindow);
    }

    closeSDL();
}

//Todo: create an function to handle the event logic
