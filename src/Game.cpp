#include "Game.hpp"

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetr.io clone by 77x17") {}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

bool moveLeft = false, moveRight = false;
float moveCooldown = 0.0f;

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) {
                moveLeft  = true;
                moveRight = false;
                if (tetromino.move(-BLOCK_SIZE, 0)) {
                    if (tetromino.collisionBottom()) {
                        clock.restart();
                    }
                }
            } else if (event.key.code == sf::Keyboard::Right) {
                moveLeft  = false;
                moveRight = true;
                if (tetromino.move(+BLOCK_SIZE, 0)) {
                    if (tetromino.collisionBottom()) {
                        clock.restart();
                    }
                }
            } else if (event.key.code == sf::Keyboard::Down) {
                if (tetromino.move(0, +BLOCK_SIZE)) {
                    if (not tetromino.collisionBottom()) {
                        clock.restart();
                    }
                }
            } else if (event.key.code == sf::Keyboard::Up and rotateFlag == false) {
                tetromino.rotate();
                if (tetromino.collisionBottom()) {
                    clock.restart();
                }
                rotateFlag = true;
            } else if (event.key.code == sf::Keyboard::Space) {
                tetromino.hardDrop(); 
                if (tetromino.gameOver()) {
                    tetromino = Tetromino();
                    board     = Board();
                }
                clock.restart();
            } else if (event.key.code == sf::Keyboard::C) {
                if (board.holdPieceShapeType == -1) {
                    board.setHoldPiece(tetromino);
                    tetromino.generateTetromino();
                } else {
                    tetromino.swapHoldPiece(board.holdPieceShapeType);
                    clock.restart();
                }
            }
        } else if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Left) {
                moveLeft = false;
            } else if (event.key.code == sf::Keyboard::Right) {
                moveRight = false;
            } else if (event.key.code == sf::Keyboard::Up) {
                rotateFlag = false;
            }
        }
    }
}

void Game::update() {
    if (clock.getElapsedTime().asSeconds() >= DROP_TIME) {
        if (not tetromino.move(0, +BLOCK_SIZE)) {
            tetromino.lockTetromino();
            
            if (tetromino.gameOver()) {
                tetromino = Tetromino();
                board     = Board();
            }
            
            tetromino.clearFullRows();
            
            tetromino.generateTetromino();
        }
        clock.restart();
    }
}

void Game::render() {
    window.clear();

    board.drawGridBorder(window);
    board.draw(window, tetromino.getGenerate());
    
    tetromino.draw(window);
    
    window.display();
}