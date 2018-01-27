//
// Created by arnito on 11/12/16.
//

#ifndef GENLAND_TEXTINPUT_H
#define GENLAND_TEXTINPUT_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Interface.h"
class TextInput: public Interface {
public:
    TextInput(sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f s, int tp, std::string text_default, std::string lab);
    ~TextInput();
    std::string _text;
    std::string _label;
    int _type;
    void draw(sf::Font font);
    void update();
    void draw(sf::Vector2f offset, sf::Font font);
    void update(sf::Vector2f offset);
    std::string getText();
    void setText(std::string new_text);
    bool _selected;
private:
    float _counter;
};


#endif //GENLAND_TEXTINPUT_H
