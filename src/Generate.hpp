#pragma once

#include <SFML/Graphics.hpp>
#include "Constant.hpp"
#include <random>
#include <array>
#include <queue>

class Generate {
private:
    bool Shape[NUM_SHAPE][SHAPE_HEIGHT][SHAPE_WIDTH] = {
        { // 0: I Shape
            {1, 1, 1, 1},
            {0, 0, 0, 0}
        },
        { // 1: J Shape
            {1, 0, 0, 0},
            {1, 1, 1, 0}
        },
        { // 2: L Shape
            {0, 0, 1, 0},
            {1, 1, 1, 0}
        },
        { // 3: O Shape
            {1, 1, 0, 0},
            {1, 1, 0, 0}
        },
        { // 4: S Shape
            {0, 1, 1, 0},
            {1, 1, 0, 0}
        },
        { // 5: T Shape
            {0, 1, 0, 0},
            {1, 1, 1, 0}
        },
        { // 6: Z Shape
            {1, 1, 0, 0},
            {0, 1, 1, 0}
        }
    };

    int rotateBlock[NUM_SHAPE] = {
        1, 2, 2, -1, 3, 2, 2
    };

    std::queue<int> tetrominoQueue;
    std::vector<int> numbers = {0, 1, 2, 3, 4, 5, 6};
    std::vector<int> centerPaddingWidth = {0, BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE, BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2};
    std::vector<int> centerPaddingHeight = {BLOCK_SIZE, BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2};
public:
    Generate();
    std::array<sf::RectangleShape, NUM_BLOCK> getShape(int);
    std::tuple<std::array<sf::RectangleShape, NUM_BLOCK>, int, int> getShape();
    std::pair<int, int> getCenterPadding(int);
    std::queue<int> getTetrominoQueue();
    int getRotateBlock(int key);
};