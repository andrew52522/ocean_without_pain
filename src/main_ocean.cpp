#include "ocean.hpp"
#include "algae.hpp"
#include "visualizer.hpp"
#include "herbivoreFish.hpp"
#include "predatorFish.hpp"
#include "sand.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

constexpr size_t WIDTH = 60;
constexpr size_t HEIGHT = 50;
constexpr int MAX_TICKS = 100;
constexpr float INITIAL_ALGAE_DENSITY = 0.2f;
constexpr float INITIAL_HERBIVORE_DENSITY = 0.08f;
constexpr float INITIAL_PREDATOR_DENSITY = 0.02f;

void initializeOceanRandomly(Ocean& ocean) {

    // Получаем доступ к единому, правильному генератору из океана
    std::mt19937& gen = ocean.getRandomEngine();

    // Создаём "распределения" для получения координат в нужном диапазоне
    std::uniform_int_distribution<> x_dist(0, ocean.getGrid().getWidth() - 1);
    std::uniform_int_distribution<> y_dist(0, ocean.getGrid().getHeight() - 1);

    size_t totalCells = ocean.getGrid().getWidth() * ocean.getGrid().getHeight();

    // Расставляем водоросли
    for (size_t i = 0; i < totalCells * INITIAL_ALGAE_DENSITY; ++i) {
        int x = x_dist(gen);
        int y = y_dist(gen);
        if (!ocean.getGrid().at(x, y)) {
            ocean.getGrid().at(x, y) = std::make_unique<Algae>();
        }
    }
    
     for (size_t i = 0; i < totalCells * INITIAL_HERBIVORE_DENSITY; ++i) {
        int x = x_dist(gen);
        int y = y_dist(gen);
        if (!ocean.getGrid().at(x, y)) {
            ocean.getGrid().at(x, y) = std::make_unique<HerbivoreFish>();
        }
    }
    for (size_t i = 0; i < totalCells * INITIAL_PREDATOR_DENSITY; ++i) {
        int x = x_dist(gen);
        int y = y_dist(gen);
        if (!ocean.getGrid().at(x, y)) {
            ocean.getGrid().at(x, y) = std::make_unique<PredatorFish>();
        }
    }

    // Остальные ячейки остаются пустыми (Sand будет по умолчанию)
}

int main() {
    std::cout << "[step 1] Program workd." << std::endl;

    Ocean ocean(WIDTH, HEIGHT);
    std::cout << "[step 2]  Ocean just created." << std::endl;

    initializeOceanRandomly(ocean);
    std::cout << "[step 3] Ocean fulfilled entyties." << std::endl;

    // --- Критический момент здесь ---
    Visualizer visualizer(ocean);
    std::cout << "[step 4]  Visualizer created. Window is open." << std::endl;

    visualizer.run();
    std::cout << "[step 5] End of Simulation." << std::endl;

    return 0;
}