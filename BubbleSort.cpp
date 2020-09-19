#include <SDL2/SDL.h>
#include "commonHeader.hpp"


#include <vector>

int main() {
    std::vector<int> v(SCREEN_WIDTH / 2);
    fillRandomElements(v);

    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        bool quit = false;
        SDL_Event e;
        bool sorted = false;

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_Rect rectangle[SCREEN_WIDTH / 2];
        for (int i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2) {
            rectangle[i] = {j, SCREEN_HEIGHT - v.at(i), 2, v.at(i)};
            SDL_RenderFillRect(gRenderer, &rectangle[i]);
        }
        SDL_RenderPresent(gRenderer);
        SDL_UpdateWindowSurface(gWindow);
        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT)
                    quit = true;
            }

            size_t row, col;
            bool swapped;

            if (!sorted) {
                for (row = 0; row < v.size(); ++row) {
                    swapped = false;
                    if (e.type == SDL_QUIT) {
                        break;
                    }
                    for (col = 0; col < v.size() - row - 1; ++col) {
                        if (e.type == SDL_QUIT) {
                            break;
                        }
                        if (v.at(col) > v.at(col + 1)) {
                            std::swap(v.at(col), v.at(col + 1));
                            swapped = true;
                            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF,
                                                   0xFF);
                            SDL_RenderClear(gRenderer);
                            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00,
                                                   0xFF);
                            for (size_t i = 0, j = 0; i < SCREEN_WIDTH / 2;
                                 ++i, j += 2) {
                                if (i == col || i == col + 1) {
                                    SDL_SetRenderDrawColor(gRenderer, 0xFF,
                                                           0x00, 0x00, 0xFF);
                                } else {
                                    SDL_SetRenderDrawColor(gRenderer, 0x00,
                                                           0xFF, 0x00, 0xFF);
                                }
                                rectangle[i] = {static_cast<int>(j),
                                                SCREEN_HEIGHT - v.at(i), 2,
                                                v.at(i)};
                                SDL_RenderFillRect(gRenderer, &rectangle[i]);
                            }
                            SDL_RenderPresent(gRenderer);
                        }
                    }
                    if (!swapped)
                        break;
                }
                // std::cout << "Out of Sorting Loop\n";
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
                sorted = true;
            }
        }
    }
    close();
    return 0;
}