#include "Board.hpp"

Board::Board() {
    holdPieceShapeType = -1;
    font.loadFromFile("assets/fonts/ARLRDBD.TTF");
}

void Board::drawGridBorder(sf::RenderWindow &window) {
    sf::RectangleShape line(sf::Vector2f(GRID_WIDTH * BLOCK_SIZE, 1));
    line.setFillColor(sf::Color(200, 200, 200, 150));
    for (int i = 0; i <= GRID_HEIGHT; i++) {
        line.setPosition(GRID_POSITION_X, GRID_POSITION_Y + i * BLOCK_SIZE);
        window.draw(line);
    }

    line.setSize(sf::Vector2f(1, GRID_HEIGHT * BLOCK_SIZE));
    for (int i = 0; i <= GRID_WIDTH; i++) {
        line.setPosition(GRID_POSITION_X + i * BLOCK_SIZE, GRID_POSITION_Y);
        window.draw(line);
    }
    

    line.setSize(sf::Vector2f(HOLD_WIDTH * BLOCK_SIZE, 1));
    line.setPosition(HOLD_POSITION_X, HOLD_POSITION_Y + 0           * BLOCK_SIZE);
    window.draw(line);
    line.setPosition(HOLD_POSITION_X, HOLD_POSITION_Y + HOLD_HEIGHT * BLOCK_SIZE);
    window.draw(line);
    
    line.setSize(sf::Vector2f(1, HOLD_HEIGHT * BLOCK_SIZE));
    line.setPosition(HOLD_POSITION_X + 0          * BLOCK_SIZE, HOLD_POSITION_Y);
    window.draw(line);
    line.setPosition(HOLD_POSITION_X + HOLD_WIDTH * BLOCK_SIZE, HOLD_POSITION_Y);
    window.draw(line);

    line.setSize(sf::Vector2f(NEXT_WIDTH * BLOCK_SIZE, 1));
    line.setPosition(NEXT_POSITION_X, NEXT_POSITION_Y + 0           * BLOCK_SIZE);
    window.draw(line);
    line.setPosition(NEXT_POSITION_X, NEXT_POSITION_Y + NEXT_HEIGHT * BLOCK_SIZE);
    window.draw(line);
    
    line.setSize(sf::Vector2f(1, NEXT_HEIGHT * BLOCK_SIZE));
    line.setPosition(NEXT_POSITION_X + 0          * BLOCK_SIZE, NEXT_POSITION_Y);
    window.draw(line);
    line.setPosition(NEXT_POSITION_X + NEXT_WIDTH * BLOCK_SIZE, NEXT_POSITION_Y);
    window.draw(line);
}

void Board::setHoldPiece(Tetromino &piece) {
    holdPieceShapeType = piece.shapeType;
}

void Board::draw(sf::RenderWindow &window, Generate generate) {
    sf::Text holdText("HOLD", font, 20);
    holdText.setPosition(HOLD_POSITION_X, HOLD_POSITION_Y - BLOCK_SIZE);
    window.draw(holdText);

    if (holdPieceShapeType != -1) {
        drawPiece(window, generate, holdPieceShapeType, HOLD_POSITION_X, HOLD_POSITION_Y);
    }


    sf::Text nextText("NEXT", font, 20);
    nextText.setPosition(NEXT_POSITION_X, NEXT_POSITION_Y - BLOCK_SIZE);
    window.draw(nextText);

    drawNextPiece(window, generate);
}

void Board::drawPiece(sf::RenderWindow &window, Generate generate, int key, int startX, int startY) {
    std::array<sf::RectangleShape, NUM_BLOCK> blocks = generate.getShape(key);
    std::pair<int, int> centerPadding = generate.getCenterPadding(key);
    for (int i = 0; i < NUM_BLOCK; i++) {
        int x = blocks[i].getPosition().x; 
        int y = blocks[i].getPosition().y;
        
        blocks[i].setPosition(startX + x * BLOCK_SIZE + 1 + centerPadding.first, startY + y * BLOCK_SIZE + 1 + centerPadding.second);
        window.draw(blocks[i]);
    }
}

void Board::drawNextPiece(sf::RenderWindow &window, Generate generate) {
    std::queue<int> tetrominoQueue = generate.getTetrominoQueue();

    for (int i = 0; i < 5; i++) {
        drawPiece(window, generate, tetrominoQueue.front(), NEXT_POSITION_X, NEXT_POSITION_Y + i * 3 * BLOCK_SIZE);
        tetrominoQueue.pop();
    }
}