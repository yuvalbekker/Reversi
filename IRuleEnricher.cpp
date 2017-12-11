//Yuval Bekker
//311254585

#include <clocale>
#include "IRuleEnricher.h"

IRuleEnricher::~IRuleEnricher() {

}

vector<RowOccupationContainer> *
IRuleEnricher::enrichPossiblePlays(vector<RowOccupationContainer> *standardPossiblePlays) {
    return standardPossiblePlays;
}
