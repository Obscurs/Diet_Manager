//
// Created by arnito on 26/01/18.
//

#include "InterfaceSet.h"
InterfaceSet::InterfaceSet(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size): Interface(window,position,size){

}
InterfaceSet::~InterfaceSet(){
    for(int i=0; i< _interfaces.size(); ++i){
        delete _interfaces[i];
    }
    _interfaces.clear();
}
void InterfaceSet::clear(){
    for(int i=0; i< _interfaces.size(); ++i){
        delete _interfaces[i];
    }
    _interfaces.clear();
    _offsets.clear();
}
void InterfaceSet::draw(sf::Font font){
    for(int i=0; i< _interfaces.size(); ++i){
        _interfaces[i]->draw(_position+_offsets[i], font);
    }
}
void InterfaceSet::update(){
    for(int i=0; i< _interfaces.size(); ++i){
        _interfaces[i]->update(_position+_offsets[i]);
    }
}
void InterfaceSet::draw(sf::Vector2f offset, sf::Font font){
    for(int i=0; i< _interfaces.size(); ++i){
        _interfaces[i]->draw(_position+_offsets[i]+offset, font);
    }
}
void InterfaceSet::update(sf::Vector2f offset){
    for(int i=0; i< _interfaces.size(); ++i){
        _interfaces[i]->update(_position+_offsets[i]+offset);
    }
}
std::vector<Interface*>& InterfaceSet::getInterfaces(){
    return _interfaces;
}

void InterfaceSet::addInterface(Interface* interface, sf::Vector2f offset){
    _interfaces.push_back(interface);
    _offsets.push_back(offset);
}
std::vector<Interface*>& InterfaceSet::getElements(){
    return _interfaces;
}