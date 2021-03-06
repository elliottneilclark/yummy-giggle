#include <array>
#include <ctime>
#include <iostream>
#include <vector>

#include "core/card.h"
#include "core/choose_hand.h"
#include "core/choose_iter.h"
#include "core/deck.h"
#include "core/hand.h"

using namespace yg;
using namespace std;

int64_t rankFive(const array<Card, 52> &cards) {
  Hand h;
  int64_t best_rank = 0;
  for (uint a = 0; a < 52; a++) {
    h.add_card(cards[a]);
    for (uint b = a + 1; b < 52; b++) {
      h.add_card(cards[b]);
      for (uint c = b + 1; c < 52; c++) {
        h.add_card(cards[c]);
        for (uint d = c + 1; d < 52; d++) {
          h.add_card(cards[d]);
          for (uint e = d + 1; e < 52; e++) {
            h.add_card(cards[e]);
            best_rank = max(best_rank, h.Rank());
            h.RemoveLast();
          }
          h.RemoveLast();
        }
        h.RemoveLast();
      }
      h.RemoveLast();
    }
    h.Remove_last();
  }
  return best_rank;
}

int64_t rankFiveIter(const Deck d) {
  int64_t best_rank = 1l << 22;
  ChooseIter iter{d, 5};
  Hand h{};
  for (const vector<Card> &cards : iter) {
    h.clear();
    for (const Card &c : cards) {
      h.add_card(c);
    }
    best_rank = min(best_rank, h.Rank());
  }
  return best_rank;
}

array<Card, 52> make_cards() {
  std::array<Card, 52> cards;
  int i = 0;
  for (uint8_t suit : kSuits) {
    for (uint16_t value : kValues) {
      cards[i++] = Card{value, suit};
    }
  }
  return cards;
}

int main(int argc, char *argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  return 0;
}
