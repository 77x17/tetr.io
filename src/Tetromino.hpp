#pragma once

#include <SFML/Graphics.hpp>
#include "Constant.hpp"
#include "Generate.hpp"
#include <vector>
#include <array>

class Tetromino {
private:
    int startX = GRID_POSITION_X + 3 * BLOCK_SIZE;
    int startY = GRID_POSITION_Y;

    Generate generate;
    int      rotateBlock;
    std::array<sf::RectangleShape, NUM_BLOCK> blocks;
    std::array<sf::RectangleShape, NUM_BLOCK> ghostBlocks;
    bool occupied[10][20] = {false};
    
    bool isOutOfBounds(const sf::RectangleShape &block) const;
public:
    Tetromino();
    void generateTetromino();
    int  shapeType;
    bool move(int dx, int dy);
    void lockTetromino();
    void clearFullRows();
    void ghostBlockHardDrop();
    void hardDrop();
    bool collisionBottom();
    void rotate();
    void draw(sf::RenderWindow &window);
    std::array<sf::RectangleShape, NUM_BLOCK> getBlocks();
    Generate getGenerate();
    void swapHoldPiece(int &holdPieceShapeType);
    bool gameOver();
};