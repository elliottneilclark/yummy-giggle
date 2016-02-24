#include "core/hand.h"

#include <cstdint>
#include <array>
#include <cmath>
#include <iostream>

#include "folly/Bits.h"
#include "folly/Benchmark.h"
#include "folly/Likely.h"

namespace yg {

using std::log2;
using std::endl;
using std::ostream;
using std::cout;
using std::unordered_map;
using std::array;
using std::string;
using folly::popcount;

constexpr array<int64_t, 9> kBase = {
    /* Straight Flush   0 = */ 0,
    /* Four of a Kind   1 = */ 1ul << 53,
    /* Full Houses      2 = */ 1ul << 54,
    /* Flush            3 = */ 1ul << 55,
    /* Straight         4 = */ 1ul << 56,
    /* Three of a Kind  5 = */ 1ul << 57,
    /* Two Pair         6 = */ 1ul << 58,
    /* One Pair         7 = */ 1ul << 59,
    /* High Card        8 = */ 1ul << 60,
};
Hand::Hand() : next_slot_(0), computed_rank_(-1) {}

Hand::Hand(const Hand &rhs)
    : next_slot_(rhs.next_slot_), computed_rank_(rhs.computed_rank_),
      cards_(rhs.cards_) {}

void Hand::add_card(Card c) { cards_[next_slot_++] = c; }

void Hand::clear() {
  computed_rank_ = -1;
  next_slot_ = 0;
}

void Hand::remove_last() {
  computed_rank_ = -1;
  next_slot_--;
}

int64_t Hand::rank() const {
  if (computed_rank_ == -1) {
    computed_rank_ = compute_rank();
  }
  return computed_rank_;
}
int64_t Hand::compute_rank() const {
  uint16_t values = 0;
  for (auto const &c : cards_) {
    values |= c.value();
  }

  bool has_flush = is_flush();
  int distinct = popcount(values);

  if (LIKELY(distinct == 5)) {
    int64_t s_rank = straight_rank(values, has_flush);
    if (s_rank >= 0) {
      return s_rank;
    }
    int64_t hand_rank = (static_cast<int64_t>(kAce) << 1) - values;
    // If we already know its a flush then no need to count the cards.
    // Otherwise it has to be a high card only
    return (has_flush ? kBase[3] : kBase[8]) + hand_rank;
  }

  unordered_map<uint8_t, uint16_t> counts = count_cards();
  auto four = counts.find(4);
  if (UNLIKELY(four != counts.end())) {
    // Four of a kind.
    return kBase[1] + ((kAce - four->second) << 16) +
           (kAce - (values - four->second));
  }

  auto three = counts.find(3);
  if (UNLIKELY(three != counts.end())) {
    auto two = counts.find(2);
    uint64_t three_rank = static_cast<uint64_t>(kAce - three->second);
    if (UNLIKELY(two != counts.end())) {
      // full house.
      uint64_t two_rank = static_cast<uint64_t>(kAce - two->second);
      return kBase[2] + (three_rank << 16) + (two_rank);
    }
    return kBase[5] + (three_rank << 16) +
           ((kAce | kKing) - (values - three->second));
  }

  auto two = counts.find(2);
  if (UNLIKELY(popcount(two->second) == 2)) {
    // two pair
    //
    // Need to make sure that the two values of the
    // two pair are the most signifigant.
    return kBase[6] + (((kAce | kKing) - two->second) << 16) +
           (kAce - (values - two->second));
  }

  return kBase[7] + ((kAce - two->second) << 16) +
         ((kAce | kKing | kQueen) - (values - two->second));
}

bool Hand::is_flush() const {
  uint8_t suits = 0;
  for (auto const &c : cards_) {
    suits |= c.suit();
  }
  return popcount(suits) == 1;
}

int64_t Hand::straight_rank(uint16_t values, bool has_flush) const {
  // High card or a straight
  uint16_t mask = kAce | kKing | kQueen | kJack | kTen;
  for (uint16_t shift = 0; shift < 9; shift++) {
    uint16_t masked = (mask >> shift) & values;
    if (masked == values) {
      // Found a straight
      int64_t result = (has_flush ? 0l : kBase[4]) + shift;
      return result;
    }
  }
  // Need to check for the wheel
  mask = kAce | kTwo | kThree | kFour | kFive;
  uint16_t masked = mask & values;
  if (masked == values) {
    int64_t result = (has_flush ? 0l : kBase[4]) + 9;
    return result;
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
  for (const auto c : cards_) {
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

bool Hand::operator<(const Hand &rhs) const { return rank() < rhs.rank(); }

bool Hand::operator==(const Hand &rhs) const { return rank() == rhs.rank(); }

string Hand::card_str() const {
  return cards_[0].str() + cards_[1].str() + cards_[2].str() + cards_[3].str() +
         cards_[4].str();
}

ostream &operator<<(ostream &os, const Hand &hand) {
  return os << hand.card_str() << "[" << hand.rank() << "]";
}

} // namespace yg
