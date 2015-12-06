#pragma once

#include <vector>
#include <memory>

#include "core/hand.h"
#include "core/card.h"

namespace yg {
class ChooseHand {
public:
  std::unique_ptr<Hand> best_hand();
  void add_card(Card c);
  void remove_last();

private:
  std::vector<bool> prepare_mask();
  std::vector<Card> cards_;
};
}
