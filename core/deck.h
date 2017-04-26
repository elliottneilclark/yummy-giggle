#pragma once

#include <cstdint>
#include <unordered_set>
#include <vector>

#include "core/card.h"

namespace yg {
class Deck {
 public:
  Deck();
  void Remove(const Card& c);
  std::vector<Card> Cards() const;

 private:
  std::unordered_set<Card> cards_ = {};
};
}  // namespace yg
