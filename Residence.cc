#include "Residence.h"
#include "Player.h"

Residence::Residence(string name, int number): Property(name, number, 200) {
    
}

int Residence::getTuition(int steps = 0) {
    if (combo) {
        return 200;
    }
    
    int numberOfResidenceOwnerOwned  = 0;
    for (vector<Property*>::iterator it = owner->getProperties()->begin(); it != owner->getProperties()->end(); it++) {
        if (dynamic_cast<Residence*>(*it)) {
            numberOfResidenceOwnerOwned++;
        }
    }
    
    switch (numberOfResidenceOwnerOwned) {
        case 1:
            return 25;
        case 2:
            return 50;
        default:
            return 100;
    }
}

void Residence::print(int lineNum, int leftMargin, int topMargin, vector<Player*> players, MyInfoBoard &mib) {
    if (number >= 10 && number <= 20) {
        cout << setw(leftMargin) << "";
    }
    
    if (number == 15) {
        if (lineNum >= 3 && lineNum <= 5 && owner) {
            if (mortgaged) {
                cout << owner->getColour(COLOUR_TYPE_BACKGROUND) << "M" << COLOUR_DEFAULT_BACKGROUND;
            } else if (combo) {
                cout << owner->getColour(COLOUR_TYPE_BACKGROUND) << "*" << COLOUR_DEFAULT_BACKGROUND;
            } else {
                cout << owner->getColour(COLOUR_TYPE_BACKGROUND) << " " << COLOUR_DEFAULT_BACKGROUND;
            }
        } else {
            cout << " ";
        }
    };
    
    switch (lineNum) {
        case 1: {
            if (number == 15) {
                bar7bar14();
                cout << "|  $$$$$$$  $$$$$$$  $$$$$$$$/$$ | /$$/   |";
                repeat(" ", 14);
            } else if (number == 35) {
                bar7();
            } else {
                repeat("_", 8);
            }
            
            break;
        }
        case 2: {
            cout << "|" << setw(7) << left << name;
            if (number == 15) {
                bar14();
                cout << "|  $$ |__$$ $$ |__$$ |   /$$/ $$ |/$$/    |";
                repeat(" ", 14);
            }
            break;
        }
        case 3: {
            cout << "|";
            repeat(" ", 7);
            if (number == 15) {
                bar14();
                cout << "|  $$    $$<$$    $$<   /$$/  $$  $$<     |";
                repeat(" ", 14);
            }
            break;
        }
        case 4: {
            cout << setw(8) << left << "|";
            if (number == 15) {
                bar14();
                cout << "|  $$$$$$$  $$$$$$$  | /$$/   $$$$$  \\    |";
                repeat(" ", 14);
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
            if (number == 15) {
                bar14();
                cout << "|  $$ |__$$ $$ |__$$ |/$$/    $$ |$$  \\   |";
                repeat(" ", 14);
            }
            break;
        }
    }
    
    if (number == 35) {
        cout << "|";
        if (lineNum >= 3 && lineNum <= 5 && owner) {
            if (mortgaged) {
                cout << owner->getColour(COLOUR_TYPE_BACKGROUND) << "M" << COLOUR_DEFAULT_BACKGROUND;
            } else if (combo) {
                cout << owner->getColour(COLOUR_TYPE_BACKGROUND) << "*" << COLOUR_DEFAULT_BACKGROUND;
            } else {
                cout << owner->getColour(COLOUR_TYPE_BACKGROUND) << " " << COLOUR_DEFAULT_BACKGROUND;
            }
        } else {
            cout << " ";
        }
    }
    
}
