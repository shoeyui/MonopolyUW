#include "Property.h"
#include "Player.h"
#include "Game.h"

Property::Property(string name, int number, int purchaseCost): Block(name, number), purchaseCost(purchaseCost), combo(false), mortgaged(false) {
    
}

string Property::my_to_string(int i) {
    ostringstream ss;
    ss << i;
    return ss.str();
}

void Property::setOwner(Player *p) {
    owner = p;
}

Player *Property::getOwner() {
    return owner;
}

int Property::getPurchaseCost() {
    return purchaseCost;
}

void Property::setCombo(bool combo) {
    this->combo = combo;
}

bool Property::getCombo() {
    return combo;
}

void Property::printOwnership() {
    if ((number >= 0 && number <= 10) || (number >= 20 && number <= 30)) {
        if (owner) {
            if (mortgaged) {
                cout << "  " << owner->getColour(COLOUR_TYPE_BACKGROUND) << "M M M" << COLOUR_DEFAULT_BACKGROUND << " ";
            } else if (combo) {
                cout << "  " << owner->getColour(COLOUR_TYPE_BACKGROUND) << "* * *" << COLOUR_DEFAULT_BACKGROUND << " ";
            } else {
                cout << "  " << owner->getColour(COLOUR_TYPE_BACKGROUND) << "     " << COLOUR_DEFAULT_BACKGROUND << " ";
            }
        } else {
            cout << setw(8) << "";
        }
    }
}

void Property::setMortgaged(bool mortgaged) {
    this->mortgaged = mortgaged;
}

bool Property::getMortgaged() {
    return mortgaged;
}

void Property::holdAuction(Game *game, vector<Player*> *bidders, int startingFrom) {
    for (vector<Player*>::iterator it = bidders->begin(); it != bidders->end(); it++) {
        (*it)->setForfeited(false);
    }
    int numberOfBidders = (int) bidders->size();
    
    bool firstRound = true;
    
    Player *highestBidder = NULL;
    int highestBid = 0;
    
    game->getMIB().push(string("Auctioning " + name));
    game->printBoard();
    
    while (numberOfBidders > 1) {
        for (vector<Player*>::iterator it = (firstRound? (bidders->begin() + startingFrom): bidders->begin()); it != bidders->end(); it++) {
            firstRound = false;
            if (!(*it)->getForfeited()) {
                while (true) {
                    game->getMIB().push(string("Highest bid: " + my_to_string(highestBid)));
                    game->getMIB().push(string("What would " + (*it)->getName() + " do (bid <amount>/pass/forfeit):"));
                    game->printBoard();
                    
                    string tmpS;
                    cin >> tmpS;
                    if (tmpS == "bid") {
                        int amount;
                        if (cin >> amount) {
                            if ((*it)->getCash() < amount) {
                                (*it)->noEnoughCash();
                            } else if (amount > highestBid) {
                                highestBid = amount;
                                highestBidder = *it;
                                
                                game->getMIB().push(string((*it)->getName() + " bid $ " + my_to_string(amount)));
                                break;
                            } else {
                                game->getMIB().push("Please enter a number that is higher than the highest bid");
                            }
                        } else {
                            cin.clear();
                            cin.ignore();
                            game->getMIB().push("Please enter a number");
                        }
                    } else if (tmpS == "pass") {
                        game->getMIB().push(string((*it)->getName() + " passed"));
                        game->printBoard();
                        break;
                    } else if (tmpS == "forfeit") {
                        game->getMIB().push(string((*it)->getName() + " forfeited"));
                        game->printBoard();
                        
                        (*it)->setForfeited(true);
                        numberOfBidders--;
                        break;
                    } else {
                        game->getMIB().push("Unknown command");
                        game->printBoard();
                    }
                }
                
                if (numberOfBidders == 1) {
                    break;
                }
            }
        }
    }
    
    if (highestBidder) {
        highestBidder->addCash(-highestBid);
        owner = highestBidder;
        highestBidder->getProperties()->push_back(this);
        game->getMIB().push(string(highestBidder->getName() + " bought " + name));
        highestBidder->checkCombo();
        game->printBoard();
    } else {
        game->getMIB().push(string("Auction of " + name + " failed"));
        game->printBoard();
    }
}
