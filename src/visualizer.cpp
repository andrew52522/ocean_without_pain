#include "visualizer.hpp"
#include <iostream>

Visualizer::Visualizer(Ocean &ocean)
    : ocean_(ocean),
      window_(sf::VideoMode(600, 500), "Ocean Simulation") // A fixed large window
{
    window_.setFramerateLimit(10);
}

void Visualizer::run()
{
    while (window_.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Visualizer::processEvents()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window_.close();
        }
    }
}

void Visualizer::update()
{
    ocean_.tick();

    // Проверяем, остались ли живые существа
    if (ocean_.countLivingEntities() == 0)
    {
        std::cout << "[INFO] All entities have died. Closing window." << std::endl;
        window_.close(); // Закрываем окно
    }

    // Добавим паузу для комфортного просмотра
    sf::sleep(sf::milliseconds(200));
}

/*
void Visualizer::render()
{
    window_.clear(sf::Color(24, 92, 153));

    sf::RectangleShape cellShape(sf::Vector2f(cellSize_, cellSize_));

    for (size_t y = 0; y < ocean_.getGrid().getHeight(); ++y)
    {
        for (size_t x = 0; x < ocean_.getGrid().getWidth(); ++x)
        {
            const auto &cell = ocean_.getGrid().at(x, y);
            if (cell)
            {
                switch (cell->getSymbol())
                {
                case 'A':
                    cellShape.setFillColor(sf::Color::Green);
                    cellShape.setPosition((x * cellSize_), y * cellSize_);
                    break;
                case 'H':
                    cellShape.setFillColor(sf::Color::Yellow);
                    cellShape.setPosition(x * cellSize_, y * cellSize_);
                    break;
                case 'P':
                    cellShape.setFillColor(sf::Color::Red);
                    cellShape.setPosition(x * cellSize_, y * cellSize_);
                    break;
                default:
                    cellShape.setFillColor(sf::Color::White);
                    cellShape.setPosition(x * cellSize_, y * cellSize_);
                    break;
                }
                // рисовка
                // cellShape.setPosition(x * cellSize_, y * cellSize_);
                window_.draw(cellShape);
            }
        }
    }
    window_.display();
}
*/

void Visualizer::render()
{
    window_.clear(sf::Color(24, 92, 153));

    // 1. Создаём "шаблон" для водорослей: узкий прямоугольник.
    // Ширина та же, а высота в 3 раза меньше.
    sf::RectangleShape algaeShape(sf::Vector2f(cellSize_, cellSize_ / 3.0f));

    // 2. Создаём "шаблон" для рыб: треугольник.
    sf::ConvexShape fishShape;
    fishShape.setPointCount(3); // Устанавливаем, что у фигуры 3 вершины
    // Задаём координаты вершин для равнобедренного треугольника, смотрящего вверх
    fishShape.setPoint(0, sf::Vector2f(cellSize_ / 2.0f, 0));  // Верхняя точка
    fishShape.setPoint(1, sf::Vector2f(0, cellSize_));         // Левая нижняя
    fishShape.setPoint(2, sf::Vector2f(cellSize_, cellSize_)); // Правая нижняя

    for (size_t y = 0; y < ocean_.getGrid().getHeight(); ++y)
    {
        for (size_t x = 0; x < ocean_.getGrid().getWidth(); ++x)
        {
            const auto &cell = ocean_.getGrid().at(x, y);
            if (cell)
            {
                switch (cell->getSymbol())
                {
                case 'A':
                    // Используем прямоугольник для водоросли
                    algaeShape.setFillColor(sf::Color::Green);
                    // Позицию смещаем, чтобы прямоугольник был по центру клетки
                    algaeShape.setPosition(x * cellSize_, y * cellSize_ + (cellSize_ / 3.0f));
                    window_.draw(algaeShape); // Рисуем водоросль
                    break;

                case 'H':
                    // Используем треугольник для травоядной рыбы
                    fishShape.setFillColor(sf::Color::Yellow);
                    fishShape.setPosition(x * cellSize_, y * cellSize_);
                    window_.draw(fishShape); // Рисуем травоядную
                    break;

                case 'P':
                    // Используем тот же треугольник для хищной рыбы
                    fishShape.setFillColor(sf::Color::Red);
                    fishShape.setPosition(x * cellSize_, y * cellSize_);
                    window_.draw(fishShape); // Рисуем хищника
                    break;

                default:
                    // Можно оставить квадрат для неизвестных объектов, если нужно
                    break;
                }
            }
        }
    }
    window_.display();
}