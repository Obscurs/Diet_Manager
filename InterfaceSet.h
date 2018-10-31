//
// Created by arnito on 26/01/18.
//

#pragma once

#include "Interface.h"

class InterfaceSet: public Interface {
public:
    InterfaceSet(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size);
    ~InterfaceSet();
    void clear();
    void draw(sf::Font font);
    void update();
    void draw(sf::Vector2f offset, sf::Font font);
    void update(sf::Vector2f offset);
    std::vector<Interface*>& getInterfaces();
    void addInterface(Interface* interface, sf::Vector2f offset);
    std::vector<Interface*>& getElements();
private:
    std::vector<Interface*> _interfaces;
    std::vector<sf::Vector2f> _offsets;
};
