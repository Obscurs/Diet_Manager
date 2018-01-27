#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Inputs.h"
#include "Button.h"
#include "InterfaceList.h"
#include "Chart.h"
#include "TextInput.h"
#include "InterfaceSet.h"
#include "CheckBox.h"

struct Component {
    int id;
    std::string name;
    std::string type;
    float kcal;
    float prot;
    float carb;
    float fat;
    float amount;
    float priority;
    float stackAmount;
    std::string unit;
} ;

struct Meal {
    int id;
    std::string name;
    std::vector<float> ingredients;
    std::vector<float> amounts;
    std::vector<float> dayzones;
    std::pair<int,int> uses;
} ;
enum States{MENU_MEALS, MENU_EDIT_MEAL};
States _state = MENU_MEALS;
bool _exit = false;
int _numDays = 7;
int _numProtes = 155;
int _numFatDay = 85;
int _numCarbDay = 300;
int _numKcalDay = 2600;
int _marginStats = 10;
int _numDayZones = 6;
int _limitMealsZone = 3;
int _currentMealIndex = -1;
std::vector<Component*> _ingredients;
std::vector<Meal*> _meals;

sf::RenderWindow _window(sf::VideoMode(1800, 900), "SFML works!");
sf::Font _font;


InterfaceList _menu_inteface_list_meals(_window, sf::Vector2f(300,200),
                                      sf::Vector2f(500,50),
                                      0,
                                      12, "Menus");

InterfaceList _menu_inteface_list_ingredients(_window, sf::Vector2f(300,850),
                                        sf::Vector2f(500,50),
                                        0,
                                        1, "Add component");


Button _add_meal_button(_window, sf::Vector2f(300,800),sf::Vector2f(500,50),"+",0);
Button _show_kcal(_window, sf::Vector2f(900,550),sf::Vector2f(500,50),"EDIT",1);
Button _show_dayzones(_window, sf::Vector2f(900,600),sf::Vector2f(500,50),"EDIT",1);
Button _show_uses(_window, sf::Vector2f(900,650),sf::Vector2f(500,50),"EDIT",1);
Button _edit_meal(_window, sf::Vector2f(900,750),sf::Vector2f(500,50),"EDIT",0);
Button _delete_meal(_window, sf::Vector2f(900,800),sf::Vector2f(500,50),"DELETE",0);
Button _save_changes(_window, sf::Vector2f(900,850),sf::Vector2f(500,50),"SAVE CHANGES",0);
Button _back(_window, sf::Vector2f(900,800),sf::Vector2f(500,50),"BACK",0);
TextInput _minUses(_window, sf::Vector2f(1160,660),sf::Vector2f(20,30),0,"1","");
TextInput _maxUses(_window, sf::Vector2f(1190,660),sf::Vector2f(20,30),0,"1","");

CheckBox _c1(_window, sf::Vector2f(1160,610),sf::Vector2f(30,30),1);
CheckBox _c2(_window, sf::Vector2f(1200,610),sf::Vector2f(30,30),2);
CheckBox _c3(_window, sf::Vector2f(1240,610),sf::Vector2f(30,30),3);
CheckBox _c4(_window, sf::Vector2f(1280,610),sf::Vector2f(30,30),4);
CheckBox _c5(_window, sf::Vector2f(1320,610),sf::Vector2f(30,30),5);
CheckBox _c6(_window, sf::Vector2f(1360,610),sf::Vector2f(30,30),6);

Chart _show_meal_chart(_window,sf::Vector2f(900,150),sf::Vector2f(350,350));


InterfaceList _meal_ingredients_list(_window, sf::Vector2f(300,200),
                                        sf::Vector2f(500,50),
                                        0,
                                        12, "Components");


void savePlConfig(std::ofstream &myfile){
    myfile <<"numDays("+std::to_string(_numDays)+")." << "\n";
    myfile <<"numProtesDay("+std::to_string(_numProtes)+")."<< "\n";
    myfile <<"numFatDay("+std::to_string(_numFatDay)+")."<< "\n";
    myfile <<"numCarbDay("+std::to_string(_numCarbDay)+")."<< "\n";
    myfile <<"numKcalDay("+std::to_string(_numKcalDay)+")."<< "\n";
    myfile <<"marginStats("+std::to_string(_marginStats)+")."<< "\n";

    myfile <<"numDayZones("+std::to_string(_numDayZones)+")."<< "\n";

    myfile <<"numIngredients("+std::to_string(_ingredients.size())+")."<< "\n";
    myfile <<"numMeals("+std::to_string(_meals.size())+")."<< "\n";

    myfile <<"limitMealsZone("+std::to_string(_limitMealsZone)+")."<< "\n";
}
void savePlComponents(std::ofstream &myfile){
    for(int i=0; i<_ingredients.size(); ++i){
        myfile << "component(";
        myfile << _ingredients[i]->id  << ", " << _ingredients[i]->name << ", " << _ingredients[i]->type
               << ", " << _ingredients[i]->kcal << ", " << _ingredients[i]->prot << ", " << _ingredients[i]->carb << ", "
               << _ingredients[i]->fat << ", " << _ingredients[i]->amount << ", " << _ingredients[i]->priority << ", "
               << _ingredients[i]->stackAmount << ", " << _ingredients[i]->unit << ").\n";
    }
}
void savePlMeals(std::ofstream &myfile){
    for(int i=0; i< _meals.size(); ++i){
        myfile << "meal(";
        myfile << _meals[i]->id  << ", " << _meals[i]->name << ", [";
        for(int j=0; j<_meals[i]->ingredients.size(); ++j){
            if(j != _meals[i]->ingredients.size()-1) myfile << _meals[i]->ingredients[j] << ",";
            else myfile << _meals[i]->ingredients[j] << "]";
        }
        myfile <<", [";
        for(int j=0; j<_meals[i]->amounts.size(); ++j){
            if(j != _meals[i]->amounts.size()-1) myfile << _meals[i]->amounts[j] << ",";
            else myfile << _meals[i]->amounts[j] << "]";
        }
        myfile << ", [";
        for(int j=0; j<_meals[i]->dayzones.size(); ++j){
            if(j != _meals[i]->dayzones.size()-1) myfile << _meals[i]->dayzones[j] << ",";
            else myfile << _meals[i]->dayzones[j] << "]";
        }
        myfile << ", [" << _meals[i]->uses.first << ", " << _meals[i]->uses.second << "]).\n";
    }
}
void saveTextConfig(std::ofstream &myfile){
    myfile << _numDays << "\n";
    myfile <<_numProtes << "\n";
    myfile <<_numFatDay << "\n";
    myfile <<_numCarbDay << "\n";
    myfile <<_numKcalDay << "\n";
    myfile <<_marginStats << "\n";
    myfile <<_numDayZones << "\n";
    myfile << _limitMealsZone << "\n";
}
void saveTextComponents(std::ofstream &myfile){
    myfile << _ingredients.size() << "\n";
    for(int i=0; i< _ingredients.size(); ++i){
        myfile << _ingredients[i]->id  << " " << _ingredients[i]->name << " " << _ingredients[i]->type
               << " " << _ingredients[i]->kcal << " " << _ingredients[i]->prot << " " << _ingredients[i]->carb << " "
               << _ingredients[i]->fat << " " << _ingredients[i]->amount << " " << _ingredients[i]->priority << " "
               << _ingredients[i]->stackAmount << " " << _ingredients[i]->unit << "\n";
    }
}
void saveTextMeals(std::ofstream &myfile){
    myfile << _meals.size() << "\n";
    for(int i=0; i< _meals.size(); ++i){
        myfile << _meals[i]->id  << " " << _meals[i]->name << " " << _meals[i]->ingredients.size() << " ";
        for(int j=0; j<_meals[i]->ingredients.size(); ++j){
            myfile << _meals[i]->ingredients[j] << " ";
        }
        myfile << _meals[i]->amounts.size() << " ";
        for(int j=0; j<_meals[i]->amounts.size(); ++j){
            myfile << _meals[i]->amounts[j] << " ";
        }
        myfile << _meals[i]->dayzones.size() << " ";
        for(int j=0; j<_meals[i]->dayzones.size(); ++j){
            myfile << _meals[i]->dayzones[j] << " ";
        }
        myfile << _meals[i]->uses.first << " " << _meals[i]->uses.second << "\n";
    }
}
void loadConfig(std::ifstream &myfile){
    myfile >> _numDays;
    myfile >> _numProtes;
    myfile >> _numFatDay;
    myfile >> _numCarbDay;
    myfile >> _numKcalDay;
    myfile >> _marginStats;
    myfile >> _numDayZones;
    myfile >> _limitMealsZone;
}
void loadComponents(std::ifstream &myfile){
    int numIngredients = 0;
    myfile >> numIngredients;
    for(int i=0; i<numIngredients; ++i){
        Component *ing = new Component;
        myfile >> ing->id;
        myfile >> ing->name;
        myfile >> ing->type;
        myfile >> ing->kcal;
        myfile >> ing->prot;
        myfile >> ing->carb;
        myfile >> ing->fat;
        myfile >> ing->amount;
        myfile >> ing->priority;
        myfile >> ing->stackAmount;
        myfile >> ing->unit;
        _ingredients.push_back(ing);
    }
}
void loadMeals(std::ifstream &myfile){
    int numMeals = 0;
    myfile >> numMeals;
    for(int i=0; i<numMeals; ++i){
        Meal *me = new Meal;
        myfile >> me->id;
        myfile >> me->name;
        int numIngredients = 0;
        int numAmounts = 0;
        int numDayzones = 0;
        myfile >> numIngredients;
        for(int i=0; i< numIngredients; ++i){
            float value = -1;
            myfile >> value;
            me->ingredients.push_back(value);
        }
        myfile >> numAmounts;
        for(int i=0; i< numAmounts; ++i){
            float value = -1;
            myfile >> value;
            me->amounts.push_back(value);
        }
        myfile >> numDayzones;
        for(int i=0; i< numDayzones; ++i){
            float value = -1;
            myfile >> value;
            me->dayzones.push_back(value);
        }
        myfile >> me->uses.first;
        myfile >> me->uses.second;
        _meals.push_back(me);
    }
}
void loadText(){
    std::string route = "test_input";
    std::ifstream myfile(route);
    loadConfig(myfile);
    loadComponents(myfile);
    loadMeals(myfile);
    myfile.close();
}
void saveToPl(){
    std::string route = "entradaHoraris.pl";
    std::ofstream myfile(route);
    savePlConfig(myfile);
    savePlComponents(myfile);
    savePlMeals(myfile);
    myfile.close();
}
void saveToText(){
    std::string route = "test_input";
    std::ofstream myfile(route);
    saveTextConfig(myfile);
    saveTextComponents(myfile);
    saveTextMeals(myfile);
    myfile.close();
}

int calcKcalMeal(Meal* meal){
    float sum = 0;
    for(int i=0; i< meal->ingredients.size(); ++i){
        float amount = meal->amounts[i];
        std::vector<Component*>& aux = _ingredients;
        float kcalIng = _ingredients[int(meal->ingredients[i])-1]->kcal;
        sum += amount*kcalIng;
    }
    return sum;
}
int calcFatMeal(Meal* meal){
    float sum = 0;
    for(int i=0; i< meal->ingredients.size(); ++i){
        float amount = meal->amounts[i];
        std::vector<Component*>& aux = _ingredients;
        float kcalIng = _ingredients[int(meal->ingredients[i])-1]->fat;
        sum += amount*kcalIng;
    }
    return sum;
}
int calcCarbMeal(Meal* meal){
    float sum = 0;
    for(int i=0; i< meal->ingredients.size(); ++i){
        float amount = meal->amounts[i];
        std::vector<Component*>& aux = _ingredients;
        float kcalIng = _ingredients[int(meal->ingredients[i])-1]->carb;
        sum += amount*kcalIng;
    }
    return sum;
}
int calcProtMeal(Meal* meal){
    float sum = 0;
    for(int i=0; i< meal->ingredients.size(); ++i){
        float amount = meal->amounts[i];
        std::vector<Component*>& aux = _ingredients;
        float kcalIng = _ingredients[int(meal->ingredients[i])-1]->prot;
        sum += amount*kcalIng;
    }
    return sum;
}
void refreashIntefaceLists(){
    if(_currentMealIndex>= _meals.size())_currentMealIndex = -1;
    _menu_inteface_list_meals.clear();
    for(int i=0; i<_meals.size(); ++i){
        sf::Vector2f size = _menu_inteface_list_meals.getSize();
        size.x -= 100;
        Button *but = new Button(_window,sf::Vector2f(0,0),size,_meals[i]->name,1);
        _menu_inteface_list_meals.insertElement(but);
    }
}
void deleteMeal(int index){
    if(index<_meals.size()){
        _meals.erase(_meals.begin()+index);
        for(int i = index; i < _meals.size(); ++i){
            --_meals[i]->id;
        }
        refreashIntefaceLists();
    }

}
void newMeal(){
    Meal* m = new Meal;
    m->id = _meals.size();
    m->uses.first = 1;
    m->uses.second = 1;
    m->name = "new meal";
    _meals.push_back(m);
    refreashIntefaceLists();
    _currentMealIndex =_meals.size()-1;
    _state = MENU_EDIT_MEAL;
}
void setDayZonesValues(std::vector<float>& dz){
    for(int i=0; i<dz.size(); ++i){
        if(dz[i]==1){
            _c1.setValue(1);
        }
        else if(dz[i]==2){
            _c2.setValue(1);
        }
        else if(dz[i]==3){
            _c3.setValue(1);
        }
        else if(dz[i]==4){
            _c4.setValue(1);
        }
        else if(dz[i]==5){
            _c5.setValue(1);
        }
        else if(dz[i]==6){
            _c6.setValue(1);
        }
    }
}
void setDayZonesValues2(int mealIndex){
    Meal* m = _meals[mealIndex];
    m->dayzones.clear();
    if(_c1.getValue()){
        m->dayzones.push_back(1);
    }
    if(_c2.getValue()){
        m->dayzones.push_back(2);
    }
    if(_c3.getValue()){
        m->dayzones.push_back(3);
    }
    if(_c4.getValue()){
        m->dayzones.push_back(4);
    }
    if(_c5.getValue()){
        m->dayzones.push_back(5);
    }
    if(_c6.getValue()){
        m->dayzones.push_back(6);
    }

}
void setComponentsEditList(int compId){
    _currentMealIndex = compId;
    _meal_ingredients_list.clear();
    Meal* m = _meals[compId];
    for(int i=0; i<m->ingredients.size();++i){
        sf::Vector2f size = _meal_ingredients_list.getSize();
        size.x = (size.x-100)/3;
        sf::Vector2f size2;
        size2.x=size.x/2;
        size2.y= size.y;
        Button *but = new Button(_window,sf::Vector2f(0,0),size,_ingredients[m->ingredients[i]-1]->name,1);
        std::string amountIng = std::to_string(m->amounts[i]*_ingredients[m->ingredients[i]-1]->stackAmount);
        int sizeAmountIng = amountIng.size();

            while(sizeAmountIng >1 && amountIng[sizeAmountIng-1] == '0'){
                amountIng.resize( amountIng.size() - 1 );
                sizeAmountIng -=1;
            }
        if(amountIng[sizeAmountIng-1] == '.')amountIng.resize( amountIng.size() - 1 );


        TextInput *but2 = new TextInput(_window,sf::Vector2f(0,0),size2,0,amountIng,"");
        Button *but3 = new Button(_window,sf::Vector2f(0,0),size,_ingredients[m->ingredients[i]-1]->unit,1);
        Button *but4 = new Button(_window,sf::Vector2f(0,0),size2,"X",0);

        InterfaceSet *intList = new InterfaceSet(_window,sf::Vector2f(0,0),sf::Vector2f(0,0));
        intList->addInterface(but,sf::Vector2f(0,0));
        intList->addInterface(but2,sf::Vector2f(size.x,0));
        intList->addInterface(but3,sf::Vector2f(size.x+size2.x,0));
        intList->addInterface(but4,sf::Vector2f(size.x*2+size2.x,0));
        _meal_ingredients_list.insertElement(intList);
    }


}

void updateMenuMeals(sf::RenderWindow &_window){

    _menu_inteface_list_meals.update();
    _save_changes.update();
    _add_meal_button.update();
    int selected = _menu_inteface_list_meals.getIdSelected();
    if(selected>=0){

        _edit_meal.update();
        _delete_meal.update();

        _show_kcal.setText("Kcal: "+std::to_string(calcKcalMeal(_meals[selected])));
        std::string dayzones = "";
        for(int i = 0; i<_meals[selected]->dayzones.size(); ++i){
            dayzones.append(std::to_string(int(_meals[selected]->dayzones[i]))+" ");
        }
        _show_dayzones.setText("Day Zones: "+dayzones);
        _show_uses.setText("Uses: "+std::to_string(_meals[selected]->uses.first)+" - "+std::to_string(_meals[selected]->uses.second));
        _show_kcal.update();
        _show_dayzones.update();
        _show_uses.update();
        _show_meal_chart.clear();
        _show_meal_chart.insertValue(calcFatMeal(_meals[selected]),"FAT");
        _show_meal_chart.insertValue(calcProtMeal(_meals[selected]),"PROT");
        _show_meal_chart.insertValue(calcCarbMeal(_meals[selected]),"CARB");
        if(_edit_meal.isClicked()) {
            setComponentsEditList(selected);
            _state = MENU_EDIT_MEAL;
        }
    }
    if(_save_changes.isClicked()){
        saveToPl();
        saveToText();
        std::cout << "Saved changes" << std::endl;
    } else if(_delete_meal.isClicked()){
        deleteMeal(selected);
    } else if(_add_meal_button.isClicked()){
        newMeal();
    }

}

void drawMenuMeals(sf::RenderWindow &_window, sf::Font font){
    _menu_inteface_list_meals.draw(font);
    _add_meal_button.draw(font);
    int selected = _menu_inteface_list_meals.getIdSelected();
    if(selected>=0){
        _edit_meal.draw(font);
        _delete_meal.draw(font);
        _show_kcal.draw(font);
        _show_dayzones.draw(font);
        _show_uses.draw(font);
        _show_meal_chart.draw(font);
    }
    _save_changes.draw(font);
}

void deleteIngredientMeal(int ingIndex, int mealIndex){
    Meal* m = _meals[mealIndex];
    m->ingredients.erase(m->ingredients.begin()+ingIndex);
    m->amounts.erase(m->amounts.begin()+ingIndex);
    setComponentsEditList(mealIndex);
}
void setIngredientMealAmount(int ingIndex, int mealIndex, float value){
    Meal* m = _meals[mealIndex];
    float amountUnity =0;
    for(int i=0; i< _ingredients.size(); ++i){
        if(_ingredients[i]->id == m->ingredients[ingIndex]){
            amountUnity = _ingredients[i]->stackAmount;
            break;
        }
    }
    m->amounts[ingIndex] = value/amountUnity;
}

void addIngredientToMeal(int ingIndex, int mealIndex){
    Meal* m = _meals[mealIndex];
    m->ingredients.push_back(_ingredients[ingIndex]->id);
    m->amounts.push_back(1);
    setComponentsEditList(mealIndex);
}
void updateEditMeals(sf::RenderWindow &_window){

    _meal_ingredients_list.update();
    _menu_inteface_list_ingredients.update();

    _show_kcal.setText("Kcal: "+std::to_string(calcKcalMeal(_meals[_currentMealIndex])));
    std::string dayzones = "";
    for(int i = 0; i<_meals[_currentMealIndex]->dayzones.size(); ++i){
        dayzones.append(std::to_string(int(_meals[_currentMealIndex]->dayzones[i]))+" ");
    }
    _show_dayzones.setText("Day Zones: "+dayzones);
    _show_uses.setText("Uses: "+std::to_string(_meals[_currentMealIndex]->uses.first)+" - "+std::to_string(_meals[_currentMealIndex]->uses.first));
    _show_kcal.update();
    _show_dayzones.update();
    _show_uses.update();
    _show_meal_chart.clear();
    _show_meal_chart.insertValue(calcFatMeal(_meals[_currentMealIndex]),"FAT");
    _show_meal_chart.insertValue(calcProtMeal(_meals[_currentMealIndex]),"PROT");
    _show_meal_chart.insertValue(calcCarbMeal(_meals[_currentMealIndex]),"CARB");
    _back.update();
    _minUses.setText(std::to_string(_meals[_currentMealIndex]->uses.first));
    _maxUses.setText(std::to_string(_meals[_currentMealIndex]->uses.second));
    _minUses.update();
    _maxUses.update();
    _c1.setValue(0);
    _c2.setValue(0);
    _c3.setValue(0);
    _c4.setValue(0);
    _c5.setValue(0);
    _c6.setValue(0);
    setDayZonesValues(_meals[_currentMealIndex]->dayzones);
    _c1.update();
    _c2.update();
    _c3.update();
    _c4.update();
    _c5.update();
    _c6.update();
    int selected = _meal_ingredients_list.getIdSelected();
    if(selected>=0){

        std::vector<Interface*> ingredients = _meal_ingredients_list.getElements();
        for(int i = 0; i<ingredients.size(); ++i){
            InterfaceSet *is = static_cast<InterfaceSet*>(ingredients[i]);
            std::vector<Interface*> interfaces = is->getElements();
            if(interfaces[3]->isClicked()){
                deleteIngredientMeal(i, _currentMealIndex);
                break;
            } else {
                TextInput *textInt = static_cast<TextInput*>(interfaces[1]);
                std::string amountxt = textInt->getText();
                if(amountxt=="") amountxt = "0";
                setIngredientMealAmount(i, _currentMealIndex,std::stof(amountxt));
            }
        }

    }
    std::vector<Interface*> ingredientsAdd = _menu_inteface_list_ingredients.getElements();
    for(int i = 0; i<ingredientsAdd.size(); ++i){
        InterfaceSet *is = static_cast<InterfaceSet*>(ingredientsAdd[i]);
        std::vector<Interface*> interfaces = is->getElements();
        if(interfaces[1]->isClicked()){
            addIngredientToMeal(i, _currentMealIndex);
            break;
        }
    }
    Meal* m = _meals[_currentMealIndex];
    std::string numdays = _minUses.getText();
    if(numdays=="") numdays = "0";
    m->uses.first = std::stof(numdays);
    numdays = _maxUses.getText();
    if(numdays=="") numdays = "0";
    m->uses.second = std::stof(numdays);
    setDayZonesValues2(_currentMealIndex);

}
void drawEditMeals(sf::RenderWindow &_window, sf::Font font){
    _meal_ingredients_list.draw(font);
    _menu_inteface_list_ingredients.draw(font);
    _show_kcal.draw(font);
    _show_dayzones.draw(font);
    _show_uses.draw(font);
    _show_meal_chart.draw(font);
    _back.draw(font);
    _minUses.draw(font);
    _maxUses.draw(font);
    _c1.draw(font);
    _c2.draw(font);
    _c3.draw(font);
    _c4.draw(font);
    _c5.draw(font);
    _c6.draw(font);
    if(_back.isClicked())_state = MENU_MEALS;
    int selected = _meal_ingredients_list.getIdSelected();
    if(selected>=0){

    }
}

void Events(sf::RenderWindow &_window){
    sf::Event currentEvent;
    while(_window.pollEvent(currentEvent))
    {
        if(currentEvent.type == sf::Event::MouseWheelMoved)
        {
            Inputs::UpdateWheel(currentEvent.mouseWheel.delta);
        }

        else if (currentEvent.type == sf::Event::Closed)
        {
            _exit=true;
        } if (currentEvent.type == sf::Event::KeyPressed) {
            Inputs::KeyPressed(currentEvent.key.code);
        }
        else if (currentEvent.type == sf::Event::KeyReleased) {
            Inputs::KeyReleased(currentEvent.key.code);
        } else if (currentEvent.type == sf::Event::MouseButtonPressed) {
            Inputs::ButtonPressed(currentEvent.mouseButton.button);
        }
        else if (currentEvent.type == sf::Event::MouseButtonReleased) {
            Inputs::ButtonReleased(currentEvent.mouseButton.button);
        }
        if(currentEvent.type == sf::Event::TextEntered) {
            if (((currentEvent.text.unicode < 58 && currentEvent.text.unicode >= 48) ||
                 currentEvent.text.unicode == 8)) Inputs::TextPressed(currentEvent.text.unicode);
        }

        /*
        if(currentEvent._type == sf::Event::TextEntered && _gameState == Game::NewGame)
        {
            if(((currentEvent._text.unicode < 58 && currentEvent._text.unicode >= 48) || currentEvent._text.unicode == 8 ) && NewGameMenu::seed._selected)
            {
                std::string name = NewGameMenu::seed.getText();
                if( currentEvent._text.unicode == 13 ) // return key
                {
                    // finished entering name
                } else if( currentEvent._text.unicode == 8 ) { // backspace
                    if( name._size() > 0 ) name.resize( name._size() - 1 );
                } else if(name._size()<10){
                    name += static_cast<char>(currentEvent._text.unicode);
                }
                NewGameMenu::seed.setText( name );
            }
            else if(((currentEvent._text.unicode < 128 && currentEvent._text.unicode >= 48) || currentEvent._text.unicode == 8 )&& NewGameMenu::name._selected)
            {
                std::string name = NewGameMenu::name.getText();
                if( currentEvent._text.unicode == 13 ) // return key
                {
                    // finished entering name
                } else if( currentEvent._text.unicode == 8 ) { // backspace
                    if( name._size() > 0 ) name.resize( name._size() - 1 );
                } else if(name._size()<10){
                    name += static_cast<char>(currentEvent._text.unicode);
                }
                NewGameMenu::name.setText( name );
            }
        }else if(currentEvent._type == sf::Event::TextEntered && _gameState == Game::Playing && Debuger::isTerminalActive())
        {
            if(((currentEvent._text.unicode < 128 && currentEvent._text.unicode >= 48) || currentEvent._text.unicode == 8  || currentEvent._text.unicode == 32 || currentEvent._text.unicode == 13))
            {
                std::string instruction = Debuger::getTerminalText();
                if( currentEvent._text.unicode == 13 ) // return key
                {
                    Debuger::sendTerminalInstruction( );
                } else if( currentEvent._text.unicode == 8 ) { // backspace
                    if( instruction._size() > 0 ) {
                        instruction.resize( instruction._size() - 1 );
                    }
                    Debuger::setTerminalText( instruction );
                } else if(instruction._size()<64){
                    instruction += static_cast<char>(currentEvent._text.unicode);
                    Debuger::setTerminalText( instruction );
                } else {
                    Debuger::setTerminalText( instruction );
                }

            }
        }
         */
    }
}


int main() {
    loadText();
    refreashIntefaceLists();
    for(int i=0; i<_ingredients.size(); ++i){
        sf::Vector2f size = _menu_inteface_list_ingredients.getSize();
        size.x = (size.x-100)/2;
        Button *but = new Button(_window,sf::Vector2f(0,0),size,_ingredients[i]->name,1);
        Button *but4 = new Button(_window,sf::Vector2f(0,0),size,"+",0);
        InterfaceSet *intList = new InterfaceSet(_window,sf::Vector2f(0,0),sf::Vector2f(0,0));
        intList->addInterface(but,sf::Vector2f(0,0));
        intList->addInterface(but4,sf::Vector2f(size.x,0));
        _menu_inteface_list_ingredients.insertElement(intList);
    }

    if (!_font.loadFromFile("resources/font1.ttf"))
    {
        std::cout << "_font error" << std::endl;
    }
    while (!_exit)
    {
        Inputs::Update();
        Events(_window);
        _window.clear(sf::Color::White);

        switch(_state){
            case MENU_MEALS:
                updateMenuMeals(_window);

                drawMenuMeals(_window,_font);
                break;
            case MENU_EDIT_MEAL:
                updateEditMeals(_window);

                drawEditMeals(_window,_font);
                break;
            default:
                break;
        }
        _window.display();
    }

    return 0;
}