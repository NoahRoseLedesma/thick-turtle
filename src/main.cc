//
// Created by stott on 8/2/19.
//
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include "tile.h"

#define SIN60 0.8660254038
#define ROOT3 1.732050808

int main(){

    Map gameMap;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML OpenGL");
    window.clear();

    for (const auto tile : gameMap.getTiles()){
        window.draw(tile);
    }
  
    window.display();
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

    }
    return 0;
}