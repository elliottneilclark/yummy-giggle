#include "core/hand.h"

#include <cmath>
#include <cstdint>
#include <iostream>

#include "utils/bits.h"

namespace yg {

using std::log2;
using std::endl;
using std::ostream;
using std::cout;
using std::unordered_map;
using std::array;
using std::string;

constexpr auto kStraightFlush = 1ul << 63;
constexpr auto kFourOfAKind = 1ul << 62;
constexpr auto kFullHouse = 1ul << 61;
constexpr auto kFlush = 1ul << 60;
constexpr auto kStraight = 1ul << 59;
constexpr auto kThreeOfAKind = 1ul << 58;
constexpr auto kTwoPair = 1ul << 57;
constexpr auto kOnePair = 1ul << 56;
constexpr auto kHighCard = 1ul << 55;
Hand::Hand() : cards_(), computed_rank_(-1) {}

Hand::Hand(const Hand &rhs)
    : cards_(rhs.cards_), computed_rank_(rhs.computed_rank_) {}

void Hand::add_card(Card c) { cards_.push_back(c); }

void Hand::clear() {
  computed_rank_ = -1;
  cards_.clear();
}

int64_t Hand::rank() const {
  if (computed_rank_ == -1) {
    computed_rank_ = compute_rank();
  }
  return computed_rank_;
}

int64_t Hand::compute_rank() const { return Bits::popcnt(uint32_t{0}); }

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
