#ifndef TEST_GUARD
#define TEST_GUARD

#include <iostream>
#include <vector>

#include "handEvaluator.h"
#include "winningOdds.h"

double testGetProbability(std::vector<cards> &hand, std::vector<cards> &OPhand,
                          std::vector<cards> board, int numOp, int numOfIter,
                          deck &d);

double testingTheFlop(std::vector<cards> &hand, std::vector<cards> &OPhand,
                      int numOfIter);

void oneOpponentSetCards();
#endif
