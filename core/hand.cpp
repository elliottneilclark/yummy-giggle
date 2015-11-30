#include "core/hand.h"

#include <cstdint>
#include <array>
#include <cmath>
#include <iostream>

#include "folly/Bits.h"
#include "folly/Likely.h"

namespace yg {

using std::log2;
using std::endl;
using std::ostream;
using std::cout;
using std::unordered_map;
using std::array;

// These are 10x the acutal bases in order to
// ensure that things don't overlap
const array<int, 9> kBase = {
    /* Straight Flush   0 = */ 0,
    /* Four of a Kind   1 = */ 10,
    /* Full Houses      2 = */ 1660,
    /* Flush            3 = */ 3220,
    /* Straight         4 = */ 15990,
    /* Three of a Kind  5 = */ 16090,
    /* Two Pair         6 = */ 246700,
    /* One Pair         7 = */ 332500,
    /* High Card        8 = */ 618500,
};

void Hand::add_card(Card c) { cards_[next_slot_++] = c; }

int Hand::rank() const {
  uint16_t values = 0;
  for (auto const &c : cards_) {
    values |= c.value();
  }

  bool has_flush = is_flush();
  int distinct = folly::popcount(values);

  if (LIKELY(distinct == 5)) {
    int s_rank = straight_rank(values, has_flush);
    if (s_rank >= 0) {
      return s_rank;
    }
    // If we already know its a flush then no need to count the cards.
    if (has_flush) {
      return kBase[3] + remaining_rank(values, 12);
    }

    // Can't be anything other than a high card.
    return kBase[8] + remaining_rank(values, 12);
  }

  unordered_map<uint8_t, uint16_t> counts = count_cards();
  auto four = counts.find(4);
  if (UNLIKELY(four != counts.end())) {
    // Four of a kind.
    return kBase[1] + remaining_rank(four->second, 12) +
           remaining_rank(values - four->second, 1);
  }

  auto three = counts.find(3);
  if (three != counts.end()) {
    auto two = counts.find(2);
    int three_rank = log2(three->second);
    if (UNLIKELY(two != counts.end())) {
      // full house.
      int two_rank = log2(two->second);
      return kBase[2] + (12 * three_rank) + (11 * two_rank) +
             remaining_rank(values - three->second - two->second, 1);
    }
    return kBase[5] + (12 * three_rank) +
           remaining_rank(values - three->second, 11);
  }

  auto two = counts.find(2);
  if (UNLIKELY(folly::popcount(two->second) == 2)) {
    // two pair
    //
    // Need to make sure that the two values of the
    // two pair are the most signifigant.
    return kBase[6] + remaining_rank(two->second, 12) +
           remaining_rank(values - two->second, 1);
  }

  return kBase[7] + (12 * log2(two->second)) +
         remaining_rank(values - two->second, 11);
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
    if (result == values) {
      // Found a straight
      return (has_flush ? 0 : kBase[4]) + shift;
    }
  }
  // Need to check for the wheel
  mask = kAce | kTwo | kThree | kFour | kFive;
  uint16_t result = mask & values;
  if (folly::popcount(result) == 5) {
    return (has_flush ? 0 : kBase[4]) + 9;
  }
  return -1;
}

/**
 * Creates a map of
 *
 * count -> card
 *
 * if there are two cards with the same count then the
 * cards will be or'd together.
 */
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

/**
 * Returns a rank based on card ranks.
 */
int Hand::remaining_rank(uint16_t values, int base_rank) const {
  int rank = 0;
  int shift = 0;
  while (values > 0) {
    uint16_t mask = (kAce >> shift);
    uint16_t result = values & mask;
    if (result) {
      values -= mask;
      rank += (shift * base_rank);
      base_rank--;
    }
    shift++;
  }
  return rank;
}

ostream &operator<<(::std::ostream &os, const Hand &hand) {
  return os << hand.cards_[0] << hand.cards_[1] << hand.cards_[2]
            << hand.cards_[3] << hand.cards_[4] 
            << "[" << hand.rank() << "]";
}

} // namespace yg
