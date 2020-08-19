//
// Created by harshal on 09/08/20.
//
#include <SDL2/SDL.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <vector>

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 360;

bool init();
void close();

// SDL_Texture *loadTexture(std::string path);

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer;

inline bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }
        gWindow = SDL_CreateWindow("Radix Sort", SDL_WINDOWPOS_CENTERED,
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
                printf("Renderer could not be created! SDL Error: %s\n",
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
                   std::vector<long>& v) {
    for (int i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2) {
        rectangle[i] = {j, static_cast<int>(SCREEN_HEIGHT - v.at(i)), 2,
                        static_cast<int>(v.at(i))};
        SDL_RenderFillRect(renderer, &rectangle[i]);
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

// void fillRectangle(SDL_Renderer *renderer, SDL_Rect *rectangle,
// std::vector<long>& v, int delay);

int main() {
    std::vector<long> v(SCREEN_WIDTH / 2);
    fillRandomElements(v);
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        bool quit = false;
        SDL_Event e;

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_Rect rectangle[SCREEN_WIDTH / 2];
        fillRectangle(gRenderer, rectangle, v);
        SDL_RenderPresent(gRenderer);
        SDL_UpdateWindowSurface(gWindow);
        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT)
                    quit = true;
            }
            // getchar();
            if (!std::is_sorted(v.begin(), v.end())) {
                int d, j, k, factor;
                const int radix = 10;
                const int digits = 10;
                std::queue<long> queues[radix];
                for (d = 0, factor = 1; d < digits; factor *= radix, d++) {
                    for (j = 0; j < static_cast<int>(v.size()); j++) {
                        queues[(v.at(j) / factor) % radix].push(v.at(j));
                        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF,
                                               0xFF);
                        SDL_RenderClear(gRenderer);
                        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00,
                                               0xFF);
                        fillRectangle(gRenderer, rectangle, v, v.at(j));
                        SDL_Delay(5);
                        SDL_RenderPresent(gRenderer);
                    }
                    for (j = k = 0; j < radix; j++) {
                        while (!queues[j].empty()) {
                            v.at(k++) = queues[j].front();
                            queues[j].pop();
                        }
                    }
                    // if(!std::is_sorted(v.begin(),v.end())) break;
                }

                SDL_Delay(200);
            }
            quit = true;
        }
    }
    close();
    return 0;
}
