#include "core/choose_hand.h"

#include <cassert>
#include <algorithm>
#include <iostream>

namespace yg {

using std::make_unique;
using std::unique_ptr;
using std::string;

ChooseHand::ChooseHand() {}

void ChooseHand::add_card(Card c) { cards_.push_back(c); }

void ChooseHand::remove_last() { cards_.pop_back(); }

unique_ptr<Hand> ChooseHand::best_hand() {
  assert(cards_.size() >= 5);
  unique_ptr<Hand> best_hand = nullptr;
  Hand h;

  for (uint a = 0; a < cards_.size(); a++) {
    h.add_card(cards_[a]);
    for (uint b = a + 1; b < cards_.size(); b++) {
      h.add_card(cards_[b]);
      for (uint c = b + 1; c < cards_.size(); c++) {
        h.add_card(cards_[c]);
        for (uint d = c + 1; d < cards_.size(); d++) {
          h.add_card(cards_[d]);
          for (uint e = d + 1; e < cards_.size(); e++) {
            h.add_card(cards_[e]);
            if (best_hand == nullptr || h < *best_hand) {
              best_hand = make_unique<Hand>(h);
            }
            h.remove_last();
          }
          h.remove_last();
        }
        h.remove_last();
      }
      h.remove_last();
    }
    h.remove_last();
  }
  return best_hand;
}
} // namespace yg
