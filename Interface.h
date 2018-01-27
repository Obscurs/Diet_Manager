//
// Created by arnito on 26/01/18.
//

#ifndef DIET_MANAGER_INTERFACE_H
#define DIET_MANAGER_INTERFACE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Interface {
public:
    Interface(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size);
    ~Interface();
    bool isClicked();
    void unhide();
    void hide();
    virtual void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    virtual void draw(sf::Font font);
    virtual void update();
    virtual void draw(sf::Vector2f offset, sf::Font font);
    virtual void update(sf::Vector2f offset);
private:
protected:
    sf::RenderWindow& _window;
    bool _isVisible;
    sf::Vector2f _position;
    sf::Vector2f _size;
    bool _clicked;
    bool _mouseOver;
};


#endif //DIET_MANAGER_INTERFACE_H
