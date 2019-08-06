//
// Created by stott on 8/2/19.
//
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include "map.h"

#define SIN60 0.8660254038
#define ROOT3 1.732050808

sf::ConvexShape generateHex(double x, double y, double r){
    sf::ConvexShape hex;
    hex.setPointCount(6);
    hex.setPoint(0, sf::Vector2f(x-r, y));
    hex.setPoint(1, sf::Vector2f(x-(r/2), y+(r*SIN60)));
    hex.setPoint(2, sf::Vector2f(x+(r/2), y+(r*SIN60)));
    hex.setPoint(3, sf::Vector2f(x+r, y));
    hex.setPoint(4, sf::Vector2f(x+(r/2), y-(r*SIN60)));
    hex.setPoint(5, sf::Vector2f(x-(r/2), y-(r*SIN60)));

    return hex;
}

std::vector<sf::ConvexShape> GenerateHexGrid(double radius, double screen_width, double screen_height){
    sf::ConvexShape hex;
    std::vector<sf::ConvexShape> grid;

    for (double y = 0; y < screen_height+radius; y+=(radius*ROOT3)) {
        double inverter = 1;
        double offset = 0;
        for (double x = 0; x < screen_width+radius; x+=(1.5 * radius)) {
            hex = generateHex(x, y+offset, radius);
            hex.setFillColor(sf::Color::Red);
            hex.setOutlineColor(sf::Color::Cyan);
            hex.setOutlineThickness(4);
            grid.push_back(hex);
            offset += (inverter * (radius * (ROOT3/2)));
            inverter *= -1;
        }
    }
    return grid;
}

int main(){

    Map gameMap;

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML OpenGL");
    window.clear();

    auto grid = GenerateHexGrid(75, 800, 600);
    for (const auto tile : gameMap.getTiles()){
        window.draw(tile);
    }
    /*window.draw(hex1);
    window.draw(hex2);
    window.draw(hex3);*/
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