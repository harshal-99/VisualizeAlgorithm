#include <iostream>
#include <SDL2/SDL.h>
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
        gWindow = SDL_CreateWindow("Shell Sort",
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
    for (int i = 1; i <= SCREEN_WIDTH / 2; i++)
    {
        v.at(i-1) = i;
    }
    std::shuffle(v.begin(),v.end(),mt);
}

void fillRectangle(SDL_Renderer *gRenderer,SDL_Rect * rectangle,std::vector<int>& v) {
    for (int i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2)
    {
        rectangle[i] = {j, SCREEN_HEIGHT - v.at(i), 2, v.at(i)};
        SDL_RenderFillRect(gRenderer, &rectangle[i]);
    }
}

void fillRectangle(SDL_Renderer *gRenderer,SDL_Rect * rectangle,std::vector<int>& v,int& least,int& other) {

    for (int i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2)
    {
        if(i == least || i == other) {
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        }else{
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
        }
        rectangle[i] = {j, SCREEN_HEIGHT - v.at(i), 2, v.at(i)};
        SDL_RenderFillRect(gRenderer, &rectangle[i]);
    }
}


void fillRectangle(SDL_Renderer *gRenderer,SDL_Rect *rectangle,std::vector<int>& v,int delay) {
    for (size_t a = 0, b = 0; a < SCREEN_WIDTH / 2; a++, b += 2)    {
        rectangle[a] = {static_cast<int>(b), SCREEN_HEIGHT - v.at(a), 2, v.at(a)};
        SDL_RenderFillRect(gRenderer, &rectangle[a]);
        SDL_RenderPresent(gRenderer);
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
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT) quit = true;
            }
            // getchar();
            if(!std::is_sorted(v.begin(),v.end())) {
                // getchar();
                int i,j,hCnt,h;
                int increment[20],k;
                for(h = 1,i = 0; h < v.size();i++) {
                    increment[i] = h;
                    h = 3 * h + 1;
                }
                for(i--;i >=0;i--) {
                    h = increment[i];
                    for(hCnt = h;hCnt < 2*h;hCnt++) {
                        for(j = hCnt; j < v.size();) {
                            int temp = v.at(j);
                            k = j;
                            while(k - h >=0 && temp < v.at(k-h)) {
                                v.at(k) = v.at(k-h);
                                SDL_Delay(2);
                                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                                SDL_RenderClear(gRenderer);
                                SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                                int z = k - h;
                                fillRectangle(gRenderer,rectangle,v,z,k);
                                SDL_RenderPresent(gRenderer);
                                k -= h;
                            }
                            v.at(k) = temp;
                            j += h;
                        }
                    }
                }
                for (size_t i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2)
                {
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
                // SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                // SDL_RenderClear(gRenderer);
                // SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
                // fillRectangle(gRenderer,rectangle,v,1);
                // SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                // fillRectangle(gRenderer,rectangle,v);
                // SDL_RenderPresent(gRenderer);
                // SDL_Delay(200);
            }

        }
    }
    close();
    return 0;
}