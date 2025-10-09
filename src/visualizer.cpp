#include "visualizer.hpp"
#include <iostream>

Visualizer::Visualizer(Ocean& ocean)
    : ocean_(ocean),
      window_(sf::VideoMode(600, 500), "Ocean Simulation") // A fixed large window
{
    window_.setFramerateLimit(10);
}

void Visualizer::run() {
    while (window_.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Visualizer::processEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
        }
    }
}

void Visualizer::update() {
    ocean_.tick();

    // Проверяем, остались ли живые существа
    if (ocean_.countLivingEntities() == 0) {
        std::cout << "[INFO] All entities have died. Closing window." << std::endl;
        window_.close(); // Закрываем окно
    }
    
    // Добавим паузу для комфортного просмотра
    sf::sleep(sf::milliseconds(200));
}

void Visualizer::render() {
    window_.clear(sf::Color(24, 92, 153));

    sf::RectangleShape cellShape(sf::Vector2f(cellSize_, cellSize_));

    for (size_t y = 0; y < ocean_.getGrid().getHeight(); ++y) {
        for (size_t x = 0; x < ocean_.getGrid().getWidth(); ++x) {
            const auto& cell = ocean_.getGrid().at(x, y);
            if (cell) {
                switch (cell->getSymbol()) {
                    case 'A':
                        cellShape.setFillColor(sf::Color::Green);
                        break;
                    case 'H':
                        cellShape.setFillColor(sf::Color::Yellow); // ИСПРАВЛЕНО
                        break;
                    case 'P':
                        cellShape.setFillColor(sf::Color::Red);
                        break;
                    default:
                        cellShape.setFillColor(sf::Color::White);
                        break;
                }
                cellShape.setPosition(x * cellSize_, y * cellSize_);
                window_.draw(cellShape);
            }
        }
    }
    window_.display();
}