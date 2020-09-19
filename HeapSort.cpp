#include <iostream>
#include <SDL2/SDL.h>
#include "commonHeader.hpp"
#include <vector>



void moveDown(std::vector<int>& v,int n,int index) {
    int largest = index;
    int l = 2 * index + 1;
    int r = 2 * index + 2;

    if(l < n && v.at(l) > v.at(largest)) {
        largest = l;
    }
    if(r < n && v.at(r) > v.at(largest)) {
        largest = r;
    }
    if(largest != index) {
        std::swap(v.at(index),v.at(largest));
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
        fillRectangle(gRenderer,rectangle,v,index,largest);
        SDL_Delay(5);
        moveDown(v,n,largest);
    }
}



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
                for(auto i = v.size() / 2 - 1 ;i >= 0; i--) {
                    moveDown(v,v.size(),i);
                }
                for(int i = v.size() - 1; i > 0; i--) {
                    std::swap(v.at(0),v.at(i));
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);
                    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                    fillRectangle(gRenderer,rectangle,v,v.at(0),i);
                    SDL_Delay(5);
                    SDL_RenderPresent(gRenderer);

                    moveDown(v,i,0);
                }
                for (size_t i = 0, j = 0; i < SCREEN_WIDTH / 2; ++i, j += 2)
                {
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
                SDL_Delay(200);
            }
        }
    }
    close();
    return 0;
}
