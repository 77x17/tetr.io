#include "Generate.hpp"

Generate::Generate() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(numbers.begin(), numbers.end(), gen);
    for (const int& x : numbers) {
        tetrominoQueue.push(x);
    }
}

std::array<sf::RectangleShape, NUM_BLOCK> Generate::getShape(int key) {
    std::array<sf::RectangleShape, NUM_BLOCK> blocks;

    int k = 0;
    for (int i = 0; i < SHAPE_HEIGHT; i++) {
        for (int j = 0; j < SHAPE_WIDTH; j++) if (Shape[key][i][j] == 1) {
            blocks[k].setSize(sf::Vector2f(BLOCK_SIZE - 1, BLOCK_SIZE - 1));
            blocks[k].setFillColor(sf::Color::Cyan);
            blocks[k].setPosition(j, i);
            k++;
        }
    }

    return blocks;
}

std::tuple<std::array<sf::RectangleShape, NUM_BLOCK>, int, int> Generate::getShape() {
    int key = tetrominoQueue.front();
    tetrominoQueue.pop();

    std::array<sf::RectangleShape, NUM_BLOCK> blocks = getShape(key);

    if (tetrominoQueue.size() < 7) {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::shuffle(numbers.begin(), numbers.end(), gen);
        for (const int& x : numbers) {
            tetrominoQueue.push(x);
        }
    }

    return std::make_tuple(blocks, rotateBlock[key], key);
}

std::pair<int, int> Generate::getCenterPadding(int key) {
    return std::make_pair(centerPaddingWidth[key], centerPaddingHeight[key]);
}

std::queue<int> Generate::getTetrominoQueue() {
    return tetrominoQueue;
}

int Generate::getRotateBlock(int key) {
    return rotateBlock[key];
}