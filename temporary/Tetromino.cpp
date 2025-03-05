#include "Tetromino.hpp"

Tetromino::Tetromino() {
    int startX = 50 + 3 * 30; // Bắt đầu từ cột giữa (50 là lề, 3*30 để vào giữa lưới)
    int startY = 50; // Bắt đầu từ hàng đầu tiên

    for (int i = 0; i < 4; ++i) {
        blocks[i].setSize(sf::Vector2f(30 - 2, 30 - 2));
        blocks[i].setFillColor(sf::Color::Blue);
        blocks[i].setPosition(startX + i * 30 + 1, startY + 1);
    }
}
bool Tetromino::canMove(int dx, int dy, int width, int height, const bool occupied[10][20]) {
    for (int i = 0; i < 4; ++i) {
        sf::Vector2f newPos = blocks[i].getPosition() + sf::Vector2f(dx, dy) + sf::Vector2f(-1, -1);

        // Chuyển đổi tọa độ pixel sang tọa độ lưới
        int x = (newPos.x - 50) / 30;
        int y = (newPos.y - 50) / 30;

        // Kiểm tra va chạm với biên trái/phải
        if (x < 0 || x >= width) return false;

        // Kiểm tra va chạm với đáy
        if (y >= height) return false;

        // Kiểm tra xem ô có bị chiếm không
        if (occupied[x][y]) return false;
    }
    return true;
}
void Tetromino::move(int dx, int dy) {
    for (int i = 0; i < 4; ++i) {
        blocks[i].move(dx, dy);
    }
}

void Tetromino::rotate(const bool occupied[10][20]) {
    sf::Vector2f pivot = blocks[1].getPosition(); // 🟢 Chọn block thứ 2 làm tâm xoay
    sf::RectangleShape newBlocks[4];

    for (int i = 0; i < 4; ++i) {
        float dx = blocks[i].getPosition().x - pivot.x;
        float dy = blocks[i].getPosition().y - pivot.y;

        sf::Vector2f newPos(pivot.x - dy, pivot.y + dx); // Công thức xoay 90 độ

        int x = (newPos.x - 50) / blocks[i].getSize().x;
        int y = (newPos.y - 50) / blocks[i].getSize().y;

        if (x < 0 || x >= 10 || y < 0 || y >= 20 || occupied[x][y]) {
            return; // Nếu va chạm, hủy xoay
        }
        newBlocks[i].setPosition(newPos);
    }

    for (int i = 0; i < 4; ++i) {
        blocks[i].setPosition(newBlocks[i].getPosition()); // Áp dụng xoay
    }
}

void Tetromino::draw(sf::RenderWindow& window) {
    for (int i = 0; i < 4; ++i) {
        window.draw(blocks[i]);
    }
}
