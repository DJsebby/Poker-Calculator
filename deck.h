#ifndef DECK_H
#define DECK_H

#include <time.h>

#include <algorithm>
#include <random>
#include <string>
#include <vector>

#include "cards.h"

class deck {
 private:
  std::vector<cards> current_deck;

 public:
  deck() {
    // populate the deck in order

    for (size_t i = 2; i < 14; i++)  // loop over the ranks
    {
      for (size_t j = 0; j < 4; j++)  // loop over the suits
      {
        current_deck.emplace_back(static_cast<cards::Rank>(i),
                                  static_cast<cards::Suit>(j));
      }
    }

    // now shuffle deck
    shuffleDeck();
  }

  void shuffleDeck() {
    std::random_device s;  // seed from hardware entropy
    std::mt19937 mt(s());
    std::shuffle(current_deck.begin(), current_deck.end(), mt);
    // std::cout << "deck has been shuffled \n";
  }

  cards drawCard() {
    if (current_deck.size() == 0) {
      std::cout << "deck is empty \n";
    }

    cards first_card = current_deck.back();
    current_deck.pop_back();
    return first_card;
  }

  void printDeck(std::vector<cards>& a) {
    for (size_t i = 0; i < a.size(); i++) {
      std::cout << a[i];
    }
    std::cout << std::endl;
  }

  std::vector<cards> drawHand() {
    std::vector<cards> hand;
    for (size_t i = 0; i < 2; i++) {
      hand.push_back(drawCard());
    }
    return hand;
  }
  std::vector<cards> drawFullRiver() {
    std::vector<cards> river;
    for (size_t i = 0; i < 5; i++) {
      river.push_back(drawCard());
    }
    return river;
  }

  std::vector<cards> drawFlop() {
    std::vector<cards> flop;
    drawCard();  // to burn the car

    for (size_t i = 0; i < 3; i++) {
      flop.push_back(drawCard());
    }
    return flop;
  }
  cards drawTurn() {
    drawCard();  // to burn the car
    return drawCard();
  }

  cards drawRiver() {
    drawCard();  // to burn the car
    return drawCard();
  }

  void reshuffle(std::vector<cards> cardsR) {
    for (size_t i = 0; i < cardsR.size(); i++) {
      current_deck.push_back(cardsR[i]);
    }

    shuffleDeck();
  }

  int getDeckSize() { return current_deck.size(); }

  std::vector<cards> drawFourHAceC() {  // just for testing purposes
    std::vector<cards> hand;
    for (int i = 0; i < current_deck.size(); i++) {
      if (current_deck[i].getRank() == cards::Rank::Four &&
          current_deck[i].getSuit() == cards::Suit::Hearts) {
        hand.push_back(current_deck[i]);
      }
    }

    for (int i = 0; i < current_deck.size(); i++) {
      if (current_deck[i].getRank() == cards::Rank::Ace &&
          current_deck[i].getSuit() == cards::Suit::Clubs) {
        hand.push_back(current_deck[i]);
      }
    }
    return hand;
  }

  std::vector<cards> drawTenCJackD() {  // just for testing purposes
    std::vector<cards> hand;
    for (int i = 0; i < current_deck.size(); i++) {
      if (current_deck[i].getRank() == cards::Rank::Ten &&
          current_deck[i].getSuit() == cards::Suit::Clubs) {
        hand.push_back(current_deck[i]);
      }
    }

    for (int i = 0; i < current_deck.size(); i++) {
      if (current_deck[i].getRank() == cards::Rank::Jack &&
          current_deck[i].getSuit() == cards::Suit::Diamonds) {
        hand.push_back(current_deck[i]);
      }
    }
    return hand;
  }
};

#endif