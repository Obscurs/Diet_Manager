//
// Created by arnito on 11/12/16.
//

#include "InterfaceList.h"
#include "Inputs.h"
#include <iostream>

InterfaceList::InterfaceList(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, int tp, int vis_slots,std::string title)
    : Interface(window,position,size)
{
    _type = tp;
    _visible_slots = vis_slots;
    _selected_slot = 0;
    _offset = 0;
    _header = title;
}

InterfaceList::~InterfaceList() {
    for(int i=0; i< _elements.size(); ++i){
        delete _elements[i];
    }
    _elements.clear();
}
void InterfaceList::insertElement(Interface* interface) {
    _elements.push_back(interface);
}
void InterfaceList::draw(sf::Font font){
    //if(!_elements.empty()) {
        sf::RectangleShape rectangle(sf::Vector2f(0, 0));


        rectangle.setFillColor(sf::Color(255, 211, 124));
        rectangle.setOutlineThickness(GRID_THICKNESS);
        rectangle.setOutlineColor(sf::Color(147, 91, 0));
        rectangle.setSize(sf::Vector2f(_size.x - GRID_THICKNESS, _size.y - GRID_THICKNESS));

        for (int i = -1; i < _visible_slots; i = ++i) {
            if(i == -1){
                rectangle.setFillColor(sf::Color(179, 145, 81));
            }
            else rectangle.setFillColor(sf::Color(255, 211, 124));

            rectangle.setPosition(sf::Vector2f(_position.x, i * _size.y + _position.y));
            _window.draw(rectangle);
            if(i != -1){
                rectangle.setFillColor(sf::Color(179, 145, 81));

                rectangle.setSize(sf::Vector2f(100, rectangle.getSize().y));
                _window.draw(rectangle);
                rectangle.setSize(sf::Vector2f(_size.x - GRID_THICKNESS, _size.y - GRID_THICKNESS));

                sf::Text sftext;
                sftext.setCharacterSize(_size.y / 2);
                sftext.setColor(sf::Color::Black);
                sftext.setPosition(sf::Vector2f(_position.x+130, (i) * _size.y + _position.y));
                sftext.setString(std::to_string(i+1+_offset));
                sftext.setFont(font); // font is a sf::Font


                sf::FloatRect textRect = sftext.getLocalBounds();
                sftext.setOrigin(textRect.left + textRect.width/2.0f,
                                 textRect.top  + textRect.height/2.0f);
                sftext.setPosition(sf::Vector2f(_position.x+(100)/2.0f,(i) * _size.y + _position.y+(_size.y)/2.0f));

                _window.draw(sftext);
            } else{
                sf::Text sftext;
                sftext.setCharacterSize(_size.y / 2);
                sftext.setColor(sf::Color::Black);
                sftext.setPosition(sf::Vector2f(_position.x+130, (i) * _size.y + _position.y));
                sftext.setString(_header);
                sftext.setFont(font); // font is a sf::Font


                sf::FloatRect textRect = sftext.getLocalBounds();
                sftext.setOrigin(textRect.left + textRect.width/2.0f,
                                 textRect.top  + textRect.height/2.0f);
                sftext.setPosition(sf::Vector2f(_position.x+(_size.x)/2.0f,(i) * _size.y + _position.y+(_size.y)/2.0f));

                _window.draw(sftext);
            }

        }

        for (int i = _offset;
             i < std::min(_visible_slots + _offset, ((int) _elements.size())); ++i) {
            _elements[i]->draw(font);
        }
        sf::RectangleShape selected(rectangle);
        selected.setPosition(sf::Vector2f(_position.x, (_selected_slot) * _size.y + _position.y));
        selected.setFillColor(sf::Color::Transparent);
        selected.setOutlineThickness(GRID_SELECTED_THICKNESS);
        selected.setOutlineColor(sf::Color(0, 0, 0));
        _window.draw(selected);

    sf::RectangleShape rectangleArrow(sf::Vector2f(0, 0));
    rectangleArrow.setSize(sf::Vector2f(_size.y/1.5, _size.y/1.5));
    rectangleArrow.setPosition(sf::Vector2f(_position.x+_size.x-_size.y/1.5, _position.y));
    rectangleArrow.setFillColor(sf::Color(255, 255, 255));
    rectangleArrow.setOutlineThickness(GRID_THICKNESS);
    rectangleArrow.setOutlineColor(sf::Color(0, 0, 0));
    _window.draw(rectangleArrow);
    rectangleArrow.setPosition(sf::Vector2f(_position.x+_size.x-_size.y/1.5, _position.y+_size.y*(_visible_slots)-_size.y/1.5));
    _window.draw(rectangleArrow);

    sf::CircleShape triangleUp(_size.y/1.5/2-3,3);
    triangleUp.setFillColor(sf::Color::Black);
    triangleUp.setPosition(_position.x+_size.x-_size.y/1.5+3,_position.y+3);
    sf::CircleShape triangleDown(_size.y/1.5/2-3,3);
    triangleDown.setOrigin(triangleDown.getRadius(),triangleDown.getRadius());
    triangleDown.rotate(180);
    //triangleDown.setOrigin(0,0);
    triangleDown.setFillColor(sf::Color::Black);
    triangleDown.setPosition(_position.x+_size.x-_size.y/1.5/2,_position.y+_size.y*(_visible_slots)+_size.y/1.5/2-_size.y/1.5);

    _window.draw(triangleUp);
    _window.draw(triangleDown);
    //}
}

void InterfaceList::draw(sf::Vector2f offset, sf::Font font){
    //if(!_elements.empty()) {
    sf::RectangleShape rectangle(sf::Vector2f(0, 0));


    rectangle.setFillColor(sf::Color(255, 211, 124));
    rectangle.setOutlineThickness(GRID_THICKNESS);
    rectangle.setOutlineColor(sf::Color(147, 91, 0));
    rectangle.setSize(sf::Vector2f(_size.x - GRID_THICKNESS, _size.y - GRID_THICKNESS));

    for (int i = -1; i < _visible_slots; i = ++i) {
        if(i == -1){
            rectangle.setFillColor(sf::Color(179, 145, 81));
        }
        else rectangle.setFillColor(sf::Color(255, 211, 124));

        rectangle.setPosition(sf::Vector2f(_position.x+offset.x, i * _size.y + _position.y+offset.y));
        _window.draw(rectangle);
        if(i != -1){
            rectangle.setFillColor(sf::Color(179, 145, 81));

            rectangle.setSize(sf::Vector2f(100, rectangle.getSize().y));
            _window.draw(rectangle);
            rectangle.setSize(sf::Vector2f(_size.x - GRID_THICKNESS, _size.y - GRID_THICKNESS));

            sf::Text sftext;
            sftext.setCharacterSize(_size.y / 2);
            sftext.setColor(sf::Color::Black);
            sftext.setPosition(sf::Vector2f(_position.x+offset.x+130, (i) * _size.y + _position.y+offset.y));
            sftext.setString(std::to_string(i+1+_offset));
            sftext.setFont(font); // font is a sf::Font


            sf::FloatRect textRect = sftext.getLocalBounds();
            sftext.setOrigin(textRect.left + textRect.width/2.0f,
                             textRect.top  + textRect.height/2.0f);
            sftext.setPosition(sf::Vector2f(_position.x+offset.x+(100)/2.0f,(i) * _size.y + _position.y+offset.y+(_size.y)/2.0f));

            _window.draw(sftext);
        } else{
            sf::Text sftext;
            sftext.setCharacterSize(_size.y / 2);
            sftext.setColor(sf::Color::Black);
            sftext.setPosition(sf::Vector2f(_position.x+offset.x+130, (i) * _size.y + _position.y+offset.y));
            sftext.setString(_header);
            sftext.setFont(font); // font is a sf::Font


            sf::FloatRect textRect = sftext.getLocalBounds();
            sftext.setOrigin(textRect.left + textRect.width/2.0f,
                             textRect.top  + textRect.height/2.0f);
            sftext.setPosition(sf::Vector2f(_position.x+offset.x+(_size.x)/2.0f,(i) * _size.y + _position.y+offset.y+(_size.y)/2.0f));

            _window.draw(sftext);
        }

    }

    for (int i = _offset;
         i < std::min(_visible_slots + _offset, ((int) _elements.size())); ++i) {
        _elements[i]->draw(font);
    }
    sf::RectangleShape selected(rectangle);
    selected.setPosition(sf::Vector2f(_position.x+offset.x, (_selected_slot) * _size.y + _position.y+offset.y));
    selected.setFillColor(sf::Color::Transparent);
    selected.setOutlineThickness(GRID_SELECTED_THICKNESS);
    selected.setOutlineColor(sf::Color(0, 0, 0));
    _window.draw(selected);

    sf::RectangleShape rectangleArrow(sf::Vector2f(0, 0));
    rectangleArrow.setSize(sf::Vector2f(_size.y/1.5, _size.y/1.5));
    rectangleArrow.setPosition(sf::Vector2f(_position.x+offset.x+_size.x-_size.y/1.5, _position.y+offset.y));
    rectangleArrow.setFillColor(sf::Color(255, 255, 255));
    rectangleArrow.setOutlineThickness(GRID_THICKNESS);
    rectangleArrow.setOutlineColor(sf::Color(0, 0, 0));
    _window.draw(rectangleArrow);
    rectangleArrow.setPosition(sf::Vector2f(_position.x+offset.x+_size.x-_size.y/1.5, _position.y+offset.y+_size.y*(_visible_slots)-_size.y/1.5));
    _window.draw(rectangleArrow);

    sf::CircleShape triangleUp(_size.y/1.5/2-3,3);
    triangleUp.setFillColor(sf::Color::Black);
    triangleUp.setPosition(_position.x+offset.x+_size.x-_size.y/1.5+3,_position.y+offset.y+3);
    sf::CircleShape triangleDown(_size.y/1.5/2-3,3);
    triangleDown.setOrigin(triangleDown.getRadius(),triangleDown.getRadius());
    triangleDown.rotate(180);
    //triangleDown.setOrigin(0,0);
    triangleDown.setFillColor(sf::Color::Black);
    triangleDown.setPosition(_position.x+offset.x+_size.x-_size.y/1.5/2,_position.y+offset.y+_size.y*(_visible_slots)+_size.y/1.5/2-_size.y/1.5);

    _window.draw(triangleUp);
    _window.draw(triangleDown);
    //}
}
void InterfaceList::clear(){
    for(int i=0; i< _elements.size(); ++i){
        delete _elements[i];
    }
    _elements.clear();
}
int InterfaceList::getIdSelected(){
    if(_selected_slot >= 0 && _selected_slot+_offset <_elements.size()) return _selected_slot+_offset;
    else return -1;
}
std::vector<Interface*>& InterfaceList::getElements(){
    return _elements;
}
void InterfaceList::update(){
    Interface::update();
    sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
    if(!_elements.empty()) {
        sf::FloatRect buttonRect(
                _position.x,
                _position.y,
                _size.x,
                _size.y*_visible_slots);
        sf::FloatRect prevPage(
                _position.x+_size.x-_size.y/1.5,
                _position.y,
                _size.y/1.5,
                _size.y/1.5);
        sf::FloatRect nextPage(
                _position.x+_size.x-_size.y/1.5,
                _position.y+_size.y*(_visible_slots)-_size.y/1.5,
                _size.y/1.5,
                _size.y/1.5);
        bool next = Inputs::MouseBreak(Inputs::M_LEFT) && nextPage.contains(mousePos.x, mousePos.y);
        bool prev = Inputs::MouseBreak(Inputs::M_LEFT) && prevPage.contains(mousePos.x, mousePos.y);
        if(next) ++_offset;
        if(prev) _offset = std::max(_offset-1,0);
        int mouseOver = buttonRect.contains(mousePos.x, mousePos.y);

        mouseOver = mouseOver*((mousePos.y-_position.y)/_size.y+1);
        if(!next && !prev){
            int tab_selection_delta = Inputs::GetWheel();
            int up_key = Inputs::KeyBreak(Inputs::UP);
            int down_key = Inputs::KeyBreak(Inputs::DOWN);
            if (tab_selection_delta != 0 && mouseOver) {
                _selected_slot = (_selected_slot - tab_selection_delta);
            }
            else if(mouseOver && Inputs::MouseBreak(Inputs::M_LEFT)){
                _selected_slot = mouseOver-1;
            }
            else if (up_key == 1) _selected_slot -= 1;
            else if (down_key == 1) _selected_slot += 1;
            while (_selected_slot < 0) {
                _selected_slot = 0;
                _offset = std::max(0,_offset-1);
            }
            if(_selected_slot>=_visible_slots) {
                _selected_slot=_visible_slots-1;
                ++_offset;
            }

        }

        for (int i = _offset;
             i < std::min(_visible_slots + _offset, ((int) _elements.size())); ++i) {
            _elements[i]->setPosition(sf::Vector2f(_position.x+100, (i - _offset) * _size.y + _position.y));
        }
        for (int i = _offset;
             i < std::min(_visible_slots + _offset, ((int) _elements.size())); ++i) {
            _elements[i]->update();
        }

    }
}

void InterfaceList::update(sf::Vector2f offset){
    Interface::update(offset);
    sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
    if(!_elements.empty()) {
        sf::FloatRect buttonRect(
                _position.x+offset.x,
                _position.y+offset.y,
                _size.x,
                _size.y*_visible_slots);
        sf::FloatRect prevPage(
                _position.x+_size.x-_size.y/1.5+offset.x,
                _position.y+offset.y,
                _size.y/1.5,
                _size.y/1.5);
        sf::FloatRect nextPage(
                _position.x+_size.x-_size.y/1.5+offset.x,
                _position.y+_size.y*(_visible_slots)-_size.y/1.5+offset.y,
                _size.y/1.5,
                _size.y/1.5);
        bool next = Inputs::MouseBreak(Inputs::M_LEFT) && nextPage.contains(mousePos.x, mousePos.y);
        bool prev = Inputs::MouseBreak(Inputs::M_LEFT) && prevPage.contains(mousePos.x, mousePos.y);
        if(next) ++_offset;
        if(prev) _offset = std::max(_offset-1,0);
        int mouseOver = buttonRect.contains(mousePos.x, mousePos.y);

        mouseOver = mouseOver*((mousePos.y-_position.y+offset.y)/_size.y);
        if(!next && !prev){
            int tab_selection_delta = Inputs::GetWheel();
            int up_key = Inputs::KeyBreak(Inputs::UP);
            int down_key = Inputs::KeyBreak(Inputs::DOWN);
            if (tab_selection_delta != 0) {
                _selected_slot = (_selected_slot - tab_selection_delta);
            }
            else if(mouseOver && Inputs::MouseBreak(Inputs::M_LEFT)){
                _selected_slot = mouseOver;
            }
            else if (up_key == 1) _selected_slot -= 1;
            else if (down_key == 1) _selected_slot += 1;
            while (_selected_slot < 0) {
                _selected_slot = 0;
                _offset = std::max(0,_offset-1);
            }
            if(_selected_slot>=_visible_slots) {
                _selected_slot=_visible_slots-1;
                ++_offset;
            }

        }

        for (int i = _offset;
             i < std::min(_visible_slots + _offset, ((int) _elements.size())); ++i) {
            _elements[i]->setPosition(sf::Vector2f(_position.x+100+offset.x, (i - _offset) * _size.y + _position.y+offset.y));
        }

    }
}