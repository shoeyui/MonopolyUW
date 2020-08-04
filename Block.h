#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "MyInfoBoard.h"

using namespace std;

class Player;

const string COLOUR_DEFAULT_BACKGROUND = "\e[49m";

const string COLOUR_DEFAULT_FOREGROUND = "\e[39m";

const string STYLE_BLINK = "\e[5m";
const string STYLE_DEFAULT = "\e[0m";

class Block {
protected:
    string name;
    int number;
    vector<Player*> landers;
    
    void removeLander(Player *p);
    
    void repeat(string s, int times);
    void bar7();
    void bar14();
    void bar71();
    void bar7bar14();
    void bar7bar71();
public:
    Block(string name, int number);
    
    void setName(string name);
    void addLander(Player *p);
    string getName();
    int getNumber();
    vector<Player*> *gameGetLanders();
    
    virtual void print(int lineNum, int leftMargin, int topMargin, vector<Player*> players, MyInfoBoard &mib);
};

#endif
