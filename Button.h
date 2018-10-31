//
// Created by ant on 03/11/16.
//

#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Interface.h"
class Button : public Interface{
public:
    Button(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, std::string txt, int tp);
    ~Button();
    void draw(sf::Font font);
    void update();
    void draw(sf::Vector2f offset, sf::Font font);
    void update(sf::Vector2f offset);
    void setText(std::string s);
private:
    std::string _text;
    int _type;
};
