#include <iostream>
#include "SDL.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr <<"SDL Cannot be initialize! SDL_Error :" << SDL_GetError() << '\n';
        return -1;
    }

    //SDL window
    SDL_Window* window = SDL_CreateWindow("Testing_sdl", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL window cannot be created! SDL_Error : " << SDL_GetError() << '\n';
        SDL_Quit();
        return -1;
    }

    //Get window surfacel
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

    //fill surface with color
    SDL_FillRect(screenSurface, nullptr,  SDL_MapRGB(screenSurface->format, 255, 255, 0));
    SDL_UpdateWindowSurface(window);
    SDL_Delay(5000);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}
