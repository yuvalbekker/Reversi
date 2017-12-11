//Yuval Bekker
//311254585

#ifndef REVERSE_STANDARDRULEENRICHER_H
#define REVERSE_STANDARDRULEENRICHER_H


#include "RowOccupationContainer.h"
#include "IRuleEnricher.h"

class StandardRuleEnricher : public IRuleEnricher {
public:
    /**
     * The constructor.
    */
    StandardRuleEnricher();

    /**
     * The destructor.
    */
    virtual ~StandardRuleEnricher();

    /**
     * Enriches the input plays with another possible game plays.
     * @param standardPossiblePlays vector<RowOccupationContainer> * object
     * @return vector<RowOccupationContainer> *
    */
    virtual vector<RowOccupationContainer> *
    enrichPossiblePlays(vector<RowOccupationContainer> *standardPossiblePlays);
};


#endif //REVERSE_STANDARDRULEENRICHER_H