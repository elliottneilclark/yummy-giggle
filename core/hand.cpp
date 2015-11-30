#include "core/hand.h"
#include "folly/Bits.h"
#include "folly/Likely.h"

#include <cstdint>
#include <array>
#include <cmath>
#include <iostream>

using namespace std;
using namespace folly;

const array<int, 9> kOccur = {
    /* Straight Flush	*/ 10,
    /* Four of a Kind */ 156,
    /* Full Houses */ 156,
    /* Flush */ 1277,
    /* Straight */ 10,
    /* Three of a Kind */ 858,
    /* Two Pair */ 858,
    /* One Pair */ 2860,
    /* High Card */ 1277,
};

const array<int, 9> kBase = {
    /* Straight Flush	 0 = */ 0,
    /* Four of a Kind  1 = */ 10,
    /* Full Houses     2 = */ 166,
    /* Flush           3 = */ 322,
    /* Straight        4 = */ 1599,
    /* Three of a Kind 5 = */ 1609,
    /* Two Pair        6 = */ 2467,
    /* One Pair        7 = */ 3325,
    /* High Card       8 = */ 6185,
};

void Hand::add_card(Card c) { cards_.push_back(c); }

int Hand::rank() const {
  uint16_t values = 0;
  for (auto const &c : cards_) {
    values |= c.value();
  }

  bool has_flush = is_flush();
  int distinct = popcount(values);

  if (LIKELY(distinct == 5)) {
    int s_rank = straight_rank(values, has_flush);
    if (s_rank >= 0) {
      return s_rank;
    }
    // If we already know its a flush then no need to count the cards.
    if (has_flush) {
      return kBase[3];
    }

    // Can't be anything other than a high card.
    return kBase[8];
  }

  unordered_map<uint8_t, uint16_t> counts = count_cards();
  auto four = counts.find(4);
  if (UNLIKELY(four != counts.end())) {
    // Four of a kind.
    int card_rank = 12 - log2(four->second);
    int four_rank =  (12 * card_rank); 
    return kBase[1] + four_rank;
  }

  auto three = counts.find(3);
  auto two = counts.find(2);
  if (three != counts.end()) {
    if (two != counts.end()) {
      // full house.
      return kBase[2];
    }
    return kBase[5];
  }

  if (two != counts.end()) {
    if (UNLIKELY(popcount(two->second) == 2)) {
      // two of a kind.
      return kBase[6];
    }
    return kBase[7];
  }

  return -1;
}

bool Hand::is_flush() const {
  uint8_t suits = 0;
  for (auto const &c : cards_) {
    suits |= c.suit();
  }
  return folly::popcount(suits) == 1;
}

int Hand::straight_rank(uint16_t values, bool has_flush) const {
  // High card or a straight
  uint16_t mask = kAce | kKing | kQueen | kJack | kTen;
  for (uint16_t shift = 0; shift < 9; shift++) {
    uint16_t result = (mask >> shift) & values;
    if (popcount(result) == 5) {
      // Found a straight
      cout << " Found non wheel straight has_flush = " << has_flush << endl;
      return (has_flush ? 0 : kBase[4]) + shift;
    }
  }
  // Need to check for the wheel
  mask = kAce | kTwo | kThree | kFour | kFive;
  uint16_t result = mask & values;
  if (popcount(result) == 5) {
    return (has_flush ? 0 : kBase[4]) + 9;
  }
  return -1;
}

unordered_map<uint8_t, uint16_t> Hand::count_cards() const {
  unordered_map<uint16_t, uint8_t> c_count;
  for (auto c : cards_) {
    auto l = c_count.find(c.value());
    if (l == c_count.end()) {
      c_count[c.value()] = 1;
    } else {
      l->second += 1;
    }
  }

  // Now rotate the map
  unordered_map<uint8_t, uint16_t> result;
  for (auto const &it : c_count) {
    if (result.find(it.second) == result.end()) {
      result[it.second] = it.first;
    } else {
      result[it.second] |= it.first;
    }
  }

  return result;
}
