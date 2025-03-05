#pragma once

#include <SFML/Graphics.hpp>
#include "Constant.hpp"
#include "Tetromino.hpp"
#include "Generate.hpp"

class Board {
private:
    sf::Font font;
    
    void drawPiece(sf::RenderWindow &window, Generate generate, int key, int startX, int startY);
    void drawNextPiece(sf::RenderWindow &window, Generate generate);
public:
    Board();
    int  holdPieceShapeType;
    void drawGridBorder(sf::RenderWindow &window);
    void setHoldPiece(Tetromino &piece);
    void draw(sf::RenderWindow &window, Generate generate);
};