#include "algae.hpp"
#include "ocean.hpp"
#include <cstdlib> // для rand()

Algae::Algae(int maxAge)
    : age_(0), maxAge_(maxAge) {}

void Algae::update(Ocean& ocean) {
    ++age_;

    if (age_ >= maxAge_) {
        return; // Водоросль умирает
    }

    // Получаем доступ к правильному генератору
    std::mt19937& gen = ocean.getRandomEngine();
    std::uniform_int_distribution<> reproduce_dist(0, 4); // Шанс 1 из 5 (0, 1, 2, 3, 4)
    
    // 20% шанс размножиться за такт
    if (reproduce_dist(gen) != 0) {
        return;
    }

    std::uniform_int_distribution<> move_dist(-1, 1); // Диапазон -1, 0, +1
    int dx = move_dist(gen);
    int dy = move_dist(gen);

    auto pos = ocean.findPosition(*this);
    if (!pos) return;

    int nx = pos->first + dx;
    int ny = pos->second + dy;

    size_t width = ocean.getGrid().getWidth();
    size_t height = ocean.getGrid().getHeight();

    if (nx >= 0 && nx < static_cast<int>(width) &&
        ny >= 0 && ny < static_cast<int>(height)) {

        auto& cell = ocean.getGrid().at(nx, ny);
        if (!cell) {
            cell = std::make_unique<Algae>(*this); // клонируем
        }
    }
}

char Algae::getSymbol() const {
    return 'A';
}

bool Algae::isAlive() const {
    return age_ < maxAge_;
}

std::unique_ptr<Entity> Algae::clone() const {
    return std::make_unique<Algae>(*this);
}