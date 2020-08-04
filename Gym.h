#ifndef __GYM_H__
#define __GYM_H__

#include <iostream>
#include "Property.h"

class Gym: public Property {
public:
    Gym(string name, int number);
    int getTuition(int steps);
    void print(int lineNum, int leftMargin, int topMargin, vector<Player*> players, MyInfoBoard &mib);
};

#endif
