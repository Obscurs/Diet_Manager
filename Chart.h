//
// Created by arnito on 26/01/18.
//

#ifndef DIET_MANAGER_CHART_H
#define DIET_MANAGER_CHART_H


#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Interface.h"
class Chart : public Interface{
public:
    Chart(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size);
    ~Chart();
    void insertValue(int value, std::string tag);
    void clear();
    void draw(sf::Font font);
    void updateValue(int value, std::string tag);

private:
    const int OFFSET_BOTTOM = 30;
    std::vector<int> _values;
    std::vector<std::string> _tags;

};


#endif //DIET_MANAGER_CHART_H
