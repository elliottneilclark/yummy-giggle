#include "core/deck.h"
#include <random>
#include <algorithm>

namespace yg {
Deck::Deck() {
  int i = 0;
  for (uint8_t suit : kSuits) {
    for (uint16_t value : kValues) {
      cards_[i++] = Card{value, suit};
    }
  }
}

void Deck::remove(Card c) {
  // The suits are ordered
  // That means that all cards of suit log2(1) will be before cards of suit
  // log2(2)
  int idx = static_cast<int>(std::log2(c.suit())) * 13 +
            static_cast<int>(std::log2(c.value()));
  if (idx != next_card_) {
    std::swap(cards_[next_card_], cards_[idx]);
  }
  next_card_++;
}

void Deck::shuffle() {
  static thread_local std::mt19937 generator;
  std::shuffle(cards_.begin() + next_card_, cards_.end(), generator);
}

bool Deck::has_more() const { return next_card_ < 52; }
Card &Deck::take() { return cards_[next_card_++]; }
} // namespace yg
