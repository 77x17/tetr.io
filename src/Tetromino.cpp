#include "Tetromino.hpp"

Tetromino::Tetromino() {
    generate = Generate();
    generateTetromino();
}

void Tetromino::generateTetromino() {
    std::tie(blocks, rotateBlock, shapeType) = generate.getShape();

    for (int i = 0; i < NUM_BLOCK; i++) {
        int x = blocks[i].getPosition().x; 
        int y = blocks[i].getPosition().y; 
        
        blocks[i].setPosition(startX + x * BLOCK_SIZE + 1, startY + y * BLOCK_SIZE + 1);
    }

    ghostBlocks = blocks;
    for (int i = 0; i < NUM_BLOCK; i++) {
        ghostBlocks[i].setFillColor(sf::Color::Yellow);
    }
    ghostBlockHardDrop();
}

int xConvert(const int &x) {
    return (x - GRID_POSITION_X  - 1) / BLOCK_SIZE;
}

int yConvert(const int &y) {
    return (y - GRID_POSITION_Y - 1) / BLOCK_SIZE;
}

bool Tetromino::isOutOfBounds(const sf::RectangleShape &block) const {
    int x = block.getPosition().x;
    int y = block.getPosition().y;
    
    if (not (GRID_POSITION_X  < x and x < GRID_POSITION_X  + GRID_WIDTH  * BLOCK_SIZE)) 
        return true;
    if (not (GRID_POSITION_Y < y and y < GRID_POSITION_Y + GRID_HEIGHT * BLOCK_SIZE))
        return true;
    if (occupied[xConvert(x)][yConvert(y)])
        return true;

    return false;
}

bool Tetromino::move(int dx, int dy) {
    for (int i = 0; i < NUM_BLOCK; i++) {
        sf::RectangleShape block = blocks[i];
        block.setPosition(block.getPosition().x + dx, block.getPosition().y + dy);
        if (isOutOfBounds(block)) 
            return false;
    }
    
    for (int i = 0; i < NUM_BLOCK; i++) {
        blocks[i].move(dx, dy);
    }
    ghostBlocks = blocks;
    for (int i = 0; i < NUM_BLOCK; i++) {
        ghostBlocks[i].setFillColor(sf::Color::Yellow);
    }
    ghostBlockHardDrop();

    return true;
}

void Tetromino::lockTetromino() {
    for (int i = 0; i < NUM_BLOCK; i++) {
        occupied[xConvert(blocks[i].getPosition().x)][yConvert(blocks[i].getPosition().y)] = true;
    }
}

void Tetromino::clearFullRows() {
    for (int j = GRID_HEIGHT - 1; j >= 0; j--) {
        bool flag = true;
        for (int i = GRID_WIDTH - 1; i >= 0; i--) {
            flag = flag and occupied[i][j];
        }

        if (flag == true) {
            for (int row = j; row >= 1; row--) {
                for (int column = 0; column < GRID_WIDTH; column++) {
                    occupied[column][row] = occupied[column][row - 1];
                }
            }
            for (int column = 0; column < GRID_WIDTH; column++) 
                occupied[column][0] = false;
            j++;
        }
    }
}

void Tetromino::ghostBlockHardDrop() {
    int maxDrop = GRID_HEIGHT;
    for (int i = 0; i < NUM_BLOCK; i++) {
        sf::RectangleShape block = blocks[i];
        int x = xConvert(block.getPosition().x);
        int y = yConvert(block.getPosition().y);
        int temp = GRID_HEIGHT;
        for (int j = y; j <= GRID_HEIGHT; j++) {
            if (occupied[x][j]) {
                temp = j;
                break;
            }
        }
        maxDrop = std::min(maxDrop, temp - y);
    }

    for (int i = 0; i < NUM_BLOCK; i++) {
        ghostBlocks[i].move(0, +BLOCK_SIZE * (maxDrop - 1));
    }
}

void Tetromino::hardDrop() {
    for (int i = 0; i < NUM_BLOCK; i++) 
        blocks[i].setPosition(ghostBlocks[i].getPosition());

    lockTetromino();

    clearFullRows();

    generateTetromino();
}

bool Tetromino::collisionBottom() {
    for (int i = 0; i < NUM_BLOCK; i++) {
        sf::RectangleShape block = blocks[i];
        block.setPosition(block.getPosition().x, block.getPosition().y + BLOCK_SIZE);
        if (isOutOfBounds(block))
            return true;
    }
    return false;
}

void Tetromino::rotate() {
    if (rotateBlock == -1) { 
        return;
    }

    std::array<sf::Vector2f, NUM_BLOCK> newPositions;
    bool flag = false;
    for (int k = 0; k < NUM_BLOCK - 1; k++) {
        bool outOfBounds = false;
        sf::Vector2f center = blocks[(rotateBlock + k) % NUM_BLOCK].getPosition();
        for (int i = 0; i < NUM_BLOCK and not outOfBounds; i++) {
            sf::Vector2f relative = blocks[i].getPosition() - center;

            newPositions[i] = sf::Vector2f(center.x - relative.y, center.y + relative.x);
            sf::RectangleShape block = blocks[i];
            block.setPosition(newPositions[i]);
            if (isOutOfBounds(block)) 
                outOfBounds = true;
        }

        if (outOfBounds) {
            outOfBounds = false;
            for (int i = 0; i < NUM_BLOCK and not outOfBounds; i++) {
                sf::Vector2f relative = blocks[i].getPosition() - center;
    
                newPositions[i] = sf::Vector2f(center.x + relative.y, center.y - relative.x);
                sf::RectangleShape block = blocks[i];
                block.setPosition(newPositions[i]);
                if (isOutOfBounds(block)) 
                    outOfBounds = true;
            }

            if (outOfBounds)
                continue;
        }
        
        int curr = 0, next = 0;
        for (int i = 0; i < NUM_BLOCK; i++) {
            curr = curr + yConvert(blocks[i].getPosition().y);
            next = next + yConvert(newPositions[i].y);
        }
        
        curr /= NUM_BLOCK; next /= NUM_BLOCK;
        if (abs(next - curr) > 2)
            continue;
        
        flag = true;
        break;
    }

    if (not flag)
        return;

    for (int i = 0; i < NUM_BLOCK; i++) 
        blocks[i].setPosition(newPositions[i]);
    
    ghostBlocks = blocks;
    for (int i = 0; i < NUM_BLOCK; i++) 
        ghostBlocks[i].setFillColor(sf::Color::Yellow);
    ghostBlockHardDrop();
}

void Tetromino::draw(sf::RenderWindow &window) {
    sf::RectangleShape block;
    block.setSize(sf::Vector2f(BLOCK_SIZE - 1, BLOCK_SIZE - 1));
    block.setFillColor(sf::Color::White); 
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) if (occupied[i][j]) {
            block.setPosition(GRID_POSITION_X + i * BLOCK_SIZE + 1, GRID_POSITION_Y + j * BLOCK_SIZE + 1);
            window.draw(block);
        }
    }

    block.setSize(sf::Vector2f(BLOCK_SIZE - 5, BLOCK_SIZE - 5));
    block.setFillColor(sf::Color::Black);
    for (int i = 0; i < NUM_BLOCK; i++) {
        window.draw(ghostBlocks[i]);
        block.setPosition(ghostBlocks[i].getPosition().x + 2, ghostBlocks[i].getPosition().y + 2);
        window.draw(block);
        window.draw(blocks[i]);
    }
}

std::array<sf::RectangleShape, NUM_BLOCK> Tetromino::getBlocks() {
    return blocks;
}

Generate Tetromino::getGenerate() {
    return generate;
}

void Tetromino::swapHoldPiece(int &holdPieceShapeType) {
    blocks = generate.getShape(holdPieceShapeType);
    for (int i = 0; i < NUM_BLOCK; i++) {
        int x = blocks[i].getPosition().x; 
        int y = blocks[i].getPosition().y; 
        
        blocks[i].setPosition(startX + x * BLOCK_SIZE + 1, startY + y * BLOCK_SIZE + 1);
    }
    rotateBlock = generate.getRotateBlock(holdPieceShapeType);
    
    ghostBlocks = blocks;
    for (int i = 0; i < NUM_BLOCK; i++) {
        ghostBlocks[i].setFillColor(sf::Color::Yellow);
    }
    ghostBlockHardDrop();

    std::swap(shapeType, holdPieceShapeType);
}

bool Tetromino::gameOver() {
    for (int i = 0; i < GRID_WIDTH; i++) 
        if (occupied[i][0])
            return true;

    return false;
}
