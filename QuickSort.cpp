//
// Created by harshal on 09/08/20.
//
#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include <algorithm>
#include <vector>

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 360;
SDL_Rect rectangle[SCREEN_WIDTH / 2];
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
        gWindow = SDL_CreateWindow("Quick Sort",
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


void quicksort(std::vector<int>& v,int first,int last){
    int lower = first + 1, upper = last;
    std::swap(v.at(first),v.at((first+last) / 2));
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
    fillRectangle(gRenderer,rectangle,v,v.at(first),v.at((first + last) / 2));
    SDL_Delay(5);
    SDL_RenderPresent(gRenderer);

    int bound = v.at(first);
    while(lower <= upper) {
        while(bound > v.at(lower) ) lower++;

        while (bound < v.at(upper)) upper--;

        if(lower < upper) {
            int a = lower++,b = upper--;
            std::swap(v.at(a),v.at(b));
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
            fillRectangle(gRenderer,rectangle,v,v.at(a),v.at(b));
            SDL_RenderPresent(gRenderer);
            SDL_Delay(4);
        }else lower++;
    }
    std::swap(v.at(upper),v.at(first));
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
    fillRectangle(gRenderer,rectangle,v,v.at(upper),v.at(first));
    SDL_RenderPresent(gRenderer);
    SDL_Delay(5);

    if(first < upper - 1) quicksort(v,first,upper-1);
    if(upper+1 < last) quicksort(v,upper+1,last);
}

void quicksort(std::vector<int>& v,int n) {
    int i,max;
    if(n < 2) return;
    for(i = 1,max = 0; i < n; i++) {
        if(v.at(max) < v.at(i)) max = i;
    }
    std::swap(v.at(n-1),v.at(max));
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
    fillRectangle(gRenderer,rectangle,v,v.at(n-1),v.at(max));
    SDL_RenderPresent(gRenderer);
    SDL_Delay(5);
    quicksort(v,0,n-2);
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
                quicksort(v,v.size());
            }
            quit = true;
            // SDL_RenderClear(gRenderer);
            // SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
            // fillRectangle(gRenderer,rectangle,v,1);
            // SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
            // fillRectangle(gRenderer,rectangle,v);
            // SDL_RenderPresent(gRenderer);
            // SDL_Delay(200);
        }
    }
    close();
    std::cout << "Sorted\n";
    return 0;
}
