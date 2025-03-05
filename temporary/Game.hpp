#pragma once
#include <SFML/Graphics.hpp>
#include "Tetromino.hpp"

class Game {
public:
    Game();
    void run();

private:
    static const int GRID_WIDTH      = 10;  // 10 cột
    static const int GRID_HEIGHT     = 20; // 20 hàng
    static const int BLOCK_SIZE      = 30;  // Kích thước mỗi ô vuông
    static constexpr float DROP_TIME = 0.5f; // Thời gian rơi mỗi bước (giây)

    static const int WINDOW_WIDTH  = 400;  // Tăng độ rộng để có khoảng trống
    static const int WINDOW_HEIGHT = 700; // Tăng chiều cao để dễ quan sát

    sf::RenderWindow window;
    Tetromino tetromino;
    sf::Clock clock; // Đồng hồ để tính thời gian rơi

    sf::RectangleShape grid[GRID_WIDTH][GRID_HEIGHT]; // Lưu trạng thái lưới
    bool occupied[GRID_WIDTH][GRID_HEIGHT] = { false }; // Đánh dấu ô đã có khối

    void processEvents();
    void update();
    void render();
    void drawGridBorder();
    void lockTetromino();
    void clearFullRows();
};
