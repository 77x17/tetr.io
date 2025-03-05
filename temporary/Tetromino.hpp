#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Tetromino {
public:
    Tetromino();
    void move(int dx, int dy);
    void rotate(const bool occupied[10][20]);
    void draw(sf::RenderWindow& window);
    
    bool canMove(int dx, int dy, int width, int height, const bool occupied[10][20]);

    std::array<sf::RectangleShape, 4> getBlocks() const { return blocks; }

private:
    std::array<sf::RectangleShape, 4> blocks;
};
