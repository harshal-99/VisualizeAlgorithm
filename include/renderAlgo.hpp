//
// Created by harshal on 9/27/20.
//

#ifndef VISUALIZEALGORITHM_RENDERALGO_HPP
#define VISUALIZEALGORITHM_RENDERALGO_HPP

#include <SFML/Graphics.hpp>
#include <chrono>
#include <numeric>
#include <random>

class RenderAlgo {
   private:
    sf::RenderWindow*               mWindow;
    std::vector<sf::RectangleShape> rect;
    std::vector<int>                elements;
    sf::Event                       event;
    std::chrono::milliseconds       delay;
    sf::Vector2<unsigned int>       mSize;
    //std::this_thread::sleep_for(delay);

   public:
    RenderAlgo(sf::RenderWindow* window);
    void swap(int i, int j);
    void shuffelElements();
};

#endif  // VISUALIZEALGORITHM_RENDERALGO_HPP
