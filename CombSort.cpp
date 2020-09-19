#include <SDL2/SDL.h>

#include <vector>

#include "commonHeader.hpp"


int main()
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
            // if(once) getchar();
            // once = false;
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT) quit = true;
            }
            if(!std::is_sorted(v.begin(),v.end())) {
                // getchar();
                int step = v.size(),i,j,k;
                while((step = int(step/1.3)) > 1) {
                    for(j = v.size() - 1; j >= step; j--) {
                        k = j - step;
                        if(v.at(j) < v.at(k)){
                            std::swap(v.at(j),v.at(k));
                            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                            SDL_RenderClear(gRenderer);
                            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                            fillRectangle(gRenderer,rectangle,v,j,k);
                            SDL_RenderPresent(gRenderer);
                        }
                    }
                    bool again = true;
                    for(i = 0; i < v.size() - 1 && again; i++) {
                        for(j = v.size() - 1,again = false; j > i; --j) {
                            if(v.at(j) < v.at(j - 1)) {
                                std::swap(v.at(j),v.at(j - 1));
                                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                                SDL_RenderClear(gRenderer);
                                SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                                int z = j - 1;
                                fillRectangle(gRenderer,rectangle,v,j,z);
                                SDL_RenderPresent(gRenderer);
                                again = true;
                            }
                        }
                    }
                }
//                // SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//                // SDL_RenderClear(gRenderer);
//                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
//                fillRectangle(gRenderer,rectangle,v,1);
//                SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
//                fillRectangle(gRenderer,rectangle,v);
//                SDL_RenderPresent(gRenderer);
                for (size_t n = 0, o = 0; n < SCREEN_WIDTH / 2; ++n, o += 2) {
                    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
                    rectangle[n] = {static_cast<int>(o), SCREEN_HEIGHT - v.at(n), 2, v.at(n)};
                    SDL_RenderFillRect(gRenderer, &rectangle[n]);
                    SDL_Delay(1);
                    SDL_RenderPresent(gRenderer);
                }
                for (size_t n = 0, o = 0; n < SCREEN_WIDTH / 2; ++n, o += 2)
                {
                    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                    rectangle[n] = {static_cast<int>(o), SCREEN_HEIGHT - v.at(n), 2, v.at(n)};
                    SDL_RenderFillRect(gRenderer, &rectangle[n]);
                    SDL_Delay(1);
                    SDL_RenderPresent(gRenderer);
                }
                SDL_Delay(200);
            }

        }
    }
    close();
    return 0;
}