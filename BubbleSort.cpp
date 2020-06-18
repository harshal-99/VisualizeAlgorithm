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

bool init()
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
        gWindow = SDL_CreateWindow("Bubble Sort",
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
        while (!quit)
        {
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                    quit = true;
            }

            size_t row, col;
            bool swapped;

            if (!sorted)
            {
                for (row = 0; row < v.size(); ++row)
                {
                    swapped = false;
                    if (e.type == SDL_QUIT)
                    {
                        break;
                    }
                    for (col = 0; col < v.size() - row - 1; ++col)
                    {
                        if (e.type == SDL_QUIT)
                        {
                            break;
                        }
                        if (v.at(col) > v.at(col + 1))
                        {
                            std::swap(v.at(col), v.at(col + 1));
                            swapped = true;
                            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                            SDL_RenderClear(gRenderer);
                            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                            for (size_t i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2)
                            {
                                if (i == col || i == col + 1)
                                {
                                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
                                }
                                else
                                {
                                    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                                }
                                rectangle[i] = {j, SCREEN_HEIGHT - v.at(i), 2, v.at(i)};
                                SDL_RenderFillRect(gRenderer, &rectangle[i]);
                            }
                            SDL_RenderPresent(gRenderer);
                        }
                    }
                    if (!swapped)
                        break;
                }
                // std::cout << "Out of Sorting Loop\n";
                for (size_t i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2)
                {
                    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
                    rectangle[i] = {j, SCREEN_HEIGHT - v.at(i), 2, v.at(i)};
                    SDL_RenderFillRect(gRenderer, &rectangle[i]);
                    SDL_Delay(1);
                    SDL_RenderPresent(gRenderer);
                }
                for (size_t i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2)
                {
                    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                    rectangle[i] = {j, SCREEN_HEIGHT - v.at(i), 2, v.at(i)};
                    SDL_RenderFillRect(gRenderer, &rectangle[i]);
                    SDL_Delay(1);
                    SDL_RenderPresent(gRenderer);
                }
                sorted = true;
            }

        }
    }
    close();
    return 0;
}
