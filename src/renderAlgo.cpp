#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "llvmlibc-callee-namespace"
//
// Created by harshal on 9/27/20.
//

#include "../include/renderAlgo.hpp"
RenderAlgo::RenderAlgo(sf::RenderWindow* window): mWindow(window), event{} , delay{}{
    rect.reserve(window->getSize().y);
    elements.reserve(window->getSize().y);
    std::iota(elements.begin(),elements.end(),1);
    mSize = mWindow->getSize();
}
void RenderAlgo::swap(int i, int j) {

}
void RenderAlgo::shuffelElements() {
    std::random_device randGen;
    std::mt19937_64 mt(randGen());
    std::shuffle(elements.begin(),elements.end(), mt);
    sf::Vector2f rectSize;
    for(size_t i{}; i < elements.size(); i++) {
        rectSize.x = mSize.x;
//        rectSize.y =
//        rect.at(i).setSize()
    }
}

#pragma clang diagnostic pop