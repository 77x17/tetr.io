#pragma once

#include <SFML/Graphics.hpp>
#include "Tetromino.hpp"
#include "Board.hpp"
#include "Constant.hpp"

class Game {
private:
    sf::RenderWindow window;
    Board            board;
    Tetromino        tetromino;
    sf::Clock        clock;

    void processEvents();
    void update();
    void render();
    bool rotateFlag = false;
public:
    Game();
    void run();
};