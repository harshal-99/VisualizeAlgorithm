#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <cstdio>
#include <random>
#include <limits>
#include <algorithm>
#include <vector>

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 640;

bool init();
void close();

SDL_Texture *loadTexture(std::string path);

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer;

inline bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }
        gWindow = SDL_CreateWindow("Insertion Sort",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   SCREEN_WIDTH,
                                   SCREEN_HEIGHT,
                                   SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }
    return success;
}

void close()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

int main(int argc, char const *argv[])
{
    std::vector<int> v(SCREEN_WIDTH / 2);
    std::random_device randGen;
    std::mt19937_64 mt(randGen());
    std::uniform_int_distribution<> distribution(1, SCREEN_HEIGHT);
    int count  = 0;
    // std::cout << "Min: " << randGen.min() << "\nMax: " << randGen.max() << "\n";
    for (int i = 0; i < SCREEN_WIDTH / 2; i++)
    {
        v.at(i) = distribution(mt);
        // std::cout << v.at(i) << " ";
    }

    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        bool quit = false;
        SDL_Event e;
        bool sorted = false;

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_Rect rectangle[SCREEN_WIDTH / 2];
        for (int i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2)
        {
            rectangle[i] = {j, SCREEN_HEIGHT - v.at(i), 2, v.at(i)};
            SDL_RenderFillRect(gRenderer, &rectangle[i]);
        }
        SDL_RenderPresent(gRenderer);
        SDL_UpdateWindowSurface(gWindow);
        // SDL_Delay(2000);
        bool once = true;
        here:
        while (!quit)
        {
            if(once) getchar();
            once = false;
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT) quit = true;
            }
            if(!sorted) {
                        for(int i = 0,j,least; i < v.size() - 1; i++) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                    goto here;
                }
                for(j = i + 1,least = i; j < v.size(); j++) {
                    if (e.type == SDL_QUIT) {
                    quit = true;
                    goto here;
                }
                    if(v.at(j) < v.at(least)) least = j;
                    std::swap(v.at(least),v.at(i));
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);
                    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                    for (size_t a = 0, b = 0; a < SCREEN_WIDTH / 2; ++a, b += 2)    {
                        if (e.type == SDL_QUIT) {
                            quit = true;
                            goto here;
                        }
                        if(a == least || a == i) {
                            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
                        }else{
                            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                        }
                        rectangle[a] = {b, SCREEN_HEIGHT - v.at(a), 2, v.at(a)};
                        SDL_RenderFillRect(gRenderer, &rectangle[a]);
                    }
                    SDL_RenderPresent(gRenderer);
                }
            }
                // sorted = true;
                for (size_t a = 0, b = 0; a < SCREEN_WIDTH / 2; ++a, b += 2)    {
                    if (e.type == SDL_QUIT) {
                    quit = true;
                    goto here;
                    }
                    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
                    rectangle[a] = {b, SCREEN_HEIGHT - v.at(a), 2, v.at(a)};
                    SDL_RenderFillRect(gRenderer, &rectangle[a]);
                    SDL_Delay(1);
                    SDL_RenderPresent(gRenderer);
                }
                for (size_t a = 0, b = 0; a < SCREEN_WIDTH / 2; ++a, b += 2)    {
                    if (e.type == SDL_QUIT) {
                    quit = true;
                    goto here;
                    }
                    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                    rectangle[a] = {b, SCREEN_HEIGHT - v.at(a), 2, v.at(a)};
                    SDL_RenderFillRect(gRenderer, &rectangle[a]);
                }
                SDL_RenderPresent(gRenderer);
            }
            
            count++;
            if(count == 2) quit = true; 
        }
    }
    close();
    return 0;
}