#include <array>
#include <iostream>
#include <folly/Benchmark.h>
#include <ctime>

#include "core/card.h"
#include "core/hand.h"
#include "core/choose_hand.h"

using namespace yg;
using namespace folly;
using namespace std;

int64_t rankFive(const array<Card, 52> &cards) {
  Hand h;
  int64_t best_rank = 1l << 20;
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
            best_rank = min(best_rank, h.rank());
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
  return best_rank;
}

int64_t rankSeven(const array<Card, 52> &cards) {
  ChooseHand ch;
  int64_t best_rank = 1l << 20;
  for (uint a = 0 + 0; a < 52; a++) {
    ch.add_card(cards[a]);
    for (uint b = a + 1; b < 52; b++) {
      ch.add_card(cards[b]);
      for (uint c = b + 1; c < 52; c++) {
        ch.add_card(cards[c]);
        for (uint d = c + 1; d < 52; d++) {
          ch.add_card(cards[d]);
          for (uint e = d + 1; e < 52; e++) {
            ch.add_card(cards[e]);
            for (uint f = e + 1; f < 52; f++) {
              ch.add_card(cards[f]);
              for (uint g = f + 1; g < 52; g++) {
                ch.add_card(cards[g]);
                best_rank = min(best_rank, ch.best_hand()->rank());
                ch.remove_last();
              }
              ch.remove_last();
            }
            ch.remove_last();
          }
          ch.remove_last();
        }
        ch.remove_last();
      }
      ch.remove_last();
    }
    ch.remove_last();
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

BENCHMARK(rankFive) { doNotOptimizeAway(rankFive(make_cards())); }
BENCHMARK_RELATIVE(rankSeven) { doNotOptimizeAway(rankSeven(make_cards())); }

int main(int argc, char *argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  runBenchmarks();
  return 0;
}
