#include "Game.hpp"

Game::Game() 
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris OOP") {}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left && tetromino.canMove(-BLOCK_SIZE, 0, GRID_WIDTH, GRID_HEIGHT, occupied))
                tetromino.move(-BLOCK_SIZE, 0);
            else if (event.key.code == sf::Keyboard::Right && tetromino.canMove(BLOCK_SIZE, 0, GRID_WIDTH, GRID_HEIGHT, occupied))
                tetromino.move(BLOCK_SIZE, 0);
            else if (event.key.code == sf::Keyboard::Down && tetromino.canMove(0, BLOCK_SIZE, GRID_WIDTH, GRID_HEIGHT, occupied))
                tetromino.move(0, BLOCK_SIZE);
            else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
                tetromino.rotate(occupied); // 🟢 Gọi xoay khi bấm lên

        }
    }
}

void Game::update() {
    if (clock.getElapsedTime().asSeconds() >= DROP_TIME) {
        if (tetromino.canMove(0, BLOCK_SIZE, GRID_WIDTH, GRID_HEIGHT, occupied)) {
            tetromino.move(0, BLOCK_SIZE);
        } else {
            lockTetromino(); // Lưu trạng thái khi chạm đáy
            clearFullRows(); // Kiểm tra hàng đầy và xóa
            tetromino = Tetromino(); // Tạo khối mới
        }
        clock.restart();
    }
}

void Game::render() {
    window.clear();
    drawGridBorder();

    // Vẽ các khối đã rơi xuống
    for (int x = 0; x < GRID_WIDTH; ++x) {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            if (occupied[x][y]) {
                window.draw(grid[x][y]);
            }
        }
    }

    // Vẽ khối hiện tại
    tetromino.draw(window);

    window.display();
}

// Vẽ đường viền nét đứt quanh vùng chơi
void Game::drawGridBorder() {
    sf::RectangleShape line(sf::Vector2f(GRID_WIDTH * BLOCK_SIZE, 1)); // Dòng ngang

    line.setFillColor(sf::Color(200, 200, 200, 150)); // Màu xám mờ

    for (int i = 0; i <= GRID_HEIGHT; ++i) {
        line.setPosition(50, 50 + i * BLOCK_SIZE);
        window.draw(line);
    }

    line.setSize(sf::Vector2f(1, GRID_HEIGHT * BLOCK_SIZE)); // Dòng dọc

    for (int i = 0; i <= GRID_WIDTH; ++i) {
        line.setPosition(50 + i * BLOCK_SIZE, 50);
        window.draw(line);
    }
}

void Game::lockTetromino() {
    auto blocks = tetromino.getBlocks(); // Lấy danh sách khối

    for (int i = 0; i < 4; ++i) {
        sf::Vector2f pos = blocks[i].getPosition(); // Lấy vị trí từng khối
        int x = (pos.x - 50) / BLOCK_SIZE;
        int y = (pos.y - 50) / BLOCK_SIZE;
        
        occupied[x][y] = true;
        grid[x][y] = blocks[i]; // Gán khối vào lưới
    }
}

void Game::clearFullRows() {
    for (int y = GRID_HEIGHT - 1; y >= 0; --y) {
        bool full = true;

        // Kiểm tra xem hàng y có đầy không
        for (int x = 0; x < GRID_WIDTH; ++x) {
            if (!occupied[x][y]) {
                full = false;
                break;
            }
        }

        if (full) {
            // Xóa hàng y
            for (int x = 0; x < GRID_WIDTH; ++x) {
                occupied[x][y] = false;
            }

            // Dời tất cả hàng trên xuống 1 bậc
            for (int row = y; row > 0; --row) {
                for (int x = 0; x < GRID_WIDTH; ++x) {
                    occupied[x][row] = occupied[x][row - 1];
                    grid[x][row] = grid[x][row - 1];
                }
            }

            // Làm rỗng hàng trên cùng sau khi dời xuống
            for (int x = 0; x < GRID_WIDTH; ++x) {
                occupied[x][0] = false;
            }

            // Kiểm tra lại hàng y sau khi đã dời xuống
            y++;
        }
    }
}


