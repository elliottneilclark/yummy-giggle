#pragma once

#include <cstdint>
#include <array>
#include "core/card.h"

namespace yg {
class Deck {
public:
  Deck();
  void remove(Card c);
  void shuffle();
  Card &take();
  bool has_more();

private:
  int next_card_ = 0;
  std::array<Card, 52> cards_ = {};
};
}
