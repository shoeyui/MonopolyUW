#ifndef __RESIDENCE_H__
#define __RESIDENCE_H__

#include <iostream>

#include "Property.h"

class Residence: public Property {
public:
    Residence(string name, int number);
    int getTuition(int steps);
    void print(int lineNum, int leftMargin, int topMargin, vector<Player*> players, MyInfoBoard &mib);
};

#endif
