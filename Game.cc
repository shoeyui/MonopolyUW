#include "Game.h"

using namespace std;

string Game::my_to_string(int i) {
    ostringstream ss;
    ss << i;
    return ss.str();
}

void clearScreen(int windowHeight);

Game::Game(bool debugMode): mib(63, 14), debugMode(debugMode) {
    // window
    struct winsize myWindowsSize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &myWindowsSize);
    myWindowWidth = myWindowsSize.ws_col;
    myWindowHeight = myWindowsSize.ws_row;
    myLeftMargin = (myWindowWidth-91)/2;
    myTopMargin = (myWindowHeight-58)/2;
    
    // gameboard
    gameboard[0] = new NonProperty("Goose Nesting", 20);
    gameboard[1] = new AcademicBuilding("EV1", 21, 220, 18, 150, 90, 250, 700, 875, 1050);
    gameboard[2] = new NonProperty("NEEDLES HALL", 22);
    gameboard[3] = new AcademicBuilding("EV2", 23, 220, 18, 150, 90, 250, 700, 875, 1050);
    gameboard[4] = new AcademicBuilding("EV3", 24, 240, 20, 150, 100, 300, 750, 925, 1100);
    gameboard[5] = new Residence("V1", 25);
    gameboard[6] = new AcademicBuilding("PHYS", 26, 260, 22, 150, 110, 330, 800, 975, 1150);
    gameboard[7] = new AcademicBuilding("B1", 27, 260, 22, 150, 110, 330, 800, 975, 1150);
    gameboard[8] = new Gym("CIF", 28);
    gameboard[9] = new AcademicBuilding("B2", 29, 280, 24, 150, 120, 360, 850, 1025, 1200);
    gameboard[10] = new NonProperty("GO TO TIMS", 30);
    gameboard[11] = new AcademicBuilding("OPT", 19, 200, 16, 100, 80, 220, 600, 800, 1000);
    gameboard[12] = new AcademicBuilding("EIT", 31, 300, 26, 200, 130, 390, 900, 1100, 1275);
    gameboard[13] = new AcademicBuilding("BMH", 18, 180, 14, 100, 70, 200, 550, 750, 950);
    gameboard[14] = new AcademicBuilding("ESC", 32, 300, 26, 200, 130, 390, 900, 1100, 1275);
    gameboard[15] = new NonProperty("SLC", 17);
    gameboard[16] = new NonProperty("SLC", 33);
    gameboard[17] = new AcademicBuilding("LHI", 16, 180, 14, 100, 70, 200, 550, 750, 950);
    gameboard[18] = new AcademicBuilding("C2", 34, 320, 28, 200, 150, 450, 1000, 1200, 1400);
    gameboard[19] = new Residence("UWP", 15);
    gameboard[20] = new Residence("REV", 35);
    gameboard[21] = new AcademicBuilding("CPH", 14, 160, 12, 100, 60, 180, 500, 700, 900);
    gameboard[22] = new NonProperty("NEEDLES HALL", 36);
    gameboard[23] = new AcademicBuilding("DWE", 13, 140, 10, 100, 50, 150, 450, 625, 750);
    gameboard[24] = new AcademicBuilding("MC", 37, 350, 35, 200, 175, 500, 1100, 1300, 1500);
    gameboard[25] = new Gym("PAC", 12);
    gameboard[26] = new NonProperty("COOP FEE", 38);
    gameboard[27] = new AcademicBuilding("RCH", 11, 140, 10, 100, 50, 150, 450, 625, 750);
    gameboard[28] = new AcademicBuilding("DC", 39, 400, 50, 200, 200, 600, 1400, 1700, 2000);
    gameboard[29] = new NonProperty("DC Tims Line", 10);
    gameboard[30] = new AcademicBuilding("HH", 9, 120, 8, 50, 40, 100, 300, 450, 600);
    gameboard[31] = new AcademicBuilding("PAS", 8, 100, 6, 50, 30, 90, 270, 400, 550);
    gameboard[32] = new NonProperty("NEEDLES HALL", 7);
    gameboard[33] = new AcademicBuilding("ECH", 6, 100, 6, 50, 30, 90, 270, 400, 550);
    gameboard[34] = new Residence("MKV", 5);
    gameboard[35] = new NonProperty("TUITION", 4);
    gameboard[36] = new AcademicBuilding("ML", 3, 60, 4, 50, 20, 60, 180, 320, 450);
    gameboard[37] = new NonProperty("SLC", 2);
    gameboard[38] = new AcademicBuilding("AL", 1, 40, 2, 50, 10, 30, 90, 160, 250);
    gameboard[39] = new NonProperty("COLLECT OSAP", 0);
    
    // pieces
    pieces['G'] = "Goose";
    pieces['B'] = "GRT bus";
    pieces['D'] = "Tim Hortons doughnut";
    pieces['P'] = "Professor";
    pieces['S'] = "Student";
    pieces['$'] = "Money";
    pieces['L'] = "Laptop";
    pieces['T'] = "Pink Tie";
    
    // welcome screen
    clearScreen(myWindowHeight);
    cout << setw((myWindowWidth+10)/2) << "Welcome to" << endl;
    cout << setw((myWindowWidth+37)/2) << " _______  _______  ________" << endl;
    cout << setw((myWindowWidth+37)/2) << "/       \\/       \\/      " << endl;
    cout << setw((myWindowWidth+37)/2) << "$$    $$ $$      $$      $$" << endl;
    cout << setw((myWindowWidth+37)/2) << "$$    $$ $$      $$      $$" << endl;
    cout << setw((myWindowWidth+37)/2) << "$$    $$ $$      $$      $$" << endl;
    cout << setw((myWindowWidth+37)/2) << "$$    $$ $$      $$      $$" << endl;
    cout << setw((myWindowWidth+37)/2) << "$$    $$ $$      $$      $$" << endl;
    cout << setw((myWindowWidth+37)/2) << "$$    $$ $$      $$      $$" << endl;
    cout << setw((myWindowWidth+37)/2) << "$$$$$$$$ $$$$$$$$$$$$$$$$$$" << endl << endl;
    if (debugMode) {
        cout << setw((myWindowWidth+10)/2) << "Debug Mode" << endl;
    }
    clearScreen((myWindowHeight-10)/2);
    
    sleep(3);
    
    // setup
    printBoard();
    while (true) {
        mib.push(string("Number of players (2-" + my_to_string(MAX_NUM_OF_PLAYERS) + "): "));
        printBoard();
        string tmpS;
        cin >> tmpS;
        istringstream ss(tmpS);
        
        if (ss >> numOfPlayers && numOfPlayers >= 2 && numOfPlayers <= MAX_NUM_OF_PLAYERS) {
            break;
        } else {
            mib.push(string("Please enter a number between 2 and " + my_to_string(MAX_NUM_OF_PLAYERS)));
        }
    }
    
    for (int i = 0; i < numOfPlayers; i++) {
        Player *p = new Player();
        mib.push(string("Player " + my_to_string(i+1) + "'s name: "));
        printBoard();
        string tmpS;
        cin >> tmpS;
        p->setName(tmpS);
        p->setNumber(i);
        p->setGame(this);
        
        while (true) {
            mib.push("Available pieces:");
            for (map<char,string>::iterator it = pieces.begin(); it != pieces.end(); it++) {
                mib.push(string(&it->first).append(" " + it->second));
            }
            mib.push(string(p->getName() + "'s piece: "));
            printBoard();
            
            char tmpC;
            cin >> tmpS;
            istringstream ss(tmpS);
            ss >> tmpC;
            
            if (pieces[tmpC] == "") {
                mib.push(string(tmpS + " is not available, please try again"));
                pieces.erase(tmpC);
                cin.clear();
                cin.ignore();
            } else {
                p->setPiece(tmpC);
                pieces.erase(tmpC);
                break;
            }
        }
        
        gameBoardArrayNumbers[0] = 38;
        gameBoardArrayNumbers[1] = 36;
        gameBoardArrayNumbers[2] = 34;
        gameBoardArrayNumbers[3] = 33;
        gameBoardArrayNumbers[4] = 31;
        gameBoardArrayNumbers[5] = 30;
        gameBoardArrayNumbers[6] = 27;
        gameBoardArrayNumbers[7] = 25;
        gameBoardArrayNumbers[8] = 23;
        gameBoardArrayNumbers[9] = 21;
        gameBoardArrayNumbers[10] = 19;
        gameBoardArrayNumbers[11] = 17;
        gameBoardArrayNumbers[12] = 13;
        gameBoardArrayNumbers[13] = 11;
        gameBoardArrayNumbers[14] = 1;
        gameBoardArrayNumbers[15] = 3;
        gameBoardArrayNumbers[16] = 4;
        gameBoardArrayNumbers[17] = 5;
        gameBoardArrayNumbers[18] = 6;
        gameBoardArrayNumbers[19] = 7;
        gameBoardArrayNumbers[20] = 8;
        gameBoardArrayNumbers[21] = 9;
        gameBoardArrayNumbers[22] = 12;
        gameBoardArrayNumbers[23] = 14;
        gameBoardArrayNumbers[24] = 18;
        gameBoardArrayNumbers[25] = 20;
        gameBoardArrayNumbers[26] = 24;
        gameBoardArrayNumbers[27] = 28;
        
        /*while (true) {
         mib.push(string("Is " + p->getName() + " a robot player? (y/n): "));
         printBoard();
         cin >> tmpS;
         if (tmpS == "y") {
         while (true) {
         mib.push("On a scale of 1 to 3, select the easiness: ");
         printBoard();
         cin >> tmpS;
         stringstream ss(tmpS);
         int easinessLv;
         if (ss >> easinessLv && easinessLv >= 1 && easinessLv <= 3) {
         // create a robot player
         break;
         } else {
         mib.push("Please enter a number from 1 to 3");
         }
         }
         break;
         } else if (tmpS == "n") {
         break;
         } else {
         mib.push("Please enter either y or n");
         }
         }*/
        
        gameboard[39]->gameGetLanders()->push_back(p);
        p->setLandsOn(gameboard[39]);
        players.push_back(p);
    }
}

Game::Game(bool debugMode, string filename): mib(63, 14), debugMode(debugMode) {
    // window
    struct winsize myWindowsSize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &myWindowsSize);
    myWindowWidth = myWindowsSize.ws_col;
    myWindowHeight = myWindowsSize.ws_row;
    myLeftMargin = (myWindowWidth-91)/2;
    myTopMargin = (myWindowHeight-58)/2;
    
    
    
    // welcome screen
    clearScreen(myWindowHeight);
    cout << setw((myWindowWidth+10)/2) << "Welcome to" << endl;
    cout << setw((myWindowWidth+37)/2) << " _______  _______  ________ __    __ " << endl;
    cout << setw((myWindowWidth+37)/2) << "/       \\/       \\/        /  |  /  |" << endl;
    cout << setw((myWindowWidth+37)/2) << "$$$$$$$  $$$$$$$  $$$$$$$$/$$ | /$$/ " << endl;
    cout << setw((myWindowWidth+37)/2) << "$$ |__$$ $$ |__$$ |   /$$/ $$ |/$$/  " << endl;
    cout << setw((myWindowWidth+37)/2) << "$$    $$<$$    $$<   /$$/  $$  $$<   " << endl;
    cout << setw((myWindowWidth+37)/2) << "$$$$$$$  $$$$$$$  | /$$/   $$$$$  \\  " << endl;
    cout << setw((myWindowWidth+37)/2) << "$$ |__$$ $$ |__$$ |/$$/    $$ |$$  \\ " << endl;
    cout << setw((myWindowWidth+37)/2) << "$$    $$/$$    $$//$$/     $$ | $$  |" << endl;
    cout << setw((myWindowWidth+37)/2) << "$$$$$$$/ $$$$$$$/ $$/      $$/   $$/ " << endl << endl;
    if (debugMode) {
        cout << setw((myWindowWidth+10)/2) << "Debug Mode" << endl;
    }
    cout << setw((myWindowWidth)/2) << "Loading from " << filename << "..." << endl;
    clearScreen((myWindowHeight-11)/2);
    
    sleep(3);
    
    // gameboard
    gameboard[0] = new NonProperty("Goose Nesting", 20);
    gameboard[1] = new AcademicBuilding("EV1", 21, 220, 18, 150, 90, 250, 700, 875, 1050);
    gameboard[2] = new NonProperty("NEEDLES HALL", 22);
    gameboard[3] = new AcademicBuilding("EV2", 23, 220, 18, 150, 90, 250, 700, 875, 1050);
    gameboard[4] = new AcademicBuilding("EV3", 24, 240, 20, 150, 100, 300, 750, 925, 1100);
    gameboard[5] = new Residence("V1", 25);
    gameboard[6] = new AcademicBuilding("PHYS", 26, 260, 22, 150, 110, 330, 800, 975, 1150);
    gameboard[7] = new AcademicBuilding("B1", 27, 260, 22, 150, 110, 330, 800, 975, 1150);
    gameboard[8] = new Gym("CIF", 28);
    gameboard[9] = new AcademicBuilding("B2", 29, 280, 24, 150, 120, 360, 850, 1025, 1200);
    gameboard[10] = new NonProperty("GO TO TIMS", 30);
    gameboard[11] = new AcademicBuilding("OPT", 19, 200, 16, 100, 80, 220, 600, 800, 1000);
    gameboard[12] = new AcademicBuilding("EIT", 31, 300, 26, 200, 130, 390, 900, 1100, 1275);
    gameboard[13] = new AcademicBuilding("BMH", 18, 180, 14, 100, 70, 200, 550, 750, 950);
    gameboard[14] = new AcademicBuilding("ESC", 32, 300, 26, 200, 130, 390, 900, 1100, 1275);
    gameboard[15] = new NonProperty("SLC", 17);
    gameboard[16] = new NonProperty("SLC", 33);
    gameboard[17] = new AcademicBuilding("LHI", 16, 180, 14, 100, 70, 200, 550, 750, 950);
    gameboard[18] = new AcademicBuilding("C2", 34, 320, 28, 200, 150, 450, 1000, 1200, 1400);
    gameboard[19] = new Residence("UWP", 15);
    gameboard[20] = new Residence("REV", 35);
    gameboard[21] = new AcademicBuilding("CPH", 14, 160, 12, 100, 60, 180, 500, 700, 900);
    gameboard[22] = new NonProperty("NEEDLES HALL", 36);
    gameboard[23] = new AcademicBuilding("DWE", 13, 140, 10, 100, 50, 150, 450, 625, 750);
    gameboard[24] = new AcademicBuilding("MC", 37, 350, 35, 200, 175, 500, 1100, 1300, 1500);
    gameboard[25] = new Gym("PAC", 12);
    gameboard[26] = new NonProperty("COOP FEE", 38);
    gameboard[27] = new AcademicBuilding("RCH", 11, 140, 10, 100, 50, 150, 450, 625, 750);
    gameboard[28] = new AcademicBuilding("DC", 39, 400, 50, 200, 200, 600, 1400, 1700, 2000);
    gameboard[29] = new NonProperty("DC Tims Line", 10);
    gameboard[30] = new AcademicBuilding("HH", 9, 120, 8, 50, 40, 100, 300, 450, 600);
    gameboard[31] = new AcademicBuilding("PAS", 8, 100, 6, 50, 30, 90, 270, 400, 550);
    gameboard[32] = new NonProperty("NEEDLES HALL", 7);
    gameboard[33] = new AcademicBuilding("ECH", 6, 100, 6, 50, 30, 90, 270, 400, 550);
    gameboard[34] = new Residence("MKV", 5);
    gameboard[35] = new NonProperty("TUITION", 4);
    gameboard[36] = new AcademicBuilding("ML", 3, 60, 4, 50, 20, 60, 180, 320, 450);
    gameboard[37] = new NonProperty("SLC", 2);
    gameboard[38] = new AcademicBuilding("AL", 1, 40, 2, 50, 10, 30, 90, 160, 250);
    gameboard[39] = new NonProperty("COLLECT OSAP", 0);
    
    // setup
    ifstream inputFile;
    inputFile.open(filename.c_str());
    
    inputFile >> numOfPlayers;
    
    for (int i = 0; i < numOfPlayers; i++) {
        Player *p = new Player();
        
        string playerName;
        inputFile >> playerName;
        p->setName(playerName);
        p->setNumber(i);
        p->setGame(this);
        
        char playerPiece;
        inputFile >> playerPiece;
        p->setPiece(playerPiece);
        pieces.erase(playerPiece);
        
        int numOfRurCups;
        inputFile >> numOfRurCups;
        for (int j = 0; j < numOfRurCups; j++) {
            p->addCup(RurCup::getCup());
        }
        
        int money;
        inputFile >> money;
        p->setCash(money);
        
        int position;
        inputFile >> position;
        if (position == 10) {
            int inJail;
            inputFile >> inJail;
            p->setInJail(inJail);
        }
        
        for (int i = 0; i < 40; i++) {
            if (gameboard[i]->getNumber() == position) {
                gameboard[i]->gameGetLanders()->push_back(p);
                p->setLandsOn(gameboard[i]);
                players.push_back(p);
                break;
            }
        }
    }
    
    gameBoardArrayNumbers[0] = 38;
    gameBoardArrayNumbers[1] = 36;
    gameBoardArrayNumbers[2] = 34;
    gameBoardArrayNumbers[3] = 33;
    gameBoardArrayNumbers[4] = 31;
    gameBoardArrayNumbers[5] = 30;
    gameBoardArrayNumbers[6] = 27;
    gameBoardArrayNumbers[7] = 25;
    gameBoardArrayNumbers[8] = 23;
    gameBoardArrayNumbers[9] = 21;
    gameBoardArrayNumbers[10] = 19;
    gameBoardArrayNumbers[11] = 17;
    gameBoardArrayNumbers[12] = 13;
    gameBoardArrayNumbers[13] = 11;
    gameBoardArrayNumbers[14] = 1;
    gameBoardArrayNumbers[15] = 3;
    gameBoardArrayNumbers[16] = 4;
    gameBoardArrayNumbers[17] = 5;
    gameBoardArrayNumbers[18] = 6;
    gameBoardArrayNumbers[19] = 7;
    gameBoardArrayNumbers[20] = 8;
    gameBoardArrayNumbers[21] = 9;
    gameBoardArrayNumbers[22] = 12;
    gameBoardArrayNumbers[23] = 14;
    gameBoardArrayNumbers[24] = 18;
    gameBoardArrayNumbers[25] = 20;
    gameBoardArrayNumbers[26] = 24;
    gameBoardArrayNumbers[27] = 28;
    
    for (int i = 0; i < 28; i++) {
        string propertyName;
        inputFile >> propertyName;
        Property *thisProperty = dynamic_cast<Property*>(gameboard[gameBoardArrayNumbers[i]]);
        thisProperty->setName(propertyName);
        
        string ownerName;
        inputFile >> ownerName;
        
        if (ownerName != "BANK") {
            Player *p;
            for (vector<Player*>::iterator it = players.begin(); it != players.end(); it++) {
                if ((*it)->getName() == ownerName) {
                    p = *it;
                    break;
                }
            }
            thisProperty->setOwner(p);
            
            p->getProperties()->push_back(thisProperty);
        }
        
        if (dynamic_cast<AcademicBuilding*>(thisProperty)) {
            int improvementLevel;
            inputFile >> improvementLevel;
            dynamic_cast<AcademicBuilding*>(thisProperty)->setImprovementLevel(improvementLevel);
        }
    }
    
    inputFile.close();
    
    for (vector<Player*>::iterator it = players.begin(); it != players.end(); it++) {
        (*it)->checkCombo();
    }
    
    mib.push("Game loaded");
}

Game::~Game() {
    for (int i = 0; i < 40; i++) {
        delete gameboard[i];
    }
}

void Game::play() {
    mib.push("Game started!");
    
    bool quit = false;
    while (players.size() != 1) {
        for (int i = 0; i < players.size(); i++) {
            players[i]->itIsMyTurn();
            if (players[i]->getQuit()) {
                quit = true;
                break;
            } else if (players.size() == 1) {
                break;
            }
        }
        if (quit) {
            break;
        }
    }
    
    if (quit) {
        clearScreen(myWindowHeight);
        cout << setw((myWindowWidth+18)/2) << right << "Thanks for playing" << endl;
        cout << setw((myWindowWidth+37)/2) << " _______  _______  ________ __    __ " << endl;
        cout << setw((myWindowWidth+37)/2) << "/       \\/       \\/        /  |  /  |" << endl;
        cout << setw((myWindowWidth+37)/2) << "$$$$$$$  $$$$$$$  $$$$$$$$/$$ | /$$/ " << endl;
        cout << setw((myWindowWidth+37)/2) << "$$ |__$$ $$ |__$$ |   /$$/ $$ |/$$/  " << endl;
        cout << setw((myWindowWidth+37)/2) << "$$    $$<$$    $$<   /$$/  $$  $$<   " << endl;
        cout << setw((myWindowWidth+37)/2) << "$$$$$$$  $$$$$$$  | /$$/   $$$$$  \\  " << endl;
        cout << setw((myWindowWidth+37)/2) << "$$ |__$$ $$ |__$$ |/$$/    $$ |$$  \\ " << endl;
        cout << setw((myWindowWidth+37)/2) << "$$    $$/$$    $$//$$/     $$ | $$  |" << endl;
        cout << setw((myWindowWidth+37)/2) << "$$$$$$$/ $$$$$$$/ $$/      $$/   $$/ " << endl << endl;
        clearScreen((myWindowHeight-10)/2);
    } else {
        
        clearScreen(myWindowHeight);
        
        Player *winner = *players.begin();
        string winningMessage = winner->getName() + " wins!";
        string winningNetWorth = winner->getName() + " 's net worth is " + my_to_string(winner->getNetWorth());
        
        cout << setw((int)(myWindowWidth+winningMessage.length())/2) << winningMessage << endl;
        cout << setw((int)(myWindowWidth+winningNetWorth.length())/2) << winningNetWorth << endl << endl;
        
        cout << setw((myWindowWidth+18)/2) << right << "Thanks for playing" << endl;
        cout << setw((myWindowWidth+37)/2) << " _______  _______  ________ __    __ " << endl;
        cout << setw((myWindowWidth+37)/2) << "/       \\/       \\/        /  |  /  |" << endl;
        cout << setw((myWindowWidth+37)/2) << "$$$$$$$  $$$$$$$  $$$$$$$$/$$ | /$$/ " << endl;
        cout << setw((myWindowWidth+37)/2) << "$$ |__$$ $$ |__$$ |   /$$/ $$ |/$$/  " << endl;
        cout << setw((myWindowWidth+37)/2) << "$$    $$<$$    $$<   /$$/  $$  $$<   " << endl;
        cout << setw((myWindowWidth+37)/2) << "$$$$$$$  $$$$$$$  | /$$/   $$$$$  \\  " << endl;
        cout << setw((myWindowWidth+37)/2) << "$$ |__$$ $$ |__$$ |/$$/    $$ |$$  \\ " << endl;
        cout << setw((myWindowWidth+37)/2) << "$$    $$/$$    $$//$$/     $$ | $$  |" << endl;
        cout << setw((myWindowWidth+37)/2) << "$$$$$$$/ $$$$$$$/ $$/      $$/   $$/ " << endl << endl;
        clearScreen((myWindowHeight-13)/2);
    }
    
}

Block **Game::getGameBoard() {
    return gameboard;
}

void Game::clearScreen(int windowHeight) {
    for (int i = 0; i < windowHeight; i++) {
        cout << endl;
    }
}

void Game::printBoard() {
    clearScreen(myWindowHeight);
    
    cout << setw(myLeftMargin+1) << "";
    for (int i = 0; i < 11; i++) {
        if (dynamic_cast<NonProperty*>(gameboard[i])) {
            for (int j = 0; j < 8; j++) {
                cout << " ";
            }
        } else {
            Property *p = dynamic_cast<Property*>(gameboard[i]);
            p->printOwnership();
        }
    }
    cout << endl;
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 11; j++) {
            gameboard[j]->print(i+1, myLeftMargin, myTopMargin, players, mib);
        }
        cout << endl;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 11; j < 13; j++) {
            gameboard[j]->print(i+1, myLeftMargin, myTopMargin, players, mib);
        }
        cout << endl;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 13; j < 15; j++) {
            gameboard[j]->print(i+1, myLeftMargin, myTopMargin, players, mib);
        }
        cout << endl;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 15; j < 17; j++) {
            gameboard[j]->print(i+1, myLeftMargin, myTopMargin, players, mib);
        }
        cout << endl;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 17; j < 19; j++) {
            gameboard[j]->print(i+1, myLeftMargin, myTopMargin, players, mib);
        }
        cout << endl;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 19; j < 21; j++) {
            gameboard[j]->print(i+1, myLeftMargin, myTopMargin, players, mib);
        }
        cout << endl;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 21; j < 23; j++) {
            gameboard[j]->print(i+1, myLeftMargin, myTopMargin, players, mib);
        }
        cout << endl;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 23; j < 25; j++) {
            gameboard[j]->print(i+1, myLeftMargin, myTopMargin, players, mib);
        }
        cout << endl;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 25; j < 27; j++) {
            gameboard[j]->print(i+1, myLeftMargin, myTopMargin, players, mib);
        }
        cout << endl;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 27; j < 29; j++) {
            gameboard[j]->print(i+1, myLeftMargin, myTopMargin, players, mib);
        }
        cout << endl;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 29; j < 40; j++) {
            gameboard[j]->print(i+1, myLeftMargin, myTopMargin, players, mib);
        }
        cout << endl;
    }
    
    cout << setw(myLeftMargin+1) << "";
    for (int i = 0; i < 11; i++) {
        cout << "|_______";
    }
    cout << "|" << endl;
    
    cout << setw(myLeftMargin+1) << "";
    for (int i = 29; i < 40; i++) {
        if (dynamic_cast<NonProperty*>(gameboard[i])) {
            for (int j = 0; j < 8; j++) {
                cout << " ";
            }
        } else {
            Property *p = dynamic_cast<Property*>(gameboard[i]);
            p->printOwnership();
        }
    }
    cout << endl;
    
    clearScreen(myTopMargin);
    
    mib.push("");
}

void Game::printHelp() {
    clearScreen(myWindowHeight);
    
    cout << setw((myWindowWidth+16)/2) << right << "LIST OF COMMANDS" << endl << endl;
    
    int leftMargin = (myWindowWidth - 16) / 2 - 37;
    
    cout << setw(leftMargin) << "" << left << "Single Player Action" << endl;
    if (debugMode) {
        cout << setw(leftMargin) << "" << left << "    roll (<dice1> <dice2>)            Roll two dice randomly or specified by <dice1> and <dice2>" << endl;
    } else {
        cout << setw(leftMargin) << "" << left << "    roll                              Roll two dice" << endl;
    }
    
    cout << setw(leftMargin) << "" << left << "    next                              End your turn" << endl;
    cout << setw(leftMargin) << "" << left << "    assets (<piece>)                  Display the assets of <piece> or the current player if <piece> is not specified" << endl;
    cout << setw(leftMargin) << "" << left << "    leave <cash/cup>                  Leave DC Tims Line by either paying $50 or using a Roll Up the Rim cup" << endl;
    cout << setw(leftMargin) << "" << left << "    bankrupt                          Declare bankruptcy" << endl << endl;
    
    cout << setw(leftMargin) << "" << left << "Property Action" << endl;
    cout << setw(leftMargin) << "" << left << "    improve <property> <buy/sell>     <buy> or <sell> an improvement of <property>" << endl;
    cout << setw(leftMargin) << "" << left << "    mortgage <property>               Mortgage <property>" << endl;
    cout << setw(leftMargin) << "" << left << "    unmortgage <property>             Unmortgage <property>" << endl << endl;
    
    cout << setw(leftMargin) << "" << left << "Multi-Player Action" << endl;
    cout << setw(leftMargin) << "" << left << "    trade <piece> <give> <receive>    Offer a trade to <piece> by offering <give> and requesting <receive>" << endl << endl;
    
    cout << setw(leftMargin) << "" << left << "Game Action" << endl;
    cout << setw(leftMargin) << "" << left << "    save <filename>                   Save the current state of the game to <filename>" << endl;
    cout << setw(leftMargin) << "" << left << "    quit                              Quit the game without saving" << endl;
    
    clearScreen((myWindowHeight-20)/2);
}

MyInfoBoard &Game::getMIB() {
    return mib;
}

bool Game::getDebugMode() {
    return debugMode;
}

vector<Player*> *Game::getPlayers() {
    return &players;
}

int *Game::getGameBoardArrayNumbers() {
    return gameBoardArrayNumbers;
}
