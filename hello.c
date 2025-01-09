#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
const int SCREEN_WIDTH = 640*2;
const int SCREEN_HEIGHT = 480*2;

// its a breeze building this program on linux or windows 
#ifdef _WIN32
#define XMAIN WinMain
#elif __linux__
#define XMAIN main
#endif
//
//int XMAIN( int argc, char* args[] )
//{
//    //The window we'll be rendering to
//    SDL_Window* window = NULL;
//
//    //The surface contained by the window
//    SDL_Surface* screenSurface = NULL;
//
//    //Initialize SDL
//    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
//        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
//    }
//    else{
//        //Create window
//        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
//        if( window == NULL ){
//            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
//        }
//        else{
//            //Get window surface
//            screenSurface = SDL_GetWindowSurface( window );
//
//            //Fill the surface white
//            //SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
//
//            //Update the surface
//            SDL_UpdateWindowSurface( window );
//
//            //Hack to get window to stay up
//            SDL_Event e;
//            bool quit = false;
//            while(quit == false){
//                while(SDL_PollEvent(&e)){
//                    if(e.type == SDL_QUIT)
//                        quit = true;
//                }
//            }
//        }
//    }
//
////Destroy window
//    SDL_DestroyWindow( window );
//
//    //Quit SDL subsystems
//    SDL_Quit();
//
//    return 0;
//}
//

SDL_Window* gwindow = NULL;
SDL_Surface* gwindow_surface = NULL;
SDL_Surface* gimage_surface = NULL;


bool initWindow(){
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


bool loadMedia(){
    bool success = true;

    gimage_surface = SDL_LoadBMP("hello.bmp");

    if(gimage_surface == NULL){
        printf( "Unable to load image %s! SDL Error: %s\n",
        "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}


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
    //global variables
//    SDL_Window* gwindow = NULL;
//    SDL_Surface* gwindow_surface = NULL;
//    SDL_Surface* gimage_surface = NULL;

    initWindow();
    loadMedia();
    SDL_BlitSurface(gimage_surface, NULL, gwindow_surface, NULL);
    SDL_UpdateWindowSurface(gwindow);

    //Hack to get window to stay up
    SDL_Event e;
    bool quit = false;
    while(quit == false){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT)
                quit = true;
        }

    }
    closeSDL();

}


