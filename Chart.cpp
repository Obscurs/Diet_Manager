//
// Created by arnito on 26/01/18.
//

#include "Chart.h"

Chart::Chart(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size): Interface(window,position,size)
{
    _position = position;
    _size = size;
    _isVisible = true;
}
Chart::~Chart(){

}
void Chart::insertValue(int value, std::string tag){
    _values.push_back(value);
    _tags.push_back(tag);
}
void Chart::clear(){
    _values.clear();
    _tags.clear();
}

void Chart::draw(sf::Font font){
    if(_isVisible){
        sf::RectangleShape background(sf::Vector2f(_size.x,_size.y-OFFSET_BOTTOM));
        background.setPosition(_position);
        background.setFillColor(sf::Color(255, 255, 255));
        background.setOutlineThickness(3);
        background.setOutlineColor(sf::Color(0, 0, 0));
        _window.draw(background);
        float max =0;
        for(int i=0; i<_values.size(); ++i){
            if(_values[i]>max)max = _values[i];
        }
        float sizeBarx = _size.x/(_values.size()*2+1);
        for(int i=0; i<_values.size(); ++i){
            float sizey = (_values[i]/max)*(_size.y-OFFSET_BOTTOM*2);
            sf::RectangleShape bar(sf::Vector2f(sizeBarx,sizey));
            bar.setPosition(sf::Vector2f(_position.x+i*2*sizeBarx+sizeBarx,_position.y+_size.y-sizey-OFFSET_BOTTOM));
            bar.setFillColor(sf::Color(0, 255, 0));
            bar.setOutlineThickness(2);
            bar.setOutlineColor(sf::Color(0, 0, 0));
            _window.draw(bar);



            sf::Text sftext;
            sftext.setCharacterSize(OFFSET_BOTTOM/1.5);
            sftext.setColor(sf::Color::Black);

            sftext.setFont(font); // font is a sf::Font

            sftext.setString(std::to_string(_values[i]));
            sftext.setPosition(sf::Vector2f(_position.x, _position.y));
            sf::FloatRect textRect = sftext.getLocalBounds();
            sftext.setOrigin(textRect.left + textRect.width/2.0f,
                             textRect.top  + textRect.height/2.0f);
            sftext.setPosition(sf::Vector2f(_position.x+i*2*sizeBarx+sizeBarx+(sizeBarx)/2.0f,_position.y+_size.y-sizey-OFFSET_BOTTOM+(OFFSET_BOTTOM)/2.0f-OFFSET_BOTTOM));

            _window.draw(sftext);


            sftext.setString(_tags[i]);
            sftext.setPosition(sf::Vector2f(_position.x, _position.y));
            textRect = sftext.getLocalBounds();
            sftext.setOrigin(textRect.left + textRect.width/2.0f,
                             textRect.top  + textRect.height/2.0f);
            sftext.setPosition(sf::Vector2f(_position.x+i*2*sizeBarx+sizeBarx+(sizeBarx)/2.0f,_position.y+_size.y+(OFFSET_BOTTOM)/2.0f-OFFSET_BOTTOM));

            _window.draw(sftext);
        }

    }
}
void Chart::updateValue(int value, std::string tag){
    for(int i=0; i< _values.size(); ++i){
        if(_tags[i] == tag) _values[i]= value;
    }
}