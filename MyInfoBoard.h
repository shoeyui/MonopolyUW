#ifndef __MYINFOBOARD_H__
#define __MYINFOBOARD_H__

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class MyInfoBoard {
    int height, width;
    vector<string> infoBoard;
    
    void separatePush(string s);
public:
    MyInfoBoard(int width, int height);
    void push(string s);
    vector<string> &getInfoBoard();
};

#endif
