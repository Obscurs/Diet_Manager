//
// Created by arnito on 1/02/18.
//

#include <algorithm>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Planer.hpp"
Planer::Planer(std::vector<Meal*>& meals): _meals(meals){
    //_currentState = generateRandomState();
    State *s = new State();
    _minState = s;
    _currentState = s;
    _currentState->generateRandomState(meals);
}
State* Planer::getMenu(){
    return _minState;
}
void Planer::generateIncs(){
    std::vector<Meal*> m1;
    std::vector<Meal*> m2;
    std::vector<Meal*> m3;
    std::vector<Meal*> m4;
    std::vector<Meal*> m5;
    std::vector<Meal*> m6;
    for(int i=0; i<_meals.size(); ++i){
        for(int j=0; j< _meals[i]->dayzones.size(); ++j){
            if(_meals[i]->dayzones[j]==1) m1.push_back((_meals[i]));
            else if(_meals[i]->dayzones[j]==2) m2.push_back((_meals[i]));
            else if(_meals[i]->dayzones[j]==3) m3.push_back((_meals[i]));
            else if(_meals[i]->dayzones[j]==4) m4.push_back((_meals[i]));
            else if(_meals[i]->dayzones[j]==5) m5.push_back((_meals[i]));
            else if(_meals[i]->dayzones[j]==6) m6.push_back((_meals[i]));
        }
    }
    for(int i=0; i < NUM_DAYS; ++i){
        for(int j = 0; j< NUM_DAYZONES; ++j){
            if(j==0){
                for(int k = 0; k < m1.size(); ++k){
                    State* newState = _currentState->getNewStateInc(i,j,m1[k]->id);
                    if(newState->isValidState(_meals)) _neighbours.push_back(newState);
                }
            }
            else if(j==1){
                for(int k = 0; k < m2.size(); ++k){
                    State* newState = _currentState->getNewStateInc(i,j,m2[k]->id);
                    if(newState->isValidState(_meals)) _neighbours.push_back(newState);
                }
            }
            else if(j==2){
                for(int k = 0; k < m3.size(); ++k){
                    State* newState = _currentState->getNewStateInc(i,j,m3[k]->id);
                    if(newState->isValidState(_meals)) _neighbours.push_back(newState);
                }
            }
            else if(j==3){
                for(int k = 0; k < m4.size(); ++k){
                    State* newState = _currentState->getNewStateInc(i,j,m4[k]->id);
                    if(newState->isValidState(_meals)) _neighbours.push_back(newState);
                }
            }
            else if(j==4){
                for(int k = 0; k < m5.size(); ++k){
                    State* newState = _currentState->getNewStateInc(i,j,m5[k]->id);
                    if(newState->isValidState(_meals)) _neighbours.push_back(newState);
                }
            }
            else if(j==5){
                for(int k = 0; k < m6.size(); ++k){
                    State* newState = _currentState->getNewStateInc(i,j,m6[k]->id);
                    if(newState->isValidState(_meals)) _neighbours.push_back(newState);
                }
            }

        }
    }
}
void Planer::generateDecs(){
    for(int i=0; i < NUM_DAYS; ++i){
        for(int j = 0; j< NUM_DAYZONES; ++j){
            int numMealsZone = _currentState->getNumMealsZone(i,j);
            for(int k = 0; k < numMealsZone; ++k){
                State* newState = _currentState->getNewStateDec(i,j,k);
                if(newState->isValidState(_meals)) _neighbours.push_back(newState);
            }
        }
    }
}
void Planer::generateChanges(){
    std::vector<Meal*> m1;
    std::vector<Meal*> m2;
    std::vector<Meal*> m3;
    std::vector<Meal*> m4;
    std::vector<Meal*> m5;
    std::vector<Meal*> m6;
    for(int i=0; i<_meals.size(); ++i){
        for(int j=0; j< _meals[i]->dayzones.size(); ++j){
            if(_meals[i]->dayzones[j]==1) m1.push_back((_meals[i]));
            else if(_meals[i]->dayzones[j]==2) m2.push_back((_meals[i]));
            else if(_meals[i]->dayzones[j]==3) m3.push_back((_meals[i]));
            else if(_meals[i]->dayzones[j]==4) m4.push_back((_meals[i]));
            else if(_meals[i]->dayzones[j]==5) m5.push_back((_meals[i]));
            else if(_meals[i]->dayzones[j]==6) m6.push_back((_meals[i]));
        }
    }
    for(int i=0; i < NUM_DAYS; ++i){
        for(int j = 0; j< NUM_DAYZONES; ++j){
            int numMealsZone = _currentState->getNumMealsZone(i,j);
            for(int k = 0; k < numMealsZone; ++k){
                if(j==0){
                    for(int kk = 0; kk < m1.size(); ++kk){
                        State* newState = _currentState->getNewStateChange(i,j,k, m1[kk]->id);
                        if(newState->isValidState(_meals) && m1[kk]->id != _currentState->getMeal(i,j,k)) _neighbours.push_back(newState);
                    }
                }
                else if(j==1){
                    for(int kk = 0; kk < m2.size(); ++kk){
                        State* newState = _currentState->getNewStateChange(i,j,k, m2[kk]->id);
                        if(newState->isValidState(_meals) && m2[kk]->id != _currentState->getMeal(i,j,k)) _neighbours.push_back(newState);
                    }
                }
                else if(j==2){
                    for(int kk = 0; kk < m3.size(); ++kk){
                        State* newState = _currentState->getNewStateChange(i,j,k, m3[kk]->id);
                        if(newState->isValidState(_meals) && m3[kk]->id != _currentState->getMeal(i,j,k)) _neighbours.push_back(newState);
                    }
                }
                else if(j==3){
                    for(int kk = 0; kk < m4.size(); ++kk){
                        State* newState = _currentState->getNewStateChange(i,j,k, m4[kk]->id);
                        if(newState->isValidState(_meals) && m4[kk]->id != _currentState->getMeal(i,j,k)) _neighbours.push_back(newState);
                    }
                }
                else if(j==4){
                    for(int kk = 0; kk < m5.size(); ++kk){
                        State* newState = _currentState->getNewStateChange(i,j,k, m5[kk]->id);
                        if(newState->isValidState(_meals) && m5[kk]->id != _currentState->getMeal(i,j,k)) _neighbours.push_back(newState);
                    }
                }
                else if(j==5){
                    for(int kk = 0; kk < m6.size(); ++kk){
                        State* newState = _currentState->getNewStateChange(i,j,k, m6[kk]->id);
                        if(newState->isValidState(_meals) && m6[kk]->id != _currentState->getMeal(i,j,k)) _neighbours.push_back(newState);
                    }
                }

            }
        }
    }
}
void Planer::generateClones() {
    for(int i=0; i<NUM_DAYS; ++i){
        for(int j=0; j<NUM_DAYS; ++j){
            if(i != j) {
                State* newState = _currentState->getNewStateCloneDay(i,j);
                if(newState->isValidState(_meals)) {
                    _neighbours.push_back(newState);
                }
            }
        }
    }
}
bool compareStates(State* a, State* b) { return (a->getScore() < b->getScore()); }
void Planer::generateNeighbors(){
    for(int i=0; i< _neighbours.size(); ++i){
        if(_neighbours[i] != _currentState) delete _neighbours[i];
    }
    _neighbours.clear();

    generateIncs();
    generateDecs();
    generateChanges();
    generateClones();
    for(int i=0; i< _neighbours.size(); ++i){
        _neighbours[i]->calcScoreState(_meals);
    }
    _currentState->calcScoreState(_meals);
    std::sort(_neighbours.begin(), _neighbours.end(), compareStates);
}
void Planer::generateMenu(sf::RenderWindow &_window){
    int minScore = BARRIER*10;

    _currentState->calcScoreState(_meals);
    _minState = _currentState->getCopy();
    float temperature = BARRIER;
    int t=0;
    sf::RectangleShape rectangleBox(sf::Vector2f(0,0));
    rectangleBox.setPosition(sf::Vector2f(200, 200));
    rectangleBox.setSize(sf::Vector2f(500, 50));
    rectangleBox.setOutlineColor(sf::Color::Black);
    rectangleBox.setOutlineThickness(4.0);
    rectangleBox.setFillColor(sf::Color(240, 240, 240));
    _window.draw(rectangleBox);
    while(temperature > 0){
        std::cout << "Score: " << _currentState->getScore() << " MinScore: " << minScore << "    Temperature: " << temperature << std::endl;
        generateNeighbors();
        int indexCurrentScoreInNeighbours = 0;
        for(int i=0; i< _neighbours.size(); ++i){
            if(_currentState->getScore() <= _neighbours[i]->getScore()) break;
            else indexCurrentScoreInNeighbours = i;
        }
        if(_neighbours.size()==0) break;
        if(indexCurrentScoreInNeighbours == 0){
            float maxScoreAllowed = temperature;
            int indexMaxAllowed = 0;
            for(int i=0; i< _neighbours.size(); ++i){
                if(_neighbours[i]->getScore() > maxScoreAllowed) break;
                else indexMaxAllowed = i;
            }
            if(indexMaxAllowed==0) break;
            else {
                delete _currentState;
                _currentState = _neighbours[std::rand() % indexMaxAllowed];
            }
        } else {
            delete _currentState;
            _currentState = _neighbours[std::rand() % indexCurrentScoreInNeighbours];
        }
        /** UNCOMENT TO LOG COOLER **/
        //temperature = (BARRIER/(log(t+1)))*MULTIPLYER;
        /** END LOG COOLER **/

        /** UNCOMENT TO LINEAR COOLER **/
        temperature -= DECREMENT;
        /** END LINEAR COOLER **/
        if(_currentState->getScore() < minScore) {
            delete _minState;
            _minState = _currentState->getCopy();
            minScore = _currentState->getScore();
        }
        ++t;

        sf::RectangleShape rectangleCompleted(sf::Vector2f(0,0));
        rectangleCompleted.setPosition(sf::Vector2f(200, 200));
        rectangleCompleted.setSize(sf::Vector2f(((BARRIER-temperature)/BARRIER)*500,50));
        rectangleCompleted.setOutlineColor(sf::Color(100, 240, 0));
        rectangleCompleted.setOutlineThickness(2.0);
        rectangleCompleted.setFillColor(sf::Color(10, 240, 0));
        _window.draw(rectangleCompleted);
        _window.display();
    }
    _minState->calcScoreState(_meals);
    _minState->printStats(_meals);

}