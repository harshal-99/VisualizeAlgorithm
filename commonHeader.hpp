#ifndef VISUALIZEALGORITHM_COMMONHEADER_HPP
#define VISUALIZEALGORITHM_COMMONHEADER_HPP
#include <SDL2/SDL.h>

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <random>
#include <string>
#include <vector>

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 360;
SDL_Rect rectangle[SCREEN_WIDTH / 2];

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer;


bool init();
void close();

bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }
        gWindow = SDL_CreateWindow("Bubble Sort", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
            printf("Window could not be created! SDL Error: %s\n",
                   SDL_GetError());
            success = false;
        } else {
            gRenderer =
                SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == nullptr) {
                printf(
                    "Renderer could not be created! SDL "
                    "Error: %s\n",
                    SDL_GetError());
                success = false;
            } else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }
    return success;
}

void close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void fillRandomElements(std::vector<int>& v) {
    std::random_device randGen;
    std::mt19937_64 mt(randGen());
    for (int i = 1; i <= SCREEN_WIDTH / 2; i++) {
        v.at(i - 1) = i;
    }
    std::shuffle(v.begin(), v.end(), mt);
}

void fillRectangle(SDL_Renderer *Renderer,SDL_Rect * rectangle,std::vector<int>& v) {
    for (int i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2)
    {
        rectangle[i] = {j, SCREEN_HEIGHT - v.at(i), 2, v.at(i)};
        SDL_RenderFillRect(Renderer, &rectangle[i]);
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

void fillRectangle(SDL_Renderer *Renderer,SDL_Rect * Rectangle,std::vector<int>& v,int& least,int& other) {

    for (int i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2)
    {
        if(i == least || i == other) {
            SDL_SetRenderDrawColor(Renderer, 0xFF, 0x00, 0x00, 0xFF);
        }else{
            SDL_SetRenderDrawColor(Renderer, 0x00, 0xFF, 0x00, 0xFF);
        }
        rectangle[i] = {j, SCREEN_HEIGHT - v.at(i), 2, v.at(i)};
        SDL_RenderFillRect(gRenderer, &Rectangle[i]);
    }
}

void fillRectangle(SDL_Renderer* renderer,
                   SDL_Rect* rectangle,
                   std::vector<long>& v,
                   long least) {
    for (long i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2) {
        if (i == least) {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        } else {
            SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        }
        rectangle[i] = {static_cast<int>(j),
                        static_cast<int>(SCREEN_HEIGHT - v.at(i)), 2,
                        static_cast<int>(v.at(i))};
        SDL_RenderFillRect(renderer, &rectangle[i]);
    }
}

void fillRectangle(SDL_Renderer* renderer,
                   SDL_Rect* rectangle,
                   std::vector<long>& v) {
    for (int i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2) {
        rectangle[i] = {j, static_cast<int>(SCREEN_HEIGHT - v.at(i)), 2,
                        static_cast<int>(v.at(i))};
        SDL_RenderFillRect(renderer, &rectangle[i]);
    }
}

void fillRandomElements(std::vector<long>& v) {
    std::random_device randGen;
    std::mt19937_64 mt(randGen());
    for (int i = 0; i < SCREEN_WIDTH / 2; i++) {
        v.at(i) = i;
    }
    std::shuffle(v.begin(), v.end(), mt);
}

void fillRectangle(SDL_Renderer* renderer,
                   SDL_Rect* rectangle,
                   std::vector<long>& v,
                   int delay) {
    for (size_t a = 0, b = 0; a < SCREEN_WIDTH / 2; a++, b += 2) {
        rectangle[a] = {static_cast<int>(b),
                        static_cast<int>(SCREEN_HEIGHT - v.at(a)), 2,
                        static_cast<int>(v.at(a))};
        SDL_RenderFillRect(renderer, &rectangle[a]);
        SDL_RenderPresent(renderer);
        SDL_Delay(delay);
    }
}

#endif  // VISUALIZEALGORITHM_COMMONHEADER_HPP
