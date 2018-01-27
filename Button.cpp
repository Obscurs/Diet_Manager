//
// Created by ant on 03/11/16.
//

#include "Button.h"
#include "Inputs.h"
#include <iostream>

Button::Button(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, std::string txt, int t): Interface(window,position,size)
{
    _text = txt;
    _type = t;
    _isVisible = true;
}

Button::~Button()

{
}
void Button::setText(std::string s){
    _text = s;
}
void Button::draw(sf::Font font){

    if(_isVisible){
        sf::Text sftext;
        sftext.setCharacterSize(_size.y/2);
        sftext.setColor(sf::Color::Black);

        sftext.setFont(font); // font is a sf::Font
        sftext.setString(_text);
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
        if(_type==0){
            if(_mouseOver) rectangle.setFillColor(sf::Color(200, 200, 200));
            else rectangle.setFillColor(sf::Color(100, 100, 100));
        } else if(_type==1){
            rectangle.setOutlineThickness(2);
            rectangle.setOutlineColor(sf::Color(147, 91, 0));
            rectangle.setFillColor(sf::Color(255, 211, 124));
        }
        _window.draw(rectangle);
        _window.draw(sftext);


    }
}
void Button::update() {
    Interface::update();
}

void Button::draw(sf::Vector2f offset, sf::Font font){
    if(_isVisible){
        sf::Text sftext;
        sftext.setCharacterSize(_size.y/2);
        sftext.setColor(sf::Color::Black);

        sftext.setFont(font); // font is a sf::Font
        sftext.setString(_text);
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
        if(_type==0){
            if(_mouseOver) rectangle.setFillColor(sf::Color(200, 200, 200));
            else rectangle.setFillColor(sf::Color(100, 100, 100));
        } else if(_type==1){
            rectangle.setOutlineThickness(2);
            rectangle.setOutlineColor(sf::Color(147, 91, 0));
            rectangle.setFillColor(sf::Color(255, 211, 124));
        }
        _window.draw(rectangle);
        _window.draw(sftext);


    }
}
void Button::update(sf::Vector2f offset){
    Interface::update(offset);
}
