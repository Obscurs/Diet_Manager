//
// Created by arnito on 26/01/18.
//

#include "Interface.h"
#include "Inputs.h"

Interface::Interface(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size):
    _window(window)
{
    _clicked = false;
    _isVisible = true;
    _position = position;
    _size = size;
}
Interface::~Interface(){

}
bool Interface::isClicked(){
    return _clicked && _isVisible;
}
void Interface::unhide(){
    _isVisible = true;
}
void Interface::hide(){
    _isVisible = false;
}
void Interface::draw(sf::Font font){

}
void Interface::update(){
    if(_isVisible){
        sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
        sf::FloatRect buttonRect(
                _position.x,
                _position.y,
                _size.x,
                _size.y);
        _mouseOver = buttonRect.contains(mousePos.x, mousePos.y);
        _clicked = Inputs::MouseBreak(Inputs::M_LEFT) && _mouseOver;
    }
}

void Interface::draw(sf::Vector2f offset, sf::Font font){

}
void Interface::update(sf::Vector2f offset){
    if(_isVisible){
        sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
        sf::FloatRect buttonRect(
                _position.x+offset.x,
                _position.y+offset.y,
                _size.x,
                _size.y);
        _mouseOver = buttonRect.contains(mousePos.x, mousePos.y);
        _clicked = Inputs::MouseBreak(Inputs::M_LEFT) && _mouseOver;
    }
}

void Interface::setPosition(sf::Vector2f pos) {
    _position = pos;
}
sf::Vector2f Interface::getPosition(){
    return _position;
}
sf::Vector2f Interface::getSize(){
    return _size;
}
