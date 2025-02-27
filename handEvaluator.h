#ifndef H_EVAL_H
#define H_EVAL_H

#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "cards.h"
#include "player.h"

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

      } else if (combined[i] != combined[i - 1] ||
                 combined[i] != combined[i - 1]) {
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

  // ---- The following will the be the tie break logic ----

  static bool cardAcending(cards a,
                           cards b) {  // comparitor for the sorting function
    int aNum = a.getRankAsInt();
    int bNum = b.getRankAsInt();
    return aNum < bNum;  // returns the cards in acending order
  }

  int straightFlushTie(const std::vector<cards>& hand1,
                       const std::vector<cards>& hand2,
                       std::vector<cards>& river) {
    std::vector<cards> combined1 = river;
    std::vector<cards> combined2 = river;
    // adding cards in the combined vector
    for (int i = 0; i < 2; i++) {
      combined1.push_back(hand1[i]);
      combined2.push_back(hand2[i]);
    }

    // sorted the combinded vectors to find the highest straight flush

    std::sort(combined1.begin(), combined1.end(), cardAcending);
    std::sort(combined2.begin(), combined2.end(), cardAcending);

    // check first card in hand and then
    std::vector<int> highCards(2, 0);  // junk value

    auto findHighestStraightFlush =
        [](const std::vector<cards>& combined) -> int {
      int count = 1;
      int highestCard = 0;
      cards lastValidCard = combined[0];

      for (size_t i = 1; i < combined.size(); i++) {
        if (combined[i].getRankAsInt() == combined[i - 1].getRankAsInt() + 1 &&
            combined[i].getSuit() == combined[i - 1].getSuit()) {
          count++;
          lastValidCard =
              combined[i];  // Track the highest card in the sequence

          if (count >= 5) {
            highestCard = lastValidCard.getRankAsInt();
          }
        } else if ((combined[i].getRankAsInt() !=
                        combined[i - 1].getRankAsInt() + 1 ||
                    combined[i].getRankAsInt() !=
                        combined[i - 1].getRankAsInt())) {
          count = 1;  // Reset count when sequence breaks
        }
      }
      return highestCard;
    };

    // Find the highest straight flush for each player
    highCards[0] = findHighestStraightFlush(combined1);
    highCards[1] = findHighestStraightFlush(combined2);

    // Compare the highest straight flushes
    return highCards[0] > highCards[1] ? highCards[0] : highCards[1];
  }

  int checkKicker(std::vector<cards> hand1, std::vector<cards> hand2) {
    // combine the hands and then find the largest card
    std::unordered_set<int> rank1;
    std::unordered_set<int> rank2;

    for (size_t i = 0; i < 2; i++) {
      rank1.insert(hand1[i].getRankAsInt());
      rank2.insert(hand2[i].getRankAsInt());
    }

    // sort the hands
    std::sort(hand1.begin(), hand1.end(), cardAcending);
    std::sort(hand2.begin(), hand2.end(), cardAcending);

    // first we need to compare the largest cards and then if they are the same
    // we should compare the next

    for (int i = 1; i >= 0; i--) {
      if (hand1[i].getRankAsInt() > hand2[i].getRankAsInt()) {
        return 1;
      } else if (hand1[i].getRankAsInt() < hand2[i].getRankAsInt()) {
        return 0;
      }
    }

    // if none of the return statements have been executed this means that the
    // hand ranks are identical meaning we have a draw

    return -1;
  }

  int fourOfaKindTie(
      const std::vector<cards>& hand1, const std::vector<cards>& hand2,
      std::vector<cards>& river) {  // find the highest 4 of a kind and if not
                                    // compare kicker find the biggest 4
    std::vector<cards> combined1 = river;
    std::vector<cards> combined2 = river;
    // adding cards in the combined vector
    for (int i = 0; i < 2; i++) {
      combined1.push_back(hand1[i]);
      combined2.push_back(hand2[i]);
    }
    // add all the cards that equal 4 and then return the cards that do

    std::vector<int> cardCount1(15, 0);
    std::vector<int> cardCount2(15, 0);

    cards rank1(cards::Rank::Two, cards::Suit::Clubs);
    cards rank2(cards::Rank::Two, cards::Suit::Clubs);

    for (size_t i = 0; i < combined1.size(); i++) {
      cardCount1[combined1[i].getRankAsInt()]++;
      cardCount2[combined2[i].getRankAsInt()]++;
      if (cardCount1[combined1[i].getRankAsInt()] == 4) {
        rank1 = combined1[i];
      }
      if (cardCount2[combined2[i].getRankAsInt()] == 4) {
        rank2 = combined2[i];
      }
    }

    //  find the highest rank
    if (rank1.getRankAsInt() > rank2.getRankAsInt()) {
      return 1;
    } else if (rank1.getRankAsInt() < rank2.getRankAsInt()) {
      return 0;
    }
    // this means that the 4 of a kind is on the bard so we need to checker
    // kicker

    return checkKicker(hand1, hand2);
  }

  int fullHouseTie(const std::vector<cards>& hand1,
                   const std::vector<cards>& hand2, std::vector<cards>& river) {
    // first we need to find which cards give either player a full house
    std::unordered_map<int, int> rankCount1;
    std::unordered_map<int, int> rankCount2;

    std::vector<cards> combined1 = river;
    std::vector<cards> combined2 = river;

    for (size_t i = 0; i < 2; i++) {
      combined1.push_back(hand1[i]);
      combined2.push_back(hand2[i]);
    }

    for (size_t i = 0; i < combined1.size(); i++) {
      rankCount1[combined1[i].getRankAsInt()]++;
      rankCount2[combined2[i].getRankAsInt()]++;
    }

    // get the three of a kind from the count
    int hero3Count = 0;
    int OP3Count = 0;

    for (auto& card : rankCount1) {
      if (card.second >= 3 && card.first > hero3Count) {
        hero3Count = card.first;
      }
    }
    for (auto& card : rankCount2) {
      if (card.second >= 3 && card.first > OP3Count) {
        OP3Count = card.first;
      }
    }

    // the higher 3 pair wins else we need to evaluate the two pair

    if (hero3Count > OP3Count) {
      return 1;
    } else if (hero3Count < OP3Count) {
      return 0;
    }

    // same proocess to identify a 2 pair
    int hero2Count = 0;
    int OP2Count = 0;

    for (auto& card : rankCount1) {
      if (card.second == 2 && card.first > hero2Count) {
        hero2Count = card.first;
      }
    }

    for (auto& card : rankCount2) {
      if (card.second == 2 && card.first > OP2Count) {
        OP2Count = card.first;
      }
    }

    // this higher pair wins else its a tie

    if (hero2Count > OP2Count) {
      return 1;
    } else if (hero2Count < OP2Count) {
      return 0;
    } else
      return -1;
  }

  int flushTie(const std::vector<cards>& hand1, const std::vector<cards>& hand2,
               std::vector<cards>& river) {
    // compare the highest flush card and move down the list of flush cards
    // until all flush cards are evaluted. if there are equal for both player
    // this means that the flush is on the board
    std::vector<cards> combined1 = river;
    std::vector<cards> combined2 = river;

    std::unordered_map<std::string, int> suitCount1;
    std::unordered_map<std::string, int> suitCount2;

    for (size_t i = 0; i < 2; i++) {
      combined1.push_back(hand1[i]);
      combined2.push_back(hand2[i]);
    }

    for (size_t i = 0; i < combined1.size(); i++) {
      suitCount1[combined1[i].suitToString()]++;
      suitCount2[combined2[i].suitToString()]++;
    }

    // find the suit that gives the flush for both players
    std::string suit1;
    for (auto& suit : suitCount1) {
      if (suit.second >= 5) {
        suit1 = suit.first;
      }
    }

    std::string suit2;
    for (auto& suit : suitCount2) {
      if (suit.second >= 5) {
        suit2 = suit.first;
      }
    }

    // now find the highest suits by sorting both of the combined vectors and
    // then checking them to see if they are of the saem suit and if they are
    // equal.

    std::sort(combined1.begin(), combined1.end(),
              [](const cards& a, const cards& b) -> bool {
                return a.getRankAsInt() > b.getRankAsInt();
              });
    std::sort(combined2.begin(), combined2.end(),
              [](const cards& a, const cards& b) -> bool {
                return a.getRankAsInt() > b.getRankAsInt();
              });

    for (size_t i = 0; i < combined1.size(); i++) {
      if (combined1[i].suitToString() == suit1 &&
          combined2[i].suitToString() == suit2) {
        if (combined1[i].getRankAsInt() > combined2[i].getRankAsInt()) {
          return 1;
        }
        if (combined1[i].getRankAsInt() < combined2[i].getRankAsInt()) {
          return 0;
        }
      }
    }

    return -1;
  }

  int straightTieBreak(const std::vector<cards>& hand1,
                       const std::vector<cards>& hand2,
                       std::vector<cards>& river) {
    // we just need to see which straight has a higher rank this means we need
    // to find the straight for both players and then find the biggest rank.
    std::vector<cards> combined1 = river;
    std::vector<cards> combined2 = river;

    for (size_t i = 0; i < 2; i++) {
      combined1.push_back(hand1[i]);
      combined2.push_back(hand2[i]);
    }

    std::sort(combined1.begin(), combined1.end(), cardAcending);
    std::sort(combined2.begin(), combined2.end(), cardAcending);
    int highestrank1 = 0;
    int highestrank2 = 0;

    int count1 = 1;
    int count2 = 1;

    // finding the highest ranks

    for (size_t i = 0; i < combined1.size(); i++) {
      if (highestrank1 < combined1[i].getRankAsInt()) {
        count1++;
        if (count1 >= 5) {
          highestrank1 = combined1[i].getRankAsInt();
        }
      }

      if (highestrank2 < combined2[i].getRankAsInt()) {
        count2++;
        if (count2 >= 5) {
          highestrank2 = combined2[i].getRankAsInt();
        }
      }
    }

    if (highestrank1 > highestrank2) {
      return 1;
    } else if (highestrank1 < highestrank2) {
      return 0;
    }

    if (highestrank1 == highestrank2) {
      return -1;
    }

    return 6;  // dummy return variable
  }

  int threeOfaKindTie(const std::vector<cards>& hand1,
                      const std::vector<cards>& hand2,
                      std::vector<cards>& river) {
    // compare the three pair and then compare kickers

    std::unordered_map<std::string, int> rankCount1;
    std::unordered_map<std::string, int> rankCount2;

    std::vector<cards> combined1 = river;
    std::vector<cards> combined2 = river;

    for (size_t i = 0; i < 2; i++) {
      combined1.push_back(hand1[i]);
      combined2.push_back(hand2[i]);
    }

    for (size_t i = 0; i < combined1.size(); i++) {
      rankCount1[combined1[i].rankToString()]++;
      rankCount2[combined2[i].rankToString()]++;
    }

    int highestRank1 = 0;
    int highestRank2 = 0;

    // we need to find the highest 3 pair for both players
    for (auto& count : rankCount1) {
      if (count.second == 3 && highestRank1 < stoi(count.first)) {
        highestRank1 = stoi(count.first);
      }
    }
    // we need to find the highest 3 pair for both players
    for (auto& count : rankCount2) {
      if (count.second == 3 && highestRank2 < stoi(count.first)) {
        highestRank2 = stoi(count.first);
      }
    }

    if (highestRank1 > highestRank2) {
      return 1;
    } else if (highestRank1 < highestRank2) {
      return 0;
    }

    // if both players have the same 3 pair we go to the kicker

    return checkKicker(hand1, hand2);
  }

  int twoPairTie(const std::vector<cards>& hand1,
                 const std::vector<cards>& hand2, std::vector<cards>& river) {
    // we need to find the 2 cards that make up the 2 pairs and compare them
    std::vector<cards> combined1 = river;
    std::vector<cards> combined2 = river;

    std::unordered_map<int, int> rankCount1;
    std::unordered_map<int, int> rankCount2;

    for (size_t i = 0; i < 2; i++) {
      combined1.push_back(hand1[i]);
      combined2.push_back(hand2[i]);
    }

    for (size_t i = 0; i < combined1.size(); i++) {
      rankCount1[combined1[i].getRankAsInt()]++;
      rankCount2[combined2[i].getRankAsInt()]++;
    }

    // search through to find the 2 pairs
    std::vector<int> pair1(2, 0);
    std::vector<int> pair2(2, 0);

    for (auto& rank : rankCount1) {
      int i = 0;
      if (rank.second == 2 && rank.second != pair1[i]) {
        pair1[i] = rank.first;
        i++;
      }
    }

    for (auto& rank : rankCount2) {
      int i = 0;
      if (rank.second == 2 && rank.second != pair2[i]) {
        pair2[i] = rank.first;
        i++;
      }
    }

    std::sort(pair1.begin(), pair1.end());
    std::sort(pair2.begin(), pair2.end());

    // now we have the 2 distict ranks in our vector we compare to find the
    // winner
    if (pair1[1] > pair2[1]) {
      return 1;
    } else if (pair1[1] < pair2[1]) {
      return 0;
    }
    if (pair1[0] > pair2[0]) {
      return 1;
    } else if (pair1[0] < pair2[0]) {
      return 0;
    }

    // if both pairs are equal we need to check the kickers
    return checkKicker(hand1, hand2);
  }

  int pairTieBreak(const std::vector<cards>& hand1,
                   const std::vector<cards>& hand2, std::vector<cards>& river) {
    // compare the pairs and then if they are the same we compare the kickers
    std::vector<cards> combined1 = river;
    std::vector<cards> combined2 = river;

    std::unordered_map<int, int> rankCount1;
    std::unordered_map<int, int> rankCount2;

    for (size_t i = 0; i < 2; i++) {
      combined1.push_back(hand1[i]);
      combined2.push_back(hand2[i]);
    }

    for (size_t i = 0; i < combined1.size(); i++) {
      rankCount1[combined1[i].getRankAsInt()]++;
      rankCount2[combined2[i].getRankAsInt()]++;
    }

    int pair1 = 0;
    int pair2 = 0;
    for (auto& rank : rankCount1) {
      if (rank.second == 2) {
        pair1 = rank.first;
      }
    }
    for (auto& rank : rankCount2) {
      if (rank.second == 2) {
        pair2 = rank.first;
      }
    }
    // compare the ranks of both pairs
    if (pair1 > pair2) {
      return 1;
    } else if (pair1 < pair2) {
      return 0;
    }

    return checkKicker(hand1, hand2);
  }
  int tieBreaker(
      const std::vector<cards>& hand1, const std::vector<cards>& hand2,
      std::vector<cards>& river,
      int score) {  // return 1 if hero wins 0 if hero loses -1 if tie

    // juding by the score, we will know how to compare both hands

    switch (score) {
      case 10:
        return -1;
        break;

      case 9:  // straight flush
        return straightFlushTie(hand1, hand2, river);

        break;

      case 8:  // four of a kind find kicker
        return fourOfaKindTie(hand1, hand2, river);
        break;
      case 7:  // full house tie
        return fullHouseTie(hand1, hand2, river);
        break;
      case 6:  // flush tie
        return flushTie(hand1, hand2, river);
        break;
      case 5:  // straight tie
        return straightTieBreak(hand1, hand2, river);
        break;
      case 4:  // three of a kind tie
        return threeOfaKindTie(hand1, hand2, river);
        break;
      case 3:  // 2 pair tie
        return twoPairTie(hand1, hand2, river);
        break;
      case 2:  // pair tie
        return pairTieBreak(hand1, hand2, river);
        break;
      case 1:  // compare kickers (high card)
        return checkKicker(hand1, hand2);
        break;

      default:
        std::cout << "default has been called, tie was NOT returned"
                  << std::endl;
        break;
    }

    return 4;  // dummy return value
  }
};

#endif