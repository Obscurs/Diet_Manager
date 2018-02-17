//
// Created by arnito on 1/02/18.
//

#ifndef DIET_MANAGER_PLANER_HPP
#define DIET_MANAGER_PLANER_HPP

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Settings.hpp"
#include "State.hpp"

class Planer {
public:
    Planer(std::vector<Meal*>& meals);
    void generateMenu(sf::RenderWindow &_window);
    State* getMenu();
    const float DECREMENT = 500;
    const float MULTIPLYER = 1;
    const float BARRIER = 1200000;
private:
    void generateNeighbors();
    void generateIncs();
    void generateDecs();
    void generateChanges();
    void generateClones();
    std::vector<Meal*>& _meals;
    State *_currentState;
    State *_minState;
    std::vector<State*> _neighbours;
};


#endif //DIET_MANAGER_PLANER_HPP
