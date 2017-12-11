//Yuval Bekker
//311254585

#ifndef REVERSE_IRULEENRICHER_H
#define REVERSE_IRULEENRICHER_H

#include "RowOccupationContainer.h"
#include <vector>

class IRuleEnricher {
public:
    /**
     * The destructor.
    */
    virtual ~IRuleEnricher();

    /**
     * Enriches the input plays with another possible game plays.
     * @param standardPossiblePlays vector<RowOccupationContainer> * object
     * @return vector<RowOccupationContainer> *
    */
    virtual vector<RowOccupationContainer> *
    enrichPossiblePlays(vector<RowOccupationContainer> *standardPossiblePlays);
};


#endif //REVERSE_IRULEENRICHER_H
