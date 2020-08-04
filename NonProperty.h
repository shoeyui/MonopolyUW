#ifndef __NONPROPERTY_H__
#define __NONPROPERTY_H__

#include <iostream>
#include "Block.h"
#include "Player.h"

class NonProperty: public Block {
    string my_to_string(int i);
public:
    NonProperty(string name, int number);
    bool effect(Game *game, Player *p);
};

#endif
