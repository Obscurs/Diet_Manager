//
// Created by arnito on 27/01/18.
//

#pragma once

#include "Interface.h"

class CheckBox: public Interface {
public:
    CheckBox(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, int id);
    ~CheckBox();
    bool getValue();
    int getId();
    void changeState();
    void setValue(bool value);
    void draw(sf::Font font);
    void update();
    void draw(sf::Vector2f offset, sf::Font font);
    void update(sf::Vector2f offset);
private:
    bool _value;
    int _id;
};
