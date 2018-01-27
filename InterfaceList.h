//
// Created by arnito on 11/12/16.
//

#ifndef GENLAND_INTERFACELIST_H
#define GENLAND_INTERFACELIST_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Interface.h"

class InterfaceList : public Interface{
public:
    InterfaceList(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, int tp, int vis_slots, std::string header);
    ~InterfaceList();
    void draw(sf::Font font);
    void update();
    void draw(sf::Vector2f offset, sf::Font font);
    void update(sf::Vector2f offset);
    void insertElement(Interface* interface);
    void clear();
    int getIdSelected();
    std::vector<Interface*>& getElements();
private:
    const static int GRID_THICKNESS = 2;
    const static int GRID_SELECTED_THICKNESS = 8;
    int _visible_slots;
    int _selected_slot;
    int _type;
    int _offset;

    std::string _header;
    std::vector<Interface*> _elements;
};


#endif //GENLAND_INTERFACELIST_H
