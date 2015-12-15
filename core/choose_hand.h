#pragma once

#include <vector>
#include <memory>

#include "core/hand.h"
#include "core/card.h"

namespace yg {

// Class for choosing the best hand from a given set
// Currently this doesn't support any constraints.
// As such it doesn't support omaha
class ChooseHand {
public:
  ChooseHand();
  std::unique_ptr<Hand> best_hand();
  void add_card(Card c);
  void remove_last();

private:
  std::vector<bool> prepare_mask();
  std::vector<Card> cards_;
};
}
