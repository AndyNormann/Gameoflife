#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string.h>
#include "Bitmap.cpp"

#define SQSZ 40
#define HEIGHT 2000
#define WIDTH 2000
#define SQX WIDTH / SQSZ
#define SQY HEIGHT / SQSZ

int main() {

  // Init
  sf::RenderWindow window(sf::VideoMode(HEIGHT, WIDTH), "SFML");
  window.setFramerateLimit(30);

  Bitmap grid(SQX, SQY);
  Bitmap next_grid(SQX, SQY);

  bool running = false;

  int timestep = 75;

  clock_t beginFrame = clock();
  clock_t deltaTime;

  // Main loop
  while (window.isOpen()) {
    // Handle keyboard/mouse events
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::KeyPressed:
        switch (event.key.code) {
          case sf::Keyboard::Escape:
            window.close();
            break;
          case sf::Keyboard::Space:
            running = !running;
            break;
          case sf::Keyboard::Up:
            if (timestep > 25) timestep -= 25;
            break;
          case sf::Keyboard::Down:
            timestep += 25;
            break;
          case sf::Keyboard::C:
            memset(grid.data, 0, grid.size);
        }
        break;
      case sf::Event::MouseButtonPressed:
        grid.toggle2d(event.mouseButton.x / SQSZ, event.mouseButton.y / SQSZ);
        break;
      }

      if (event.type == sf::Event::Closed)
        window.close();
    }

    auto c = [&](int x, int y) {
      return x > 0 && x < SQX && y > 0 && y < SQY && grid.get2d(x, y);
    };

    // Advance grid / Deal with timestep 
    deltaTime = (clock() - beginFrame) / 1000;
    if (running && deltaTime > timestep) {
      beginFrame = clock();

      for (int i = 0; i < SQX; i++) {
        for (int j = 0; j < SQY; j++) {
          int cur = 
            c(i-1,j-1)+c(i,j-1)+c(i+1,j-1)+
            c(i-1,j  )+         c(i+1,j  )+
            c(i-1,j+1)+c(i,j+1)+c(i+1,j+1);

          next_grid.set2d(i, j, 
              (grid.get2d(i, j) && (cur == 2 || cur == 3)) || 
              (!grid.get2d(i, j) && cur == 3));
        }
      }

      memcpy(grid.data, next_grid.data, grid.size);
      memset(next_grid.data, 0, next_grid.size);
    }

    // Clear the screen
    sf::RectangleShape clearer(sf::Vector2f(HEIGHT, WIDTH));
    clearer.setFillColor(sf::Color::White);
    window.draw(clearer);

    // Draw squares
    for (int i = 0; i < SQX; i++) {
      for (int j = 0; j < SQY; j++) {
        sf::RectangleShape border(sf::Vector2f(SQSZ, SQSZ));
        border.setFillColor(sf::Color(146, 156, 170));
        border.setPosition(i * SQSZ, j * SQSZ);
        sf::RectangleShape square(sf::Vector2f(SQSZ - 4, SQSZ - 4));
        if (grid.get2d(i, j))
          square.setFillColor(sf::Color::White);
        else
          square.setFillColor(sf::Color::Black);
        square.setPosition((i * SQSZ) + 2, (j * SQSZ) + 2);
        window.draw(border);
        window.draw(square);
      }
    }

    window.display();
  }

  return 0;
}
