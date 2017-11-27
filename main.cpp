//Yuval Bekker
//311254585

#include <iostream>
#include "Board.h"
#include "ConsoleGameOperator.h"
#include "StandardRuleEnricher.h"

using namespace std;

/**
* The main function of the program.
* @return int
*/
int main() {
    Player *first = new Player(new Disk('X'), Board::Black);
    Player *second = new Player(new Disk('O'), Board::White);
    ConsoleGameOperator *gameOperator = new ConsoleGameOperator(first, second, 8, 8);
    GameResult result = gameOperator->play((StandardRuleEnricher()));
    switch (result.getType()) {
        case Board::White:
            cout << "O Player Won! your score is " << result.getScore();
            break;
        case Board::Black:
            cout << "X Player Won! your score is " << result.getScore();
            break;
        case Board::None:
            cout << "Tie. score is " << result.getScore();
            break;
    }
    cout << "\n";
    delete gameOperator;
    delete first;
    delete second;
    return 0;
}