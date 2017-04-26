#include "core/deck.h"

namespace yg {
Deck::Deck() {
  for (uint8_t suit : kSuits) {
    for (uint16_t value : kValues) {
      cards_.emplace(value, suit);
    }
  }
}

std::vector<Card> Deck::Cards() const {
  return std::vector<Card>{cards_.begin(), cards_.end()};
}

void Deck::Remove(const Card& c) { cards_.erase(c); }
}  // namespace yg
