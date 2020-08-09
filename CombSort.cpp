#include <iostream>
#include <SDL2/SDL.h>
#include <cstdio>
#include <random>
#include <algorithm>
#include <vector>

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 360;

bool init();
void close();

// SDL_Texture *loadTexture(std::string path);

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
        gWindow = SDL_CreateWindow("CombSort Sort",
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

void fillRandomElements(std::vector<int>& v) {
    std::random_device randGen;
    std::mt19937_64 mt(randGen());
    for (int i = 1; i <= SCREEN_WIDTH / 2; i++) {
        v.at(i-1) = i;
    }
    std::shuffle(v.begin(),v.end(),mt);
}

void fillRectangle(SDL_Renderer *Renderer,SDL_Rect * rectangle,std::vector<int>& v) {
    for (int i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2)
    {
        rectangle[i] = {j, SCREEN_HEIGHT - v.at(i), 2, v.at(i)};
        SDL_RenderFillRect(Renderer, &rectangle[i]);
    }
}

void fillRectangle(SDL_Renderer *Renderer,SDL_Rect * rectangle,std::vector<int>& v,int& least,int& other) {

    for (int i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2)
    {
        if(i == least || i == other) {
            SDL_SetRenderDrawColor(Renderer, 0xFF, 0x00, 0x00, 0xFF);
        }else{
            SDL_SetRenderDrawColor(Renderer, 0x00, 0xFF, 0x00, 0xFF);
        }
        rectangle[i] = {j, SCREEN_HEIGHT - v.at(i), 2, v.at(i)};
        SDL_RenderFillRect(gRenderer, &rectangle[i]);
    }
}


void fillRectangle(SDL_Renderer *Renderer,SDL_Rect *rectangle,std::vector<int>& v,int delay) {
    for (size_t a = 0, b = 0; a < SCREEN_WIDTH / 2; a++, b += 2)    {
        rectangle[a] = {static_cast<int>(b), SCREEN_HEIGHT - v.at(a), 2, v.at(a)};
        SDL_RenderFillRect(Renderer, &rectangle[a]);
        SDL_RenderPresent(Renderer);
        SDL_Delay(delay);
    }
}



int main(int argc, char const *argv[])
{
    std::vector<int> v(SCREEN_WIDTH / 2);
    fillRandomElements(v);
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        bool quit = false;
        SDL_Event e;

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_Rect rectangle[SCREEN_WIDTH / 2];
        fillRectangle(gRenderer,rectangle,v);
        SDL_RenderPresent(gRenderer);
        SDL_UpdateWindowSurface(gWindow);
        while (!quit) {
            // if(once) getchar();
            // once = false;
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT) quit = true;
            }
            if(!std::is_sorted(v.begin(),v.end())) {
                // getchar();
                int step = v.size(),i,j,k;
                while((step = int(step/1.3)) > 1) {
                    for(j = v.size() - 1; j >= step; j--) {
                        k = j - step;
                        if(v.at(j) < v.at(k)){
                            std::swap(v.at(j),v.at(k));
                            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                            SDL_RenderClear(gRenderer);
                            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                            fillRectangle(gRenderer,rectangle,v,j,k);
                            SDL_RenderPresent(gRenderer);
                        }
                    }
                    bool again = true;
                    for(i = 0; i < v.size() - 1 && again; i++) {
                        for(j = v.size() - 1,again = false; j > i; --j) {
                            if(v.at(j) < v.at(j - 1)) {
                                std::swap(v.at(j),v.at(j - 1));
                                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                                SDL_RenderClear(gRenderer);
                                SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                                int z = j - 1;
                                fillRectangle(gRenderer,rectangle,v,j,z);
                                SDL_RenderPresent(gRenderer);
                                again = true;
                            }
                        }
                    }
                }
//                // SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//                // SDL_RenderClear(gRenderer);
//                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
//                fillRectangle(gRenderer,rectangle,v,1);
//                SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
//                fillRectangle(gRenderer,rectangle,v);
//                SDL_RenderPresent(gRenderer);
                for (size_t i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2) {
                    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
                    rectangle[i] = {static_cast<int>(j), SCREEN_HEIGHT - v.at(i), 2, v.at(i)};
                    SDL_RenderFillRect(gRenderer, &rectangle[i]);
                    SDL_Delay(1);
                    SDL_RenderPresent(gRenderer);
                }
                for (size_t i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2)
                {
                    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                    rectangle[i] = {static_cast<int>(j), SCREEN_HEIGHT - v.at(i), 2, v.at(i)};
                    SDL_RenderFillRect(gRenderer, &rectangle[i]);
                    SDL_Delay(1);
                    SDL_RenderPresent(gRenderer);
                }
                SDL_Delay(200);
            }

        }
    }
    close();
    return 0;
}