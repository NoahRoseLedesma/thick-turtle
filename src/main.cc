//
// Created by stott on 8/2/19.
//
#include <iostream>

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include "game.h"

unsigned int ValidateUserInput(int argc, char **argv) {
  // Gives a default value in the even the user does not specify a radius
  if (argc < 2) {
    return 8;
    // Critical error in the event the user enters too many args
  } else if (argc > 2) {
    std::cout << "Too many arguments entered" << std::endl
              << "Please try again and enter the desired radius of the game map"
              << std::endl;
    exit(2);

    // Else just return the radius the user specified;
  } else {
    // Throws an exception if the string cannot be converted to an unsigned int
    // i.e. radius < 0 or argv[1] is a string like "hello"
    try {
      return std::stoul(argv[1]);
    }
    catch (std::invalid_argument &e) {
      std::cout << "Invalid radius argument" << std::endl
                << "Please try again and enter a valid positive integer"
                << std::endl;
      exit(3);
    }
  }
}

int main(int argc, char **argv) {
  Game game;
  unsigned int radius = ValidateUserInput(argc, argv);
  game.InitWindow(800, 850);
  game.InitMap(radius);
  game.InitCamera();
  game.Run();
  return 0;
}
