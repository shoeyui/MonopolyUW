#include "MyInfoBoard.h"

MyInfoBoard::MyInfoBoard(int width, int height): width(width), height(height) {
    
}

void MyInfoBoard::separatePush(string s) {
    stringstream ss(s);
    string line, word;

    ss >> line;
    while (ss >> word) {
        if (line.length() + word.length() + 1 > width) {
            push(line);
            line = "    " + word;
        } else {
            line += " " + word;
        }
    }
    push(line);
}

void MyInfoBoard::push(string s) {
    if (s.length() > width) {
        separatePush(s);
    } else {
        if (infoBoard.end() - infoBoard.begin() >= height) {
            infoBoard.erase(infoBoard.begin());
        }
        infoBoard.push_back(s);
    }
}

vector<string> &MyInfoBoard::getInfoBoard() {
    return infoBoard;
}


