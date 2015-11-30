#include "core/hand.h"

#include <array>
#include <iostream>

#include "core/card.h"

using namespace yg;
using namespace std;

int main (int argc, char *argv[]) {
  std::array<Card, 52> cards = {};
  int i = 0;
  for (uint8_t suit : kSuits) {
    for (uint16_t value : kValues) {
      cards[i++] = Card{value, suit};
    }
  }

  for (uint a = 0; a < cards.size(); a++) {
    for (uint b = a + 1; b < cards.size(); b++) {
      for (uint c = b + 1; c < cards.size(); c++) {
        for (uint d = c + 1; d < cards.size(); d++) {
          for (uint e = d + 1; e < cards.size(); e++) {
            Hand h;

            h.add_card(cards[a]);
            h.add_card(cards[b]);
            h.add_card(cards[c]);
            h.add_card(cards[d]);
            h.add_card(cards[e]);

            cout << h << "\n";
          }
        }
      }
    }
  }
}
