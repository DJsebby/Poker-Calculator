#ifndef H_EVAL_H
#define H_EVAL_H

#include <algorithm>
#include <string>

#include "cards.h"
#include "player.h"
#include "unordered_map"
#include "unordered_set"

class handEvaluator {
 private:
 public:
  bool hasPair(std::vector<cards> hand, std::vector<cards> river) {
    if (hand[0].getRank() == hand[1].getRank()) {
      return true;
    }

    for (size_t i = 0; i < river.size(); i++) {
      if (hand[0].getRank() == river[i].getRank()) {
        return true;
      }
    }

    for (size_t i = 0; i < river.size(); i++) {
      if (hand[1].getRank() == river[i].getRank()) {
        return true;
      }
    }
    return false;
  }

  bool hasTwoPair(std::vector<cards> hand, std::vector<cards> river) {
    // combine hand and river. check if there are 2 pairs by
    std::unordered_map<int, int> rankCount;
    std::vector<cards> combined = hand;
    for (size_t i = 0; i < river.size(); i++) {
      combined.push_back(river[i]);
    }

    for (size_t i = 0; i < combined.size(); i++) {
      rankCount[combined[i].getRankAsInt()]++;
    }

    int pairCount = 0;
    for (auto it : rankCount) {
      if (it.second == 2) {
        pairCount++;
      }
    }

    return pairCount >= 2;
  }

  bool hasThreeOfaKind(const std::vector<cards>& hand,
                       const std::vector<cards>& river) {
    std::vector<cards> combined;  // hand and river

    std::unordered_map<cards::Rank, int> rankCount;

    for (size_t i = 0; i < hand.size(); i++) {
      combined.push_back(hand[i]);
      rankCount[hand[i].getRank()]++;  // default value = 0 therefore we are
                                       // counting once instance of that object
    }

    for (size_t i = 0; i < river.size(); i++) {
      combined.push_back(river[i]);
      rankCount[river[i].getRank()]++;
    }

    for (auto it = rankCount.begin(); it != rankCount.end(); it++) {
      if (it->second == 3) {
        return true;
      }
    }

    return false;
  }

  bool hasFourOfaKind(const std::vector<cards>& hand,
                      const std::vector<cards>& river) {
    std::unordered_map<cards::Rank, int> rankCount;

    for (size_t i = 0; i < hand.size(); i++) {
      rankCount[hand[i].getRank()]++;  // default value = 0 therefore we are
                                       // counting once instance of that object
    }

    for (size_t i = 0; i < river.size(); i++) {
      rankCount[river[i].getRank()]++;
    }

    for (auto it = rankCount.begin(); it != rankCount.end(); it++) {
      if (it->second == 4) {
        return true;
      }
    }

    return false;
  }

  bool hasStraight(const std::vector<cards>& hand,
                   const std::vector<cards>& river) {
    // create combined river, sort and check if 5 ranks are consecutive
    // O(nlogn)

    std::vector<int> combined;

    for (size_t i = 0; i < hand.size(); i++) {
      combined.push_back(hand[i].getRankAsInt());
      if (hand[i].getRankAsInt() == 14) {
        combined.push_back(1);
      }
    }

    for (size_t i = 0; i < river.size(); i++) {
      combined.push_back(river[i].getRankAsInt());
      if (river[i].getRankAsInt() == 14) {
        combined.push_back(1);
      }
    }

    // sorting
    std::sort(combined.begin(), combined.end());

    // checking if consecutive
    int count = 1;

    for (size_t i = 1; i < combined.size(); i++) {
      if (combined[i] == combined[i - 1] + 1) {
        count++;
        if (count >= 5) {
          return true;
        }

      } else if (combined[i] != combined[i - 1]) {
        count = 1;
      }
    }

    return false;
  }

  bool hasFlush(const std::vector<cards>& hand,
                const std::vector<cards>& river) {
    // now form combined and check if there are 5 matching suits.
    std::unordered_map<std::string, int> suitCount;

    for (size_t i = 0; i < hand.size(); i++) {
      suitCount[hand[i].suitToString()]++;
    }

    for (size_t i = 0; i < river.size(); i++) {
      suitCount[river[i].suitToString()]++;
    }

    // check if any counts are >= 5

    for (auto it : suitCount) {
      if (it.second >= 5) {
        return true;
      }
    }
    return false;
  }

  bool hasFullHouse(const std::vector<cards>& hand,
                    const std::vector<cards>& river) {
    std::unordered_map<std::string, int> rankCount;

    for (size_t i = 0; i < hand.size(); i++) {
      rankCount[hand[i].rankToString()]++;
    }

    for (size_t i = 0; i < river.size(); i++) {
      rankCount[river[i].rankToString()]++;
    }

    // check if any counts are >= 5
    bool pair = false;
    bool three = false;
    for (auto it : rankCount) {
      if (it.second >= 3) {
        three = true;
      }

      if (it.second >= 2) {
        pair = true;
      }
    }

    // checking if the 2 of a kinda and 3 of a kinda exists seperatly
    if (three) {
      for (const auto& it : rankCount) {
        if (it.second >= 2 && !(it.second >= 3)) {
          pair = true;
          break;
        }
      }
    }

    return three && pair;
  }

  bool hasStraightFlush(const std::vector<cards>& hand,
                        const std::vector<cards>& river) {
    // same process as flush checker but need to check if the flush cards are
    // consecutive. store the flush cards in an array and then sort and check

    std::unordered_map<std::string, int> suitCount;
    std::vector<cards> combined;

    for (size_t i = 0; i < hand.size(); i++) {
      suitCount[hand[i].suitToString()]++;
      combined.push_back(hand[i]);
    }
    for (size_t i = 0; i < river.size(); i++) {
      suitCount[river[i].suitToString()]++;
      combined.push_back(river[i]);
    }

    std::vector<cards> sameSuit;
    for (size_t i = 0; i < combined.size(); i++) {
      if (suitCount[combined[i].suitToString()] >= 5) {
        sameSuit.push_back(combined[i]);
      }
    }

    // check if the same suits have consecutive ranks
    std::vector<cards> empty;

    return hasStraight(sameSuit, empty);
  }

  bool hasRoyalFlush(const std::vector<cards>& hand,
                     const std::vector<cards>& river) {
    // add all cards of the same suit to a set and then check the set to ensure
    // that they have all the royal cards
    std::vector<cards> combined;
    std::vector<cards> royal;
    std::unordered_map<std::string, std::unordered_set<int>> sameSuit;
    // set of valid ranks
    std::unordered_set<int> validRanks = {10, 11, 12, 13, 14};

    for (size_t i = 0; i < hand.size(); i++) {
      combined.push_back(hand[i]);
      sameSuit[hand[i].suitToString()].insert(hand[i].getRankAsInt());
    }
    for (size_t i = 0; i < river.size(); i++) {
      combined.push_back(river[i]);
      sameSuit[river[i].suitToString()].insert(river[i].getRankAsInt());
    }

    for (auto it : sameSuit) {
      if (it.second == validRanks) {
        return true;
      }
    }

    return false;
  }

  int evaluateHandStrength(const std::vector<cards>& hand,
                           const std::vector<cards>& river) {
    if (hasRoyalFlush(hand, river)) return 10;
    if (hasStraightFlush(hand, river)) return 9;
    if (hasFourOfaKind(hand, river)) return 8;
    if (hasFullHouse(hand, river)) return 7;
    if (hasFlush(hand, river)) return 6;
    if (hasStraight(hand, river)) return 5;
    if (hasThreeOfaKind(hand, river)) return 4;
    if (hasTwoPair(hand, river)) return 3;
    if (hasPair(hand, river)) return 2;
    return 1;  // High card
  }
};

#endif