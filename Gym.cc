#include "Gym.h"
#include "Player.h"

Gym::Gym(string name, int number): Property(name, number, 150) {
    
}

int Gym::getTuition(int steps = 0) {
    if (combo) {
        return steps * 10;
    } else {
        return steps * 4;
    }
}

void Gym::print(int lineNum, int leftMargin, int topMargin, vector<Player*> players, MyInfoBoard &mib) {
    if (number >= 10 && number <= 20) {
        cout << setw(leftMargin) << "";
    }
    
    if (number == 12) {
        if (lineNum >= 3 && lineNum <= 5 && owner) {
            if (mortgaged) {
                cout << owner->getColour(COLOUR_TYPE_BACKGROUND) << "*" << COLOUR_DEFAULT_BACKGROUND;
            } else if (combo) {
                cout << owner->getColour(COLOUR_TYPE_BACKGROUND) << "*" << COLOUR_DEFAULT_BACKGROUND;
            } else {
                cout << owner->getColour(COLOUR_TYPE_BACKGROUND) << " " << COLOUR_DEFAULT_BACKGROUND;
            }
        } else {
            cout << " ";
        }
    }
    
    switch (lineNum) {
        case 1: {
            if (number == 12) {
                if (mib.getInfoBoard().size() > 5) {
                    bar7();
                    cout << "|";
                    repeat(" ", 4);
                    cout << setw(67) << mib.getInfoBoard().at(5);
                } else {
                    bar7bar71();
                }
            } else {
                repeat("_", 8);
            }
            
            break;
        }
        case 2: {
            cout << "|" << setw(7) << left << name;
            if (number == 12) {
                if (mib.getInfoBoard().size() > 6) {
                    cout << "|";
                    repeat(" ", 4);
                    cout << setw(67) << mib.getInfoBoard().at(6);
                } else {
                    bar71();
                }
            }
            break;
        }
        case 3: {
            cout << "|";
            repeat(" ", 7);
            if (number == 12) {
                if (mib.getInfoBoard().size() > 7) {
                    cout << "|";
                    repeat(" ", 4);
                    cout << setw(67) << mib.getInfoBoard().at(7);
                } else {
                    bar71();
                }
            }
            break;
        }
        case 4: {
            cout << setw(8) << left << "|";
            if (number == 12) {
                if (mib.getInfoBoard().size() > 8) {
                    cout << "|";
                    repeat(" ", 4);
                    cout << setw(67) << mib.getInfoBoard().at(8);
                } else {
                    bar71();
                }
            }
            break;
        }
        case 5: {
            string s = "";
            int count = 0;
            for (vector<Player*>::iterator it = landers.begin(); it != landers.end(); it++) {
                count++;
                s.append((*it)->getColour(COLOUR_TYPE_FOREGROUND));
                if ((*it)->getMyTurn()) {
                    s.append(STYLE_BLINK);
                }
                s.append(string(1, (*it)->getPiece()));
                s.append(STYLE_DEFAULT);
            }
            
            cout << "|" << s << COLOUR_DEFAULT_FOREGROUND;
            repeat(" ", 7-count);
            if (number == 12) {
                if (mib.getInfoBoard().size() > 9) {
                    cout << "|";
                    repeat(" ", 4);
                    cout << setw(67) << mib.getInfoBoard().at(9);
                } else {
                    bar71();
                }
            }
            break;
        }
    }
    
}
