#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

#include "Property.h"
#include "RurCup.h"

using namespace std;

class Game;

const int INITIAL_BALANCE = 1500;

const int COLOUR_TYPE_FOREGROUND = 0;
const int COLOUR_TYPE_BACKGROUND = 1;

class Player {
    string name;
    char piece;
    int number;
    
    vector<Property*> properties;
    vector<RurCup*> rurCups;
    int cash;
    Block *landsOn;
    bool quit;
    
    int owing;
    Player *renter;
    
    bool forfeited;
    
    Game *game;
    bool myTurn;
    int inJail;
    int rollingTime;
    int doubleCount;
    
    int rollDice();
    void getOutOfJail();
    
    string my_to_string(int i);
public:
    Player();
    
    void setName(string name);
    string getName();
    
    void setPiece(char piece);
    char getPiece();
    
    void setNumber(int number);
    int getNumber();
    
    void setCash(int amount);
    void addCash(int amount);
    int getCash();
    
    void addProperty(Property *p);
    vector<Property*> *getProperties();
    int getNetWorth();
    
    void addCup(RurCup *rc);
    vector<RurCup*> *getRurCups();
    
    void setLandsOn(Block *landsOn);
    Block *getLandsOn();
    
    void itIsMyTurn();
    bool getMyTurn();
    
    bool getQuit();
    
    void setGame(Game *g);
    string getColour(int type);
    
    void setInJail(int inJail);
    int getInJail();
    
    void setForfeited(bool forfeited);
    bool getForfeited();
    
    bool roll(int firstDice = 0, int secondDice = 0);
    bool next();
    void leaveTimsLine(string payment);
    void trade(char tradeWithC, vector<string> propertyNames);
    void improve(string improveAbS, string buyOrSell);
    void mortgage(string propertyName);
    void unmortgage(string propertyName);
    void bankrupt();
    void assets();
    void save(string);
    
    bool movePlayer(int steps);
    
    void noEnoughCash();
    void checkCombo();
};

#endif
