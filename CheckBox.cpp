//
// Created by arnito on 27/01/18.
//

#include "CheckBox.h"
CheckBox::CheckBox(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, int id): Interface(window,position,size){
    _value = false;
    _id = id;
}
CheckBox::~CheckBox(){

}
bool CheckBox::getValue(){
    return _value;
}
void CheckBox::changeState(){
    _value = !_value;
}
int CheckBox::getId(){
    return _id;
}
void CheckBox::setValue(bool val){
    _value = val;
}
void CheckBox::draw(sf::Font font){
    if(_isVisible){
        sf::Text sftext;
        sftext.setCharacterSize(_size.y/2);
        sftext.setColor(sf::Color::Black);

        sftext.setFont(font); // font is a sf::Font
        sf::String s;
        if(_value) s = "X";
        else s = "";
        sftext.setString(s);
        sftext.setPosition(sf::Vector2f(_position.x, _position.y));
        sf::FloatRect textRect = sftext.getLocalBounds();
        sftext.setOrigin(textRect.left + textRect.width/2.0f,
                         textRect.top  + textRect.height/2.0f);
        sftext.setPosition(sf::Vector2f(_position.x+(_size.x)/2.0f,_position.y+(_size.y)/2.0f));
        sf::RectangleShape rectangle(sf::Vector2f(0,0));
        rectangle.setPosition(sf::Vector2f(_position.x, _position.y));
        rectangle.setSize(sf::Vector2f(_size.x, _size.y));
        rectangle.setOutlineColor(sf::Color::Black);
        rectangle.setOutlineThickness(4.0);

        if(_mouseOver) rectangle.setFillColor(sf::Color(200, 200, 200));
        else rectangle.setFillColor(sf::Color(100, 100, 100));

        _window.draw(rectangle);
        _window.draw(sftext);


    }
}
void CheckBox::update(){
    Interface::update();
    if(isClicked()) changeState();
}
void CheckBox::draw(sf::Vector2f offset, sf::Font font){
    if(_isVisible){
        sf::Text sftext;
        sftext.setCharacterSize(_size.y/2);
        sftext.setColor(sf::Color::Black);

        sftext.setFont(font); // font is a sf::Font
        sf::String s;
        if(_value) s = "X";
        else s = "";
        sftext.setString(s);
        sftext.setPosition(sf::Vector2f(_position.x+offset.x, _position.y+offset.y));
        sf::FloatRect textRect = sftext.getLocalBounds();
        sftext.setOrigin(textRect.left + textRect.width/2.0f,
                         textRect.top  + textRect.height/2.0f);
        sftext.setPosition(sf::Vector2f(_position.x+(_size.x)/2.0f+offset.x,_position.y+offset.y+(_size.y)/2.0f));
        sf::RectangleShape rectangle(sf::Vector2f(0,0));
        rectangle.setPosition(sf::Vector2f(_position.x+offset.x, _position.y+offset.y));
        rectangle.setSize(sf::Vector2f(_size.x, _size.y));
        rectangle.setOutlineColor(sf::Color::Black);
        rectangle.setOutlineThickness(4.0);

        if(_mouseOver) rectangle.setFillColor(sf::Color(200, 200, 200));
        else rectangle.setFillColor(sf::Color(100, 100, 100));

        _window.draw(rectangle);
        _window.draw(sftext);


    }
}
void CheckBox::update(sf::Vector2f offset){
    Interface::update(offset);
    if(isClicked()) changeState();
}
