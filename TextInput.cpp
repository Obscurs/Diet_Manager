//
// Created by arnito on 11/12/16.
//

#include "TextInput.h"
#include "Inputs.h"
#include <iostream>
TextInput::TextInput(sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f s, int tp, std::string text_default, std::string lab): Interface(window, pos,s)
{
    _text = text_default;
    _type = tp;
    _label = lab;
    _selected = false;
    _counter = 0;
}

TextInput::~TextInput()
{
}
std::string TextInput::getText(){
    return _text;
}
void TextInput::setText(std::string new_text){
    _text = new_text;
}

void TextInput::draw(sf::Font font){

    if(_type==0){
        std::string barra = "";
        if(_counter <0.75 && _selected) barra = "_";
        std::string final_text = _label;
        final_text.append(_text);
        sf::Text sftext;
        sftext.setCharacterSize(_size.y/2);
        sftext.setColor(sf::Color::Black);
        sftext.setPosition(sf::Vector2f(_position.x, _position.y));
        sftext.setString(final_text+barra);
        sftext.setFont(font); // font is a sf::Font


        sf::RectangleShape rectangle(sf::Vector2f(0,0));
        rectangle.setPosition(sf::Vector2f(_position.x, _position.y));
        rectangle.setSize(sf::Vector2f(_size.x, _size.y));
        rectangle.setOutlineColor(sf::Color::Black);
        rectangle.setOutlineThickness(4.0);
        if(_selected)rectangle.setFillColor(sf::Color(200, 200, 200));
        else rectangle.setFillColor(sf::Color(100, 100, 100));
        _window.draw(rectangle);
        _window.draw(sftext);
    }

}
void TextInput::update(){
    Interface::update();
    if(_clicked) _selected=true;
    else if(Inputs::MouseBreak(Inputs::M_LEFT)) _selected = false;
    _counter -= 0.005;
    if(_counter <=0) _counter =1.5;
    int key = Inputs::GetText();
    if(key !=-1 && _selected){
        if(key==8 && _text.size()>0){
            _text.resize( _text.size() - 1 );
        }
        else if(key==13){

        } else if(_text.size()<5 && key!=8){
            _text += static_cast<char>(key);
        }

    }

}
void TextInput::draw(sf::Vector2f offset, sf::Font font){

    if(_type==0){
        std::string barra = "";
        if(_counter <0.75 && _selected) barra = "_";
        std::string final_text = _label;
        final_text.append(_text);
        sf::Text sftext;
        sftext.setCharacterSize(_size.y/2);
        sftext.setColor(sf::Color::Black);
        sftext.setPosition(sf::Vector2f(_position.x+offset.x, _position.y+offset.y));
        sftext.setString(final_text+barra);
        sftext.setFont(font); // font is a sf::Font


        sf::RectangleShape rectangle(sf::Vector2f(0,0));
        rectangle.setPosition(sf::Vector2f(_position.x+offset.x, _position.y+offset.y));
        rectangle.setSize(sf::Vector2f(_size.x, _size.y));
        rectangle.setOutlineColor(sf::Color::Black);
        rectangle.setOutlineThickness(4.0);
        if(_selected)rectangle.setFillColor(sf::Color(200, 200, 200));
        else rectangle.setFillColor(sf::Color(100, 100, 100));
        _window.draw(rectangle);
        _window.draw(sftext);
    }

}
void TextInput::update(sf::Vector2f offset){
    Interface::update(offset);
    if(_clicked) _selected=true;
    else if(Inputs::MouseBreak(Inputs::M_LEFT)) _selected = false;
    _counter -= 0.005;
    if(_counter <=0) _counter =1.5;
    int key = Inputs::GetText();
    if(key !=-1 && _selected){
        if(key==8 && _text.size()>0){
            _text.resize( _text.size() - 1 );
        }
        else if(key==13){

        } else if(_text.size()<5 && key!=8){
            _text += static_cast<char>(key);
        }

    }
}
