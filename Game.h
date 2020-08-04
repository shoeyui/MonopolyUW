#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <vector>
#include <map>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>

#include "Block.h"
#include "Player.h"
#include "NonProperty.h"
#include "AcademicBuilding.h"
#include "Residence.h"
#include "Gym.h"
#include "MyInfoBoard.h"

using namespace std;

const int MAX_NUM_OF_PLAYERS = 7;
const int OSAP_AMOUNT = 200;

class Game {
    Block *gameboard[40];
    int numOfPlayers;
    vector<Player*> players;
    MyInfoBoard mib;
    
    int gameBoardArrayNumbers[28];
    
    bool debugMode;

    struct Piece {
        char symbol;
        string discription;
    };
    map<char, string> pieces;
    
    int myWindowWidth, myWindowHeight, myLeftMargin, myTopMargin;
    
    void clearScreen(int windowHeight);
    
    string my_to_string(int i);
public:
    Game(bool debugMode);
    Game(bool debugMode, string filename);
    ~Game();
    void play();
    
    vector<Player*> *getPlayers();
    MyInfoBoard &getMIB();
    Block **getGameBoard();
    int *getGameBoardArrayNumbers();
    bool getDebugMode();
    
    void printHelp();
    void printBoard();
};

#endif
