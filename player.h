#include "cards.h"
#include "deck.h"

class player {
 private:
  std::vector<cards> hand;

 public:
  // every player begins with 2 cards in hand from the deck
  player(deck& deck) {
    this->hand.push_back(deck.drawCard());
    this->hand.push_back(deck.drawCard());
  }

  void displayHand() {
    std::cout << "your hand is: " << hand[0] << " , " << hand[1] << std::endl;
  }
  std::vector<cards> getHand() { return this->hand; }
};
