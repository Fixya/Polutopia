#pragma once
#include <SFML/Graphics.hpp>

const float WINDOW_WIDTH = 1000;
const float WINDOW_HEIGHT = 780;
const std::string WINDOW_TITLE = "Polutopia";
const float FPS = 60.f;

const std::string PLAYER_FILE_NAME = "dom.png";
const std::string PLAYER1_FILE_NAME = "dom1.png";
const std::string IMAGES_FILE_NAME = "images.png";
const float PLAYER_SPEED = 10.f;

const std::string FONT_FILE_NAME = "DS-DIGIB.ttf";
const int FONT_SIZE = 32;

const float BLOCK_WIDTH = 85.f;
const float BLOCK_HEIGHT = 60.f;
const sf::Color BLOCK_COLOR{ sf::Color(28, 255, 50) };
const sf::Vector2f BLOCK_POS{ 0, 0 };

const int COL_LINE = 10;
const int COL_ROW = 10;