#include "core/deck.h"
#include <algorithm>
#include <random>

namespace yg {
Deck::Deck() {
  int i = 0;
  for (uint8_t suit : kSuits) {
    for (uint16_t value : kValues) {
      cards_[i++] = Card{value, suit};
    }
  }
}

void Deck::remove(Card c) {}

void Deck::shuffle() {
  static thread_local std::mt19937 generator;
  std::shuffle(cards_.begin() + next_card_, cards_.end(), generator);
}

bool Deck::has_more() const { return next_card_ < 52; }
Card &Deck::take() { return cards_[next_card_++]; }
}  // namespace yg
