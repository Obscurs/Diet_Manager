//
// Created by arnito on 1/02/18.
//

#ifndef DIET_MANAGER_SETTINGS_HPP
#define DIET_MANAGER_SETTINGS_HPP

#include <vector>
#include <iostream>
const int MAX_NUM_MEALS_ZONE[6] = {1, 3, 1, 3, 2, 2};
const int NUM_DAYS = 7;
const int NUM_DAYZONES = 6;
const int GOAL_PROT = 155;
const int GOAL_FAT = 85;
const int GOAL_CARB = 300;
const int GOAL_KCAL = 2600;
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
    float kcal;
    float prot;
    float carb;
    float fat;
} ;

#endif //DIET_MANAGER_SETTINGS_HPP
