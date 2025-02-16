#ifndef TEST_GUARD
#define TEST_GUARD

#include <vector>

#include "winningOdds.h"

int testGetProbability(std::vector<cards> &hand, std::vector<cards> &OPhand,
                       std::vector<cards> &board, int numOp, int numOfIter,
                       deck &d);

void oneOpponentSetCards();

#endif
