#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include <iostream>

#include "Block.h"

using namespace std;

class Player;
class Game;

class Property: public Block {
private:
    string my_to_string(int i);
protected:
    Player *owner;
    int purchaseCost;
    bool combo;
    bool mortgaged;
public:
    Property(string name, int number, int purchaseCost);
    
    void setOwner(Player *p);
    Player *getOwner();
    int getPurchaseCost();
    virtual int getTuition(int steps) = 0;
    void setCombo(bool combo);
    bool getCombo();
    
    void setMortgaged(bool mortgaged);
    bool getMortgaged();
    
    void holdAuction(Game *game, vector<Player*> *bidders, int startingFrom);
    void printOwnership();
};

#endif
