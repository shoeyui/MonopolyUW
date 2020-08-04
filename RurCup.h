#ifndef __RURCUP_H__
#define __RURCUP_H__

#include <iostream>
#include "sstream"
#include <vector>

using namespace std;

class RurCup {
    static RurCup *rc1;
    static RurCup *rc2;
    static RurCup *rc3;
    static RurCup *rc4;
    
    static vector<RurCup*> *cupStack;
    
    RurCup();
    ~RurCup();
public:
    static RurCup *getCup();
    static void putCup(RurCup *cup);
    static int getNumOfCups();
};

#endif
