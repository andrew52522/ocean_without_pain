#pragma once
#include <SFML/Graphics.hpp>
#include "ocean.hpp"

class Visualizer {
public:
    Visualizer(Ocean& ocean);
    void run();

private:
    void processEvents();
    void update();
    void render();

    Ocean& ocean_;
    sf::RenderWindow window_;
    const int cellSize_ = 10; // Размер одной клетки в пикселях
};
