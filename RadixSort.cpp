#include <SDL2/SDL.h>
#include <queue>
#include <string>
#include <vector>
#include "commonHeader.hpp"

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
