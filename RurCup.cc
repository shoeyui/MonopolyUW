#include "RurCup.h"

RurCup *RurCup::rc1 = 0;
RurCup *RurCup::rc2 = 0;
RurCup *RurCup::rc3 = 0;
RurCup *RurCup::rc4 = 0;
vector<RurCup*> *RurCup::cupStack = 0;

RurCup::RurCup() {
    
}

RurCup::~RurCup() {
    while (cupStack->size() != 0) {
        delete *(cupStack->begin());
    }
    
    delete cupStack;
}

RurCup *RurCup::getCup() {
    if (cupStack) {
        if (cupStack->size() > 0) {
            RurCup *result = *(cupStack->begin());
            cupStack->erase(cupStack->begin());
            return result;
        } else {
            return NULL;
        }
    } else {
        rc1 = new RurCup();
        rc2 = new RurCup();
        rc3 = new RurCup();
        rc4 = new RurCup();
        
        cupStack = new vector<RurCup*>();
        
        cupStack->push_back(rc1);
        cupStack->push_back(rc2);
        cupStack->push_back(rc3);
        cupStack->push_back(rc4);
        
        return getCup();
    }
}

void RurCup::putCup(RurCup *cup) {
    cupStack->push_back(cup);
}

int RurCup::getNumOfCups() {
    return (int) cupStack->size();
}
