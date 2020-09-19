#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "commonHeader.hpp"

int main() {
    std::vector<int> v(SCREEN_WIDTH / 2);
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
                // getchar();
                int i, j, hCnt, h;
                int increment[20], k;
                for (h = 1, i = 0; h < v.size(); i++) {
                    increment[i] = h;
                    h = 3 * h + 1;
                }
                for (i--; i >= 0; i--) {
                    h = increment[i];
                    for (hCnt = h; hCnt < 2 * h; hCnt++) {
                        for (j = hCnt; j < v.size();) {
                            int temp = v.at(j);
                            k = j;
                            while (k - h >= 0 && temp < v.at(k - h)) {
                                v.at(k) = v.at(k - h);
                                SDL_Delay(2);
                                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF,
                                                       0xFF, 0xFF);
                                SDL_RenderClear(gRenderer);
                                SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF,
                                                       0x00, 0xFF);
                                int z = k - h;
                                fillRectangle(gRenderer, rectangle, v, z, k);
                                SDL_RenderPresent(gRenderer);
                                k -= h;
                            }
                            v.at(k) = temp;
                            j += h;
                        }
                    }
                }
                for (size_t i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2) {
                    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
                    rectangle[i] = {static_cast<int>(j),
                                    SCREEN_HEIGHT - v.at(i), 2, v.at(i)};
                    SDL_RenderFillRect(gRenderer, &rectangle[i]);
                    SDL_Delay(1);
                    SDL_RenderPresent(gRenderer);
                }
                for (size_t i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2) {
                    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                    rectangle[i] = {static_cast<int>(j),
                                    SCREEN_HEIGHT - v.at(i), 2, v.at(i)};
                    SDL_RenderFillRect(gRenderer, &rectangle[i]);
                    SDL_Delay(1);
                    SDL_RenderPresent(gRenderer);
                }
            }
        }
    }
    close();
    return 0;
}