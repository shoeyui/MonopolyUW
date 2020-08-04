#include <iostream>
#include <cstring>
#include "Game.h"

using namespace std;

int main(int argc, char **argv) {
    srand((unsigned int)time(NULL));
    
    Game *game;
    
    bool testing = false;
    bool readFromFile = false;
    string fileName = "";
    
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-testing") == 0) {
            testing = true;
        } else if (strcmp(argv[i], "-load") == 0) {
            readFromFile = true;
        } else if (readFromFile && fileName == "") {
            fileName = argv[i];
        }
    }
    
    if (readFromFile) {
        game = new Game(testing, fileName);
    } else {
        game = new Game(testing);
    }
    
    game->play();
    
    delete game;
}
