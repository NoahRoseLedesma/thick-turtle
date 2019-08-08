//
// Created by stott on 8/2/19.
//
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include "map.h"

#define SIN60 0.8660254038
#define ROOT3 1.732050808

int main(){

    auto gameMap = new Map(50);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML OpenGL");
    window.clear();

    auto coord1 = AxialCoordinate(2,-1);
    auto tile1 = Tile(gameMap, coord1);
    window.draw(tile1);
    auto coord = AxialCoordinate(4,0);
    auto tile = new Tile(gameMap, coord);
    window.draw(*tile);

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