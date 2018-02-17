//
// Created by arnito on 1/02/18.
//

#ifndef DIET_MANAGER_STATE_HPP
#define DIET_MANAGER_STATE_HPP


#include <vector>
#include "Settings.hpp"

class State {
public:
    State();
    ~State();
    void generateRandomState(std::vector<Meal*>& meals);
    bool isValidState(std::vector<Meal*>& meals);
    void calcScoreState(std::vector<Meal*>& meals);
    int getNumMealsZone(int day, int zone);
    int getMeal(int indexDay, int indexDayZone, int indexMeal);
    State* getNewStateInc(int indexDay, int indexDayZone, int idMeal);
    State* getNewStateDec(int indexDay, int indexDayZone, int indexMeal);
    State* getNewStateChange(int indexDay, int indexDayZone, int indexMeal, int idMeal);
    State* getNewStateCloneDay(int indexDayClone, int indexDayDelete);
    int getScore();
    State* getCopy();
    void printStats(std::vector<Meal*>& meals);
private:

    int _value;
    bool validAmountMealsEachZone();
    bool noRepetitionMealsPerDay(int numMeals);
    bool validRepetitionMealsDiet(std::vector<Meal*>& meals);
    bool validZoneMeal(std::vector<Meal*>& meals);

protected:
    std::vector<int> _meals[NUM_DAYS][NUM_DAYZONES];
};


#endif //DIET_MANAGER_STATE_HPP
