#pragma once

#include <array>
#include <cstdint>

#include "core/card.h"

namespace yg {
class Deck {
public:
  Deck();
  void remove(Card c);
  void shuffle();
  Card &take();
  bool has_more() const;
  const std::array<Card, 52> &cards() const { return cards_; }
  int next_card() const { return next_card_; }

private:
  int next_card_ = 0;
  std::array<Card, 52> cards_ = {};
};
} // namespace yg
