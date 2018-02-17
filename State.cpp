//
// Created by arnito on 1/02/18.
//

#include <queue>
#include <cmath>
#include "State.hpp"

State::State(){
    _value = 0;


}
State::~State(){

}
void State::generateRandomState(std::vector<Meal*>& meals){
    int numMeals =meals.size();
    int repetitions[numMeals];
    std::vector<std::pair<Meal*, int> > m1;
    std::vector<std::pair<Meal*, int> > m2;
    std::vector<std::pair<Meal*, int> > m3;
    std::vector<std::pair<Meal*, int> > m4;
    std::vector<std::pair<Meal*, int> > m5;
    std::vector<std::pair<Meal*, int> > m6;
    for(int i=0; i<meals.size(); ++i){
        for(int j=0; j< meals[i]->dayzones.size(); ++j){
            if(meals[i]->dayzones[j]==1) m1.push_back(std::pair<Meal*, int>(meals[i],i));
            else if(meals[i]->dayzones[j]==2) m2.push_back(std::pair<Meal*, int>(meals[i],i));
            else if(meals[i]->dayzones[j]==3) m3.push_back(std::pair<Meal*, int>(meals[i],i));
            else if(meals[i]->dayzones[j]==4) m4.push_back(std::pair<Meal*, int>(meals[i],i));
            else if(meals[i]->dayzones[j]==5) m5.push_back(std::pair<Meal*, int>(meals[i],i));
            else if(meals[i]->dayzones[j]==6) m6.push_back(std::pair<Meal*, int>(meals[i],i));
        }
    }
    for(int i=0; i<numMeals; ++i){
        repetitions[i]=0;
    }
    for(int i=0; i<NUM_DAYS; ++i){
        std::vector<int> mealsToday;
        bool done = false;
        while(!done){
            int randIndex = std::rand() % m1.size();
            bool yetAssigned = false;
            for(int j=0; j<mealsToday.size(); ++j){
                if(mealsToday[j] == m1[randIndex].first->id) yetAssigned = true;
            }
            if(repetitions[m1[randIndex].second] < m1[randIndex].first->uses.second && !yetAssigned) {
                done = true;
                _meals[i][0].push_back(m1[randIndex].first->id);
                repetitions[m1[randIndex].second] +=1;
                mealsToday.push_back(m1[randIndex].first->id);
            }
        }
        done = false;
        while(!done){
            int randIndex = std::rand() % m2.size();
            bool yetAssigned = false;
            for(int j=0; j<mealsToday.size(); ++j){
                if(mealsToday[j] == m2[randIndex].first->id) yetAssigned = true;
            }
            if(repetitions[m2[randIndex].second] < m2[randIndex].first->uses.second && !yetAssigned) {
                done = true;
                _meals[i][1].push_back(m2[randIndex].first->id);
                repetitions[m2[randIndex].second] +=1;
                mealsToday.push_back(m2[randIndex].first->id);
            }
        }
        done = false;
        while(!done){
            int randIndex = std::rand() % m3.size();
            bool yetAssigned = false;
            for(int j=0; j<mealsToday.size(); ++j){
                if(mealsToday[j] == m3[randIndex].first->id) yetAssigned = true;
            }
            if(repetitions[m3[randIndex].second] < m3[randIndex].first->uses.second && !yetAssigned) {
                done = true;
                _meals[i][2].push_back(m3[randIndex].first->id);
                repetitions[m3[randIndex].second] +=1;
                mealsToday.push_back(m3[randIndex].first->id);
            }
        }
        done = false;
        while(!done){
            int randIndex = std::rand() % m4.size();
            bool yetAssigned = false;
            for(int j=0; j<mealsToday.size(); ++j){
                if(mealsToday[j] == m4[randIndex].first->id) yetAssigned = true;
            }
            if(repetitions[m4[randIndex].second] < m4[randIndex].first->uses.second && !yetAssigned) {
                done = true;
                _meals[i][3].push_back(m4[randIndex].first->id);
                repetitions[m4[randIndex].second] +=1;
                mealsToday.push_back(m4[randIndex].first->id);
            }
        }
        done = false;
        while(!done){
            int randIndex = std::rand() % m5.size();
            bool yetAssigned = false;
            for(int j=0; j<mealsToday.size(); ++j){
                if(mealsToday[j] == m5[randIndex].first->id) yetAssigned = true;
            }
            if(repetitions[m5[randIndex].second] < m5[randIndex].first->uses.second && !yetAssigned) {
                done = true;
                _meals[i][4].push_back(m5[randIndex].first->id);
                repetitions[m5[randIndex].second] +=1;
                mealsToday.push_back(m5[randIndex].first->id);
            }
        }
        done = false;
        while(!done){
            int randIndex = std::rand() % m6.size();
            bool yetAssigned = false;
            for(int j=0; j<mealsToday.size(); ++j){
                if(mealsToday[j] == m6[randIndex].first->id) yetAssigned = true;
            }
            if(repetitions[m6[randIndex].second] < m6[randIndex].first->uses.second && !yetAssigned) {
                done = true;
                _meals[i][5].push_back(m6[randIndex].first->id);
                repetitions[m6[randIndex].second] +=1;
                mealsToday.push_back(m6[randIndex].first->id);
            }
        }
    }
}

bool State::isValidState(std::vector<Meal*>& meals){
    return validAmountMealsEachZone() && noRepetitionMealsPerDay(meals.size()) && validRepetitionMealsDiet(meals);
}
bool State::validAmountMealsEachZone(){
    for(int i = 0; i< NUM_DAYS; ++i){
        if(_meals[i][0].size()<=0 || _meals[i][0].size()>MAX_NUM_MEALS_ZONE[0]) return false;
        if(_meals[i][1].size()<=0 || _meals[i][1].size()>MAX_NUM_MEALS_ZONE[1]) return false;
        if(_meals[i][2].size()<=0 || _meals[i][2].size()>MAX_NUM_MEALS_ZONE[2]) return false;
        if(_meals[i][3].size()<=0 || _meals[i][3].size()>MAX_NUM_MEALS_ZONE[3]) return false;
        if(_meals[i][4].size()<=0 || _meals[i][4].size()>MAX_NUM_MEALS_ZONE[4]) return false;
        if(_meals[i][5].size()<=0 || _meals[i][5].size()>MAX_NUM_MEALS_ZONE[5]) return false;
    }
    return true;
}
bool State::noRepetitionMealsPerDay(int numMeals){

    for(int i = 0; i< NUM_DAYS; ++i){
        bool found[numMeals];
        for(int i = 0; i < numMeals; ++i){
            found[i] = false;
        }
        for(int j=0; j< 6; ++j){
            for(int k = 0; k< _meals[i][j].size(); ++ k){
                if(found[_meals[i][j][k]-1]) return false;
                else found[_meals[i][j][k]-1] = true;
            }
        }
    }
    return true;
}
bool State::validRepetitionMealsDiet(std::vector<Meal*>& meals){
    int amount[meals.size()];
    for(int i = 0; i < meals.size(); ++i){
        amount[i] = 0;
    }
    for(int i = 0; i< NUM_DAYS; ++i){
        for(int j=0; j< 6; ++j){
            for(int k = 0; k< _meals[i][j].size(); ++ k){
                if(amount[_meals[i][j][k]-1] >= meals[_meals[i][j][k]-1]->uses.second) return false;
                else {
                    amount[_meals[i][j][k]-1] += 1;
                }
            }
        }
    }
}
bool State::validZoneMeal(std::vector<Meal*>& meals){
    for(int i = 0; i< NUM_DAYS; ++i){
        for(int j=0; j< NUM_DAYZONES; ++j){
            for(int k = 0; k< _meals[i][j].size(); ++ k){
                bool trobat = false;
                for(int kk =0; kk < meals[_meals[i][j][k]-1]->dayzones.size(); ++kk){
                    if(meals[_meals[i][j][k]-1]->dayzones[kk] == j+1) trobat = true;
                }
                if(!trobat) {
                    std::cout << "error greu" <<std::endl;
                    return false;
                }
            }
        }
    }
    return true;
}
int State::getNumMealsZone(int day, int zone){
    return _meals[day][zone].size();
}
int State::getMeal(int indexDay, int indexDayZone, int indexMeal){
    return _meals[indexDay][indexDayZone][indexMeal];
}
int State::getScore(){
    return _value;
}
void State::printStats(std::vector<Meal*>& meals) {
    for(int i = 0; i< NUM_DAYS; ++i){
        float fat = 0;
        float kcal = 0;
        float carb = 0;
        float prot = 0;
        for(int j=0; j< NUM_DAYZONES; ++j){
            for(int k = 0; k< _meals[i][j].size(); ++ k){
                fat += meals[_meals[i][j][k]-1]->fat;
                kcal += meals[_meals[i][j][k]-1]->kcal;
                carb += meals[_meals[i][j][k]-1]->carb;
                prot += meals[_meals[i][j][k]-1]->prot;
            }
        }
        float devKcal = kcal > GOAL_KCAL ? kcal - GOAL_KCAL : GOAL_KCAL - kcal;
        float devFat = fat > GOAL_FAT ? fat - GOAL_FAT : GOAL_FAT - fat;
        float devProt = prot > GOAL_PROT ? prot - GOAL_PROT : GOAL_PROT - prot;
        float devCarb = carb > GOAL_CARB ? carb - GOAL_CARB : GOAL_CARB - carb;
        std::cout << "DAY " << i << std::endl;
        std::cout << "Kcal: " << kcal << " (" << ((GOAL_KCAL+devKcal)/GOAL_KCAL-1)*100 << "%)" << std::endl;
        std::cout << "Fat: " << fat << " (" << ((GOAL_FAT+devFat)/GOAL_FAT-1)*100 << "%)" << std::endl;
        std::cout << "Prot: " << prot << " (" << ((GOAL_PROT+devProt)/GOAL_PROT-1)*100 << "%)" << std::endl;
        std::cout << "Carb: " << carb << " (" << ((GOAL_CARB+devCarb)/GOAL_CARB-1)*100 << "%)" << std::endl;
        std::cout << "//////////////////////" << std::endl;
    }
}
void State::calcScoreState(std::vector<Meal*>& meals){
    float total_dev = 0;
    for(int i = 0; i< NUM_DAYS; ++i){
        float dev = 0;
        float fat = 0;
        float kcal = 0;
        float carb = 0;
        float prot = 0;
        for(int j=0; j< NUM_DAYZONES; ++j){
            for(int k = 0; k< _meals[i][j].size(); ++ k){
                fat += meals[_meals[i][j][k]-1]->fat;
                kcal += meals[_meals[i][j][k]-1]->kcal;
                carb += meals[_meals[i][j][k]-1]->carb;
                prot += meals[_meals[i][j][k]-1]->prot;
            }
        }
        float devKcal = kcal > GOAL_KCAL ? kcal - GOAL_KCAL : GOAL_KCAL - kcal;
        float devFat = fat > GOAL_FAT ? fat - GOAL_FAT : GOAL_FAT - fat;
        float devProt = prot > GOAL_PROT ? prot - GOAL_PROT : GOAL_PROT - prot;
        float devCarb = carb > GOAL_CARB ? carb - GOAL_CARB : GOAL_CARB - carb;
        float percentKcal = ((GOAL_KCAL+devKcal)/GOAL_KCAL-1)*100;
        float percentFat = ((GOAL_FAT+devFat)/GOAL_FAT-1)*100;
        float percentProt = ((GOAL_PROT+devProt)/GOAL_PROT-1)*100;
        float percentCarb = ((GOAL_CARB+devCarb)/GOAL_CARB-1)*100;
        dev = std::pow(percentKcal*percentKcal + percentFat*percentFat + percentProt*percentProt + percentCarb*percentCarb,1.5);
        total_dev += dev;
    }
    _value = (int)total_dev;
}
State* State::getCopy(){
    State *res = new State();
    for(int i = 0; i< NUM_DAYS; ++i){
        for(int j=0; j< NUM_DAYZONES; ++j){
            for(int k = 0; k< _meals[i][j].size(); ++ k){
                res->_meals[i][j].push_back(_meals[i][j][k]);
            }
        }
    }
    return res;
}
State* State::getNewStateInc(int indexDay, int indexDayZone, int idMeal){
    State *res = getCopy();
    res->_meals[indexDay][indexDayZone].push_back(idMeal);
    return res;
}
State* State::getNewStateDec(int indexDay, int indexDayZone, int indexMeal){
    State *res = getCopy();
    res->_meals[indexDay][indexDayZone].erase(res->_meals[indexDay][indexDayZone].begin()+indexMeal);
    return res;
}
State* State::getNewStateChange(int indexDay, int indexDayZone, int indexMeal, int idMeal){
    State *res = getCopy();
    res->_meals[indexDay][indexDayZone][indexMeal] = idMeal;
    return res;
}
State* State::getNewStateCloneDay(int indexDayClone, int indexDayDelete){
    State *res = getCopy();
    for(int j=0; j< NUM_DAYZONES; ++j){
        res->_meals[indexDayDelete][j].clear();
        for(int k = 0; k< _meals[indexDayClone][j].size(); ++ k){
            res->_meals[indexDayDelete][j].push_back(_meals[indexDayClone][j][k]);
        }
    }
    return res;
}