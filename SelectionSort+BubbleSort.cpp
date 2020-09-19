#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "commonHeader.hpp"




int main()
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