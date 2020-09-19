#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "commonHeader.hpp"

void quicksort(std::vector<int>& v, int first, int last) {
    int lower = first + 1, upper = last;
    std::swap(v.at(first), v.at((first + last) / 2));
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
    fillRectangle(gRenderer, rectangle, v, v.at(first),
                  v.at((first + last) / 2));
    SDL_Delay(5);
    SDL_RenderPresent(gRenderer);

    int bound = v.at(first);
    while (lower <= upper) {
        while (bound > v.at(lower))
            lower++;

        while (bound < v.at(upper))
            upper--;

        if (lower < upper) {
            int a = lower++, b = upper--;
            std::swap(v.at(a), v.at(b));
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
            fillRectangle(gRenderer, rectangle, v, v.at(a), v.at(b));
            SDL_RenderPresent(gRenderer);
            SDL_Delay(4);
        } else
            lower++;
    }
    std::swap(v.at(upper), v.at(first));
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
    fillRectangle(gRenderer, rectangle, v, v.at(upper), v.at(first));
    SDL_RenderPresent(gRenderer);
    SDL_Delay(5);

    if (first < upper - 1)
        quicksort(v, first, upper - 1);
    if (upper + 1 < last)
        quicksort(v, upper + 1, last);
}

void quicksort(std::vector<int>& v, int n) {
    int i, max;
    if (n < 2)
        return;
    for (i = 1, max = 0; i < n; i++) {
        if (v.at(max) < v.at(i))
            max = i;
    }
    std::swap(v.at(n - 1), v.at(max));
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
    fillRectangle(gRenderer, rectangle, v, v.at(n - 1), v.at(max));
    SDL_RenderPresent(gRenderer);
    SDL_Delay(5);
    quicksort(v, 0, n - 2);
}

int main(int argc, char const* argv[]) {
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
                quicksort(v, v.size());
            }
            quit = true;
            for (size_t i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2) {
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
                rectangle[i] = {static_cast<int>(j), SCREEN_HEIGHT - v.at(i), 2,
                                v.at(i)};
                SDL_RenderFillRect(gRenderer, &rectangle[i]);
                SDL_Delay(1);
                SDL_RenderPresent(gRenderer);
            }
            for (size_t i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2) {
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                rectangle[i] = {static_cast<int>(j), SCREEN_HEIGHT - v.at(i), 2,
                                v.at(i)};
                SDL_RenderFillRect(gRenderer, &rectangle[i]);
                SDL_Delay(1);
                SDL_RenderPresent(gRenderer);
            }
            SDL_Delay(200);
        }
    }
    close();
    std::cout << "Sorted\n";
    return 0;
}
