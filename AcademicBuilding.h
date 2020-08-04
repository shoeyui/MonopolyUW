#ifndef __ACADEMIC_BUILDING_H__
#define __ACADEMIC_BUILDING_H__

#include <iostream>
#include <iomanip>

#include "Property.h"

class AcademicBuilding: public Property {
    int improvementCost;
    int tuitionWithImprovements[6];
    int improvementLevel;
    
    string getColour();
    
    string my_to_string(int i);
public:
    AcademicBuilding(string name, int number, int purchaseCost, int bastTuition, int improvementCost, int tuition1, int tuition2, int tuition3, int tuition4, int tuition5);
    
    void setImprovementLevel(int improvementLevel);
    int getTuition(int steps);
    int getImprovementCost();
    int getImprovementLevel();
    
    bool monopolyImprovementsAreClear(Block** gameBoard);
    
    void improve(bool buy, Game *game);
    
    void print(int lineNum, int leftMargin, int topMargin, vector<Player*> players, MyInfoBoard &mib);
};

#endif
