#include "Player.h"
#include "Game.h"

using namespace std;

string Player::my_to_string(int i) {
    ostringstream ss;
    ss << i;
    return ss.str();
}

void Player::itIsMyTurn() {
    this->myTurn = true;
    
    rollingTime = 1;
    doubleCount = 0;
    
    game->getMIB().push(string(name + "'s turn"));
    
    string tmp;
    while (true) {
        game->getMIB().push(string("What would " + name + " like to do (type help for the list of commands):"));
        game->printBoard();
        
        cin >> tmp;
        if (tmp == "help") {
            game->printHelp();
            while (true) {
                cin >> tmp;
                if (tmp == "quit") {
                    break;
                } else {
                    game->printHelp();
                    cout << "Type quit to quit help";
                }
            }
        } else if (tmp == "roll") {
            getline(cin, tmp);
            
            if (game->getDebugMode() && tmp != "") {
                stringstream ss(tmp);
                int firstDice, secondDice;
                if (ss >> firstDice >> secondDice) {
                    if (roll(firstDice, secondDice)) {
                        next();
                        break;
                    }
                } else {
                    game->getMIB().push("Invalid arguments");
                    game->printBoard();
                }
            } else {
                if (roll()) {
                    next();
                    break;
                }
            }
        } else if (tmp == "next") {
            if (next()) {
                break;
            }
        } else if (tmp == "assets") {
            getline(cin, tmp);
            if (tmp == "") {
                assets();
            } else {
                stringstream ss(tmp);
                char playerPiece;
                ss >> playerPiece;
                
                for (vector<Player*>::iterator it = game->getPlayers()->begin(); it != game->getPlayers()->end(); it++) {
                    if ((*it)->getPiece() == playerPiece) {
                        (*it)->assets();
                        break;
                    }
                }
            }
        } else if (tmp == "leave") {
            getline(cin, tmp);
            stringstream ss(tmp);
            ss >> tmp;
            leaveTimsLine(tmp);
        } else if (tmp == "bankrupt") {
            bankrupt();
        } else if (tmp == "improve") {
            getline(cin, tmp);
            stringstream ss(tmp);
            string improveAbS, buyOrSell;
            ss >> improveAbS >> buyOrSell;
            
            if (buyOrSell != "buy" && buyOrSell != "sale") {
                game->getMIB().push("Invalid arguments");
            } else {
                improve(improveAbS, buyOrSell);
            }
        } else if (tmp == "mortgage") {
            getline(cin, tmp);
            stringstream ss(tmp);
            ss >> tmp;
            if (tmp == "") {
                game->getMIB().push("Invalid arguments");
            } else {
                mortgage(tmp);
            }
        } else if (tmp == "unmortgage") {
            getline(cin, tmp);
            stringstream ss(tmp);
            ss >> tmp;
            if (tmp == "") {
                game->getMIB().push("Invalid arguments");
            } else {
                unmortgage(tmp);
            }
        } else if (tmp == "trade") {
            getline(cin, tmp);
            stringstream ss(tmp);
            
            char tradeWith;
            ss >> tradeWith;
            
            vector<string> propertyNames;
            
            while (ss >> tmp) {
                propertyNames.push_back(tmp);
            }
            
            trade(tradeWith, propertyNames);
        } else if (tmp == "save") {
            getline(cin, tmp);
            stringstream ss(tmp);
            
            string filename;
            ss >> filename;
            
            ofstream outputFile;
            outputFile.open(filename.c_str());
            
            outputFile << game->getPlayers()->size() << endl;
            for (vector<Player*>::iterator it = game->getPlayers()->begin(); it != game->getPlayers()->end(); it++) {
                if ((*it)->getNumber() > number) {
                    outputFile << (*it)->getName() << " " << (*it)->getPiece() << " " << (*it)->getRurCups()->size() << " " << (*it)->getCash() << " " << (*it)->getLandsOn()->getNumber() << ((*it)->getLandsOn()->getNumber() == 10? string(" " + my_to_string((*it)->getInJail())): "") << endl;
                }
            }
            for (vector<Player*>::iterator it = game->getPlayers()->begin(); it != game->getPlayers()->end(); it++) {
                if ((*it)->getNumber() <= number) {
                    outputFile << (*it)->getName() << " " << (*it)->getPiece() << " " << (*it)->getRurCups()->size() << " " << (*it)->getCash() << " " << (*it)->getLandsOn()->getNumber() << ((*it)->getLandsOn()->getNumber() == 10? string(" " + my_to_string((*it)->getInJail())): "") << endl;
                    if ((*it)->getNumber() == number) {
                        break;
                    }
                }
            }
            
            int *gameBoardArrayNumbers = game->getGameBoardArrayNumbers();
            for (int i = 0; i < 28; i++) {
                Property *thisProperty = dynamic_cast<Property*>(game->getGameBoard()[gameBoardArrayNumbers[i]]);
                outputFile << thisProperty->getName() << " " << (thisProperty->getOwner()? thisProperty->getOwner()->getName(): "BANK") << (dynamic_cast<AcademicBuilding*>(thisProperty)? string(" " + my_to_string(dynamic_cast<AcademicBuilding*>(thisProperty)->getImprovementLevel())): "") << endl;
            }
            
            outputFile.close();
            game->getMIB().push("Game Saved");
            game->printBoard();
            
        } else if (tmp == "quit") {
            quit = true;
            break;
        } else {
            game->getMIB().push("Unknown command");
        }
    }
}

bool Player::getMyTurn() {
    return myTurn;
}

bool Player::roll(int firstDice, int secondDice) {
    if (rollingTime != 0) {
        rollingTime = 0;
        int sum;
        
        if (firstDice == 0) {
            firstDice = rollDice();
            secondDice = rollDice();
        }
        sum = firstDice + secondDice;
        
        game->getMIB().push(string(name + " rolled " + my_to_string(firstDice) + " and " + my_to_string(secondDice)));
        game->printBoard();
        
        if (firstDice == secondDice) {
            doubleCount++;
            
            if (doubleCount == 3){
                game->getMIB().push(string("Three Doubles... " + name + " has to go to DC Tims Line"));
                game->printBoard();
                
                game->getGameBoard()[29]->addLander(this);
                inJail = 1;
                
                return true;
            } else {
                rollingTime = 1;
                if (inJail) {
                    getOutOfJail();
                    rollingTime = 0;
                    return movePlayer(sum);
                } else {
                    game->getMIB().push(string("Double! " + name + " has one more chance to roll"));
                    game->printBoard();
                    return movePlayer(sum);
                }
            }
        } else if (inJail) {
            inJail++;
            if (inJail == 4) {
                game->getMIB().push(string("Failed to roll a double, " + name + " has to pay or use a Roll Up the Rim cup to leave DC Tims Line"));
            } else {
                game->getMIB().push(string("Failed to roll a double, " + name + " cannot leave DC Tims Line"));
            }
            game->printBoard();
        } else {
            return movePlayer(sum);
        }
    } else {
        game->getMIB().push(string(name + " doesn't have any chance to roll"));
        game->printBoard();
    }
    
    return false;
}

bool Player::next() {
    if (rollingTime != 0) {
        game->getMIB().push(string(name + " still has one chance to roll"));
        game->printBoard();
    } else if (cash < 0) {
        game->getMIB().push(string(name + " doesn't have enough cash to continue the game"));
        game->printBoard();
    } else if (inJail == 4) {
        game->getMIB().push(string(name + " has to pay or use a Roll Up the Rim cup to leave DC Tims Line"));
        game->printBoard();
    } else {
        myTurn = false;
        
        renter = NULL;
        owing = 0;
        
        return true;
    }
    return false;
}

void Player::getOutOfJail() {
    inJail = 0;
    game->getMIB().push(string(name + " got out of DC Tims Line"));
    game->printBoard();
}

bool Player::movePlayer(int steps) {
    int newPosition = landsOn->getNumber() + steps;
    
    if (newPosition >= 40) {
        game->getMIB().push(string(name + " collected OSAP"));
        cash += OSAP_AMOUNT;
        game->printBoard();
    } else if (newPosition < 0) {
        newPosition += 40;
    }
    
    newPosition = newPosition%40;
    
    Block *newBlock;
    for (int i = 0; i < 40; i++) {
        if (game->getGameBoard()[i]->getNumber() == newPosition) {
            newBlock = game->getGameBoard()[i];
            break;
        }
    }
    
    newBlock->addLander(this);
    game->getMIB().push(string(name + " moved " + my_to_string(abs(steps)) + " step" + (abs(steps) > 1? "s": "") + (steps > 0? " forward": " backward") + " and landed on " + landsOn->getName()));
    game->printBoard();
    
    if (dynamic_cast<Property*>(newBlock)) {
        Property *prop = dynamic_cast<Property*>(newBlock);
        
        if (prop->getOwner() && prop->getOwner() != this) {
            if (prop->getMortgaged()) {
                game->getMIB().push(string(prop->getName() + " is mortaged, " + name + " doesn't have to pay tuition"));
                game->printBoard();
            } else {
                int tuition = prop->getTuition(steps);
                
                if (tuition > cash) {
                    renter = prop->getOwner();
                    owing = tuition - cash;
                }
                
                cash -= tuition;
                prop->getOwner()->addCash(tuition);
                
                game->getMIB().push(string(name + " paied $" + my_to_string(tuition) + " of tuition to " + prop->getOwner()->getName()));
                game->printBoard();
            }
        } else if (prop->getOwner() == NULL) {
            while (true) {
                game->getMIB().push(string(prop->getName() + " is unowned, does " + name + " want to buy it for $" + my_to_string(prop->getPurchaseCost()) + "? (y/n):"));
                game->printBoard();
                string tmpS;
                cin >> tmpS;
                if (tmpS == "y") {
                    if (cash >= prop->getPurchaseCost()) {
                        cash -= prop->getPurchaseCost();
                        prop->setOwner(this);
                        properties.push_back(prop);
                        
                        game->getMIB().push(string(name + " bought " + prop->getName()));
                        checkCombo();
                        game->printBoard();
                        break;
                    } else {
                        noEnoughCash();
                    }
                } else if (tmpS == "n") {
                    vector<Player*>::iterator it;
                    for (it = game->getPlayers()->begin(); it != game->getPlayers()->end(); it++) {
                        if (*it == this) {
                            break;
                        }
                    }
                    int startingFrom = (int) (it - game->getPlayers()->begin()+1)%game->getPlayers()->size();
                    prop->holdAuction(game, game->getPlayers(), startingFrom);
                    break;
                } else {
                    game->getMIB().push("Please enter either y or n");
                    game->printBoard();
                }
            }
        }
    } else {
        return dynamic_cast<NonProperty*>(newBlock)->effect(game, this);
    }
    
    return false;
}

void Player::assets() {
    game->getMIB().push(string("Assets of " + name + ":"));
    game->getMIB().push(string("Cash: $" + my_to_string(cash)));
    
    string propertyList = "Properties: ";
    if (properties.size() > 0) {
        for (vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++) {
            propertyList.append(string((*it)->getName() + ((*it)->getMortgaged()? "<M>": "") + " "));
        }
    } else {
        propertyList.append("None");
    }
    game->getMIB().push(propertyList);
    
    game->getMIB().push(string("Roll Up the Rim Cups: " + my_to_string(rurCups.size())));
    
    game->printBoard();
}

void Player::leaveTimsLine(string payment) {
    if (inJail) {
        if (payment == "cup") {
            if (rurCups.size() > 0) {
                RurCup *myCup = *(rurCups.begin());
                rurCups.erase(rurCups.begin());
                RurCup::putCup(myCup);
                
                game->getMIB().push(string(name + " lost one Roll Up the Rim Cup"));
                getOutOfJail();
            } else {
                game->getMIB().push(string(name + " doesn't have any Roll Up the Rim Cup"));
                game->printBoard();
            }
        } else if (payment == "cash") {
            if (cash >= 50) {
                cash -= 50;
                game->getMIB().push(string(name + " lost $50"));
                getOutOfJail();
            } else {
                noEnoughCash();
            }
        } else {
            game->getMIB().push("Invalid arguments");
            game->printBoard();
        }
    } else {
        game->getMIB().push(string(name + " is not in DC Tims Line"));
        game->printBoard();
    }
}

void Player::bankrupt() {
    if (getNetWorth() >= 0) {
        game->getMIB().push(string(name + " is still able to continue the game"));
        game->printBoard();
    } else {
        for (vector<Player*>::iterator it = game->getPlayers()->begin(); it != game->getPlayers()->end(); it++) {
            if ((*it)->getPiece() == piece) {
                game->getPlayers()->erase(it);
                break;
            }
        }
        
        game->getMIB().push(string(name + " declared bankruptcy"));
        
        if (renter) {
            renter->addCash(-owing);
            string propertiesTransfered = renter->getName() + " receives: ";
            for (vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++) {
                renter->addProperty(*it);
                propertiesTransfered.append(string((*it)->getName() + ((*it)->getMortgaged()? "<M>": "") + " "));
            }
            game->getMIB().push(propertiesTransfered);
            game->printBoard();
        } else {
            game->getMIB().push(string(name + "'s properties will be auctioned"));
            game->printBoard();
            
            for (vector<Property*>::iterator it1 = properties.begin(); it1 != properties.end(); it1++) {
                vector<Player*>::iterator it2;
                for (it2 = game->getPlayers()->begin(); it2 != game->getPlayers()->end(); it2++) {
                    if (*it2 == this) {
                        break;
                    }
                }
                int startingFrom = (int) (it2 - game->getPlayers()->begin()+1)%game->getPlayers()->size();
                (*it1)->holdAuction(game, game->getPlayers(), startingFrom);
            }
        }
    }
}

void Player::improve(string improveAbS, string buyOrSell) {
    AcademicBuilding* improveAb = NULL;
    for (vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++) {
        if ((*it)->getName() == improveAbS) {
            improveAb = dynamic_cast<AcademicBuilding*>(*it);
            break;
        }
    }
    
    if (!improveAb) {
        game->getMIB().push(string(name + " doesn't own an academic building called " + improveAbS));
    } else if (!improveAb->getCombo()){
        game->getMIB().push(string(name + " must form a monopoly in order to improve"));
    } else {
        if (buyOrSell == "buy") {
            improveAb->improve(true, game);
        } else {
            improveAb->improve(false, game);
        }
    }
}

void Player::mortgage(string propertyName) {
    Property* mortgageP = NULL;
    for (vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++) {
        if ((*it)->getName() == propertyName) {
            mortgageP = *it;
            break;
        }
    }
    
    if (!mortgageP) {
        game->getMIB().push(string(name + " doesn't own a property called " + propertyName));
    } else if (mortgageP->getMortgaged()){
        game->getMIB().push(string(propertyName + " has already been mortgaged"));
    } else if ((dynamic_cast<AcademicBuilding*>(mortgageP)) && !(dynamic_cast<AcademicBuilding*>(mortgageP)->monopolyImprovementsAreClear(game->getGameBoard()))) {
        game->getMIB().push("All improvements of properties within the monopoly have to be sold before mortgaging");
    } else {
        mortgageP->setMortgaged(true);
        int loan = (int) (mortgageP->getPurchaseCost() / 2.0);
        cash += loan;
        
        game->getMIB().push(string(name + " mortgaged " + propertyName + " and received $" + my_to_string(loan)));
        game->printBoard();
    }
}

void Player::unmortgage(string propertyName) {
    Property* mortgageP = NULL;
    for (vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++) {
        if ((*it)->getName() == propertyName) {
            mortgageP = *it;
            break;
        }
    }
    
    if (!mortgageP) {
        game->getMIB().push(string(name + " doesn't own a property called " + propertyName));
    } else if (!mortgageP->getMortgaged()){
        game->getMIB().push(string(propertyName + " has not been mortgaged yet"));
    } else {
        int loan = (int) (mortgageP->getPurchaseCost() / 2.0 * 1.1);
        
        if (cash < loan) {
            noEnoughCash();
        } else {
            cash -= loan;
            mortgageP->setMortgaged(false);
            game->getMIB().push(string(name + " paid $" + my_to_string(loan) + " and unmortgaged " + propertyName));
            game->printBoard();
        }
    }
}

void Player::trade(char tradeWithC, vector<string> propertyNames) {
    Player *tradeWith = NULL;
    string tradeWithS = "";
    for (vector<Player*>::iterator it = game->getPlayers()->begin(); it != game->getPlayers()->end(); it++) {
        if (tradeWithC == (*it)->getPiece()) {
            tradeWith = *it;
            tradeWithS = (*it)->getName();
            break;
        }
    }
    
    if (!tradeWith) {
        game->getMIB().push(string("Player " + my_to_string(tradeWithC) + " doesn't exist"));
        game->printBoard();
    } else {
        int myCash = 0;
        vector<Property*> myProperties;
        
        int oCash = 0;
        vector<Property*> oProperties;
        
        bool invalid = false;
        while (propertyNames.size() > 0) {
            string s = *(propertyNames.begin());
            int number = 0;
            number = atoi(s.c_str());
            if (number != 0) {
                if (myCash == 0 && myProperties.size() == 0) {
                    if (cash >= number && number > 0) {
                        myCash = number;
                    } else {
                        noEnoughCash();
                        invalid = true;
                        break;
                    }
                } else {
                    if (tradeWith->getCash() >= number && number > 0) {
                        oCash = number;
                    } else {
                        noEnoughCash();
                        invalid = true;
                        break;
                    }
                }
            } else {
                Property* tmpProperty = NULL;
                for (vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++) {
                    if (s == (*it)->getName()) {
                        tmpProperty = *it;
                        myProperties.push_back(*it);
                        break;
                    }
                }
                if (!tmpProperty) {
                    for (vector<Property*>::iterator it = tradeWith->getProperties()->begin(); it != tradeWith->getProperties()->end(); it++) {
                        if (s == (*it)->getName()) {
                            tmpProperty = *it;
                            oProperties.push_back(*it);
                            break;
                        }
                    }
                    if (!tmpProperty) {
                        game->getMIB().push(string("Unknown property name: " + s));
                        invalid = true;
                        break;
                    }
                }
            }
            propertyNames.erase(propertyNames.begin());
        }
        
        if (!invalid) {
            while (true) {
                game->getMIB().push(string(name + " wants to trade with " + tradeWithS));
                
                string myOfferingS = myCash == 0? "": ("$" + my_to_string(myCash) + " ");
                for (vector<Property*>::iterator it = myProperties.begin(); it != myProperties.end(); it++) {
                    myOfferingS.append((*it)->getName() + ((*it)->getMortgaged()?"<M>": "")  + " ");
                }
                game->getMIB().push(string(name + " is offering: " + myOfferingS));
                
                string oOfferingS = oCash == 0? "": ("$" + my_to_string(oCash) + " ");
                for (vector<Property*>::iterator it = oProperties.begin(); it != oProperties.end(); it++) {
                    oOfferingS.append((*it)->getName() + ((*it)->getMortgaged()?"<M>": "")  + " ");
                }
                
                game->getMIB().push(string(name + " is asking for: " + oOfferingS));
                game->getMIB().push("Does " + tradeWithS + " want to trade (accept/reject):");
                game->printBoard();
                
                string answer;
                cin >> answer;
                if (answer == "accept") {
                    if (myCash != 0) {
                        cash -= myCash;
                        tradeWith->addCash(myCash);
                        game->getMIB().push(string(name + " gave $" + my_to_string(myCash) + " to " + tradeWith->getName()));
                    }
                    if (oCash != 0) {
                        cash += oCash;
                        tradeWith->addCash(-oCash);
                        game->getMIB().push(string(tradeWith->getName() + " gave $" + my_to_string(oCash) + " to " + name));
                    }
                    
                    for (vector<Property*>::iterator it1 = myProperties.begin(); it1 != myProperties.end(); it1++) {
                        for (vector<Property*>::iterator it2 = properties.begin(); it2 != properties.end(); it2++) {
                            if ((*it1)->getNumber() == (*it2)->getNumber()) {
                                (*it2)->setOwner(tradeWith);
                                tradeWith->getProperties()->push_back(*it2);
                                properties.erase(it2);
                                
                                game->getMIB().push(string(name + " gave " + (*it1)->getName() + " to " + tradeWith->getName()));
                                break;
                            }
                        }
                    }
                    
                    for (vector<Property*>::iterator it1 = oProperties.begin(); it1 != oProperties.end(); it1++) {
                        for (vector<Property*>::iterator it2 = tradeWith->getProperties()->begin(); it2 != tradeWith->getProperties()->end(); it2++) {
                            if ((*it1)->getNumber() == (*it2)->getNumber()) {
                                (*it2)->setOwner(this);
                                properties.push_back(*it2);
                                tradeWith->getProperties()->erase(it2);
                                
                                game->getMIB().push(string(tradeWith->getName() + " gave " + (*it1)->getName() + " to " + name));
                                break;
                            }
                        }
                    }
                    checkCombo();
                    tradeWith->checkCombo();
                    game->printBoard();
                    break;
                } else if (answer == "reject") {
                    game->getMIB().push(string(tradeWithS + " doesn't accept the deal, trade closed"));
                    break;
                } else {
                    game->getMIB().push("Please enter either accept or reject");
                }
            }
        }
    }
}

void Player::noEnoughCash() {
    game->getMIB().push(string(name + " doesn't have enough cash"));
    game->printBoard();
}

void Player::addProperty(Property *p) {
    properties.push_back(p);
}

vector<Property*> *Player::getProperties() {
    return &properties;
}

void Player::setForfeited(bool forfeited) {
    this->forfeited = forfeited;
}
bool Player::getForfeited() {
    return forfeited;
}

int Player::getNetWorth() {
    double netWorth = cash;
    
    for (vector<Property*>::iterator it = properties.begin(); it != properties.end(); it++) {
        netWorth += (*it)->getPurchaseCost()/2.0;
        if (dynamic_cast<AcademicBuilding*>(*it)) {
            AcademicBuilding *ab = dynamic_cast<AcademicBuilding*>(*it);
            netWorth += ab->getImprovementLevel() * ab->getImprovementCost() / 2.0;
        }
    }
    
    return netWorth;
}

void Player::setInJail(int inJail) {
    if (inJail == 1) {
        myTurn = false;
    }
    this->inJail = inJail;
}

void Player::addCup(RurCup *rc) {
    rurCups.push_back(rc);
}

Player::Player():cash(INITIAL_BALANCE), myTurn(false), inJail(false), quit(false) {
    
}

int Player::rollDice() {
    return rand() % 6 + 1;
}

void Player::setName(string name) {
    this->name = name;
}

string Player::getName() {
    return name;
}

void Player::setPiece(char piece) {
    this->piece = piece;
}

char Player::getPiece() {
    return piece;
}

void Player::setNumber(int number) {
    this->number = number;
}

int Player::getNumber() {
    return number;
}

void Player::setCash(int amount) {
    cash = amount;
}

void Player::addCash(int amount) {
    cash += amount;
}

int Player::getCash() {
    return cash;
}

void Player::setLandsOn(Block *landsOn) {
    this->landsOn = landsOn;
}

Block *Player::getLandsOn() {
    return landsOn;
}

void Player::setGame(Game *g) {
    game = g;
}

bool Player::getQuit() {
    return quit;
}

void Player::checkCombo() {
    if (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[36])->getOwner() != NULL && (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[36])->getOwner() == dynamic_cast<AcademicBuilding*>(game->getGameBoard()[38])->getOwner())) {
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[36])->setCombo(true);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[38])->setCombo(true);
    } else {
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[36])->setCombo(false);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[38])->setCombo(false);
    }
    if (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[30])->getOwner() != NULL && (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[30])->getOwner() == dynamic_cast<AcademicBuilding*>(game->getGameBoard()[31])->getOwner()) && (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[31])->getOwner() == dynamic_cast<AcademicBuilding*>(game->getGameBoard()[33])->getOwner())) {
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[30])->setCombo(true);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[31])->setCombo(true);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[33])->setCombo(true);
    } else {
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[30])->setCombo(false);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[31])->setCombo(false);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[33])->setCombo(false);
    }
    if (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[11])->getOwner() != NULL && (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[11])->getOwner() == dynamic_cast<AcademicBuilding*>(game->getGameBoard()[13])->getOwner()) && (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[13])->getOwner() == dynamic_cast<AcademicBuilding*>(game->getGameBoard()[14])->getOwner())) {
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[11])->setCombo(true);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[13])->setCombo(true);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[14])->setCombo(true);
    }
    if (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[21])->getOwner() != NULL && (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[21])->getOwner() == dynamic_cast<AcademicBuilding*>(game->getGameBoard()[23])->getOwner()) && (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[23])->getOwner() == dynamic_cast<AcademicBuilding*>(game->getGameBoard()[27])->getOwner())) {
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[21])->setCombo(true);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[23])->setCombo(true);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[27])->setCombo(true);
    } else {
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[21])->setCombo(false);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[23])->setCombo(false);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[27])->setCombo(false);
    }
    if (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[11])->getOwner() != NULL && (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[11])->getOwner() == dynamic_cast<AcademicBuilding*>(game->getGameBoard()[13])->getOwner()) && (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[13])->getOwner() == dynamic_cast<AcademicBuilding*>(game->getGameBoard()[17])->getOwner())) {
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[11])->setCombo(true);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[13])->setCombo(true);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[17])->setCombo(true);
    } else {
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[11])->setCombo(false);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[13])->setCombo(false);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[17])->setCombo(false);
    }
    if (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[1])->getOwner() != NULL && (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[1])->getOwner() == dynamic_cast<AcademicBuilding*>(game->getGameBoard()[3])->getOwner()) && (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[3])->getOwner() == dynamic_cast<AcademicBuilding*>(game->getGameBoard()[4])->getOwner())) {
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[1])->setCombo(true);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[3])->setCombo(true);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[4])->setCombo(true);
    } else {
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[1])->setCombo(false);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[3])->setCombo(false);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[4])->setCombo(false);
    }
    if (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[6])->getOwner() != NULL && (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[6])->getOwner() == dynamic_cast<AcademicBuilding*>(game->getGameBoard()[7])->getOwner()) && (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[7])->getOwner() == dynamic_cast<AcademicBuilding*>(game->getGameBoard()[9])->getOwner())) {
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[6])->setCombo(true);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[7])->setCombo(true);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[9])->setCombo(true);
    } else {
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[6])->setCombo(false);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[7])->setCombo(false);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[9])->setCombo(false);
    }
    if (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[12])->getOwner() != NULL && (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[12])->getOwner() == dynamic_cast<AcademicBuilding*>(game->getGameBoard()[14])->getOwner()) && (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[14])->getOwner() == dynamic_cast<AcademicBuilding*>(game->getGameBoard()[18])->getOwner())) {
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[12])->setCombo(true);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[14])->setCombo(true);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[18])->setCombo(true);
    } else {
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[12])->setCombo(false);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[14])->setCombo(false);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[18])->setCombo(false);
    }
    if (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[24])->getOwner() != NULL && (dynamic_cast<AcademicBuilding*>(game->getGameBoard()[24])->getOwner() == dynamic_cast<AcademicBuilding*>(game->getGameBoard()[28])->getOwner())) {
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[24])->setCombo(true);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[28])->setCombo(true);
    } else {
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[24])->setCombo(false);
        dynamic_cast<AcademicBuilding*>(game->getGameBoard()[28])->setCombo(false);
    }
    if (dynamic_cast<Gym*>(game->getGameBoard()[8])->getOwner() != NULL && (dynamic_cast<Gym*>(game->getGameBoard()[8])->getOwner() == dynamic_cast<Gym*>(game->getGameBoard()[25])->getOwner())) {
        dynamic_cast<Gym*>(game->getGameBoard()[8])->setCombo(true);
        dynamic_cast<Gym*>(game->getGameBoard()[25])->setCombo(true);
    } else {
        dynamic_cast<Gym*>(game->getGameBoard()[8])->setCombo(false);
        dynamic_cast<Gym*>(game->getGameBoard()[25])->setCombo(false);
    }
    if (dynamic_cast<Residence*>(game->getGameBoard()[5])->getOwner() != NULL && (dynamic_cast<Residence*>(game->getGameBoard()[5])->getOwner() == dynamic_cast<Residence*>(game->getGameBoard()[19])->getOwner()) && (dynamic_cast<Residence*>(game->getGameBoard()[19])->getOwner() == dynamic_cast<Residence*>(game->getGameBoard()[20])->getOwner()) && (dynamic_cast<Residence*>(game->getGameBoard()[20])->getOwner() == dynamic_cast<Residence*>(game->getGameBoard()[34])->getOwner())) {
        dynamic_cast<Residence*>(game->getGameBoard()[5])->setCombo(true);
        dynamic_cast<Residence*>(game->getGameBoard()[19])->setCombo(true);
        dynamic_cast<Residence*>(game->getGameBoard()[20])->setCombo(true);
        dynamic_cast<Residence*>(game->getGameBoard()[34])->setCombo(true);
    } else {
        dynamic_cast<Residence*>(game->getGameBoard()[5])->setCombo(false);
        dynamic_cast<Residence*>(game->getGameBoard()[19])->setCombo(false);
        dynamic_cast<Residence*>(game->getGameBoard()[20])->setCombo(false);
        dynamic_cast<Residence*>(game->getGameBoard()[34])->setCombo(false);
    }
}

string Player::getColour(int type) {
    string colour;
    
    if (type == COLOUR_TYPE_BACKGROUND) {
        colour = "\e[48;5;";
    } else if ( type == COLOUR_TYPE_FOREGROUND) {
        colour = "\e[38;5;";
    }
    
    switch (number) {
        case 0: {
            colour.append("160");
            break;
        }
        case 1: {
            colour.append("112");
            break;
        }
        case 2: {
            colour.append("220");
            break;
        }
        case 3: {
            colour.append("55");
            break;
        }
        case 4: {
            colour.append("202");
            break;
        }
        case 5: {
            colour.append("38");
            break;
        }
        case 6: {
            colour.append("146");
            break;
        }
        default: {
            colour.append("15");
            break;
        }
    }
    colour.append("m");
    return colour;
}

vector<RurCup*> *Player::getRurCups() {
    return &rurCups;
}

int Player::getInJail() {
    return inJail;
}
