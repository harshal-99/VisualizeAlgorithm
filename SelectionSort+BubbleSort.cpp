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
        gWindow = SDL_CreateWindow("Selection Sort",
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
    int count  = 0;
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
        // for (int i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2)
        // {
        //     rectangle[i] = {j, SCREEN_HEIGHT - v.at(i), 2, v.at(i)};
        //     SDL_RenderFillRect(gRenderer, &rectangle[i]);
        // }
        fillRectangle(gRenderer,rectangle,v);
        SDL_RenderPresent(gRenderer);
        SDL_UpdateWindowSurface(gWindow);
        // SDL_Delay(2000);
        // bool once = true;
        while (!quit) {
            // if(once) getchar();
            // once = false;
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT) quit = true;
            }
            if(!std::is_sorted(v.begin(),v.end())) {
                for(int i = 0,j,least; i < v.size() - 1; i++) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    for(j = i + 1,least = i; j < v.size(); j++) {
                        if (e.type == SDL_QUIT) {
                            quit = true;
                        }
                        if(v.at(j) < v.at(least)) least = j;
                        if( i != least) std::swap(v.at(least),v.at(i));
                        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                        SDL_RenderClear(gRenderer);
                        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                        fillRectangle(gRenderer,rectangle,v,least,i);
                        SDL_RenderPresent(gRenderer);
                    }
                }

            }
            if(std::is_sorted(v.begin(),v.end())) {
                quit = true;
            }else{
                for(int i =0; i < v.size() ; i++) {
                    for(int j = 0; j < v.size() - i - 1; j++) {
                        if(v.at(j) > v.at(j + 1)) {
                            std::swap(v.at(j),v.at(j+1));
                            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                            SDL_RenderClear(gRenderer);
                            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                            int z = j+1;
                            fillRectangle(gRenderer,rectangle,v,j,z);
                        }
                        SDL_RenderPresent(gRenderer);
                    }
                }
            }
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
        }
    }
    close();
    std::cout << "\nNumber of time Algorithm had to be repeatedly execute because it was not sorted " << count << "\n";
    return 0;
}