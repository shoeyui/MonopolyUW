#include "NonProperty.h"
#include "Game.h"
#include "RurCup.h"

NonProperty::NonProperty(string name, int number): Block(name, number) {
    
}

string NonProperty::my_to_string(int i) {
    ostringstream ss;
    ss << i;
    return ss.str();
}

bool goToTimsLine(Game *game, Player *p) {
    game->getMIB().push(string(p->getName() + " has to go to DC Tims Line"));
    game->printBoard();
    
    game->getGameBoard()[29]->addLander(p);
    p->setInJail(1);
    
    return true;
}

bool inRangeOf(int number, int lowerBound, int upperBound) {
    return (number >= lowerBound && number <= upperBound);
}

void grantRurCup(Game *game, Player *p) {
    p->addCup(RurCup::getCup());
    
    game->getMIB().push(string(p->getName() + " received a Roll Up the Rim Cup!"));
    game->printBoard();
}

bool NonProperty::effect(Game *game, Player *p) {
    if (name == "SLC") {
        int randomNum = rand() % 100;
        if (randomNum == 0 && RurCup::getNumOfCups() > 0) { // 1%
            grantRurCup(game, p);
        } else {
            
            
            randomNum = rand() % 24 + 1;
            if (inRangeOf(randomNum, 1, 3)) { // back 3
                p->movePlayer(-3);
            } else if (inRangeOf(randomNum, 4, 7)) { // back 2
                p->movePlayer(-2);
            } else if (inRangeOf(randomNum, 8, 11)) { // back 1
                p->movePlayer(-1);
            } else if (inRangeOf(randomNum, 12, 14)) { // forward 1
                p->movePlayer(1);
            } else if (inRangeOf(randomNum, 15, 18)) { // forward 2
                p->movePlayer(2);
            } else if (inRangeOf(randomNum, 19, 22)) { // forward 3
                p->movePlayer(3);
            } else if (randomNum == 23) { // DC Tims Line
                return goToTimsLine(game, p);
            } else { // OSAP
                game->getMIB().push(string(p->getName() + " advanced to COLLECT OSAP"));
                game->getMIB().push(string(p->getName() + " collected OSAP"));
                p->addCash(OSAP_AMOUNT);
                game->printBoard();
                
                game->getGameBoard()[39]->addLander(p);
            }
        }
    } else if (name == "TUITION") {
        while (true) {
            game->getMIB().push(string(p->getName() + " has to pay either $300 or 10% of total worth ($" + my_to_string((int)(p->getNetWorth() * 0.1)) + ") (300/worth):"));
            game->printBoard();
            
            string tmpS;
            cin >> tmpS;
            if (tmpS == "300") {
                p->addCash(-300);
                
                game->getMIB().push(string(p->getName() + " paid $300 of tuition"));
                game->printBoard();
                break;
            } else if (tmpS == "worth") {
                int payment = -(int)(p->getNetWorth() * 0.1);
                p->addCash(payment);
                
                game->getMIB().push(string(p->getName() + " paid 10% of total worth ($" + my_to_string(-payment) + ") of tuition"));
                game->printBoard();
                break;
            } else {
                cin.clear();
                cin.ignore();
                game->getMIB().push("Please enter either 300 or worth");
            }
        }
    } else if (name == "NEEDLES HALL") {
        int randomNum = rand() % 100;
        if (randomNum == 0 && RurCup::getNumOfCups() > 0) { // 1%
            grantRurCup(game, p);
        } else {
            randomNum = rand() % 18 + 1;
            if (randomNum == 1) { // -200
                p->addCash(-200);
                
                game->getMIB().push(string(p->getName() + " lost $200"));
            } else if (inRangeOf(randomNum, 2, 3)) { // -100
                p->addCash(-100);
                
                game->getMIB().push(string(p->getName() + " lost $100"));
            } else if (inRangeOf(randomNum, 4, 6)) { // -50
                p->addCash(-50);
                
                game->getMIB().push(string(p->getName() + " lost $50"));
            } else if (inRangeOf(randomNum, 7, 12)) { // 25
                p->addCash(25);
                
                game->getMIB().push(string(p->getName() + " received $25"));
            } else if (inRangeOf(randomNum, 13, 15)) { // 50
                p->addCash(50);
                
                game->getMIB().push(string(p->getName() + " received $50"));
            } else if (inRangeOf(randomNum, 16, 17)) { // 100
                p->addCash(100);
                
                game->getMIB().push(string(p->getName() + " received $100"));
            } else { // 200
                p->addCash(200);
                
                game->getMIB().push(string(p->getName() + " received $200"));
            }
            game->printBoard();
        }
    } else if (name == "GO TO TIMS") {
        return goToTimsLine(game, p);
    } else if (name == "COOP FEE") {
        p->addCash(-150);
        
        game->getMIB().push(string(p->getName() + " paid $150 of co-op fee"));
        game->printBoard();
    }
    return false;
}
