#include "core/hand.h"

#include <bitset>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>

#include <glog/logging.h>

#include "utils/bits.h"

namespace yg {

using std::log2;
using std::endl;
using std::ostream;
using std::cout;
using std::unordered_map;
using std::array;
using std::string;

constexpr std::uint16_t kWheel =
    (1 << kAce) | (1 << kTwo) | (1 << kThree) | (1 << kFour) | (1 << kFive);

Hand::Hand() : cards_(), computed_rank_(boost::none) {}

Hand::Hand(const std::string &str) : cards_(), computed_rank_(boost::none) {
  auto it = str.begin();
  while (it != str.end()) {
    auto first = *(it++);
    auto second = *(it++);
    AddCard(Card{first, second});
  }
}

Hand::Hand(const Hand &rhs)
    : cards_(rhs.cards_), computed_rank_(rhs.computed_rank_) {}

void Hand::AddCard(Card c) { cards_.push_back(c); }

void Hand::Clear() {
  computed_rank_ = -1;
  cards_.clear();
}

uint64_t Hand::Rank() const {
  if (!computed_rank_) {
    computed_rank_ = ComputeRank();
  }
  return *computed_rank_;
}

boost::optional<std::uint64_t> FindFlush(
    const std::array<std::uint16_t, 4> &suit_to_count) {
  for (int i = 0; i < 4; i++) {
    if (suit_to_count[i] >= 5) {
      return i;
    }
  }
  return boost::none;
}

boost::optional<std::uint64_t> RankStraight(std::uint16_t vmap) {
  auto left = vmap & (vmap << 1) & (vmap << 2) & (vmap << 3) & (vmap << 4);
  auto idx = Bits::clz(static_cast<std::uint16_t>(left));
  if (idx < 16) {
    return 16 - idx - 4;
  } else if ((vmap & kWheel) == kWheel) {
    return 1;
  }
  return boost::none;
}

uint64_t Hand::ComputeRank() const {
  auto value_to_count = std::array<std::uint8_t, 13>{0};
  auto count_to_vmap = std::array<std::uint16_t, 5>{0};
  auto suit_to_count = std::array<std::uint16_t, 4>{0};
  auto suit_to_vmap = std::array<std::uint16_t, 4>{0};
  auto vmap = std::uint16_t{0};

  for (const Card &c : cards_) {
    value_to_count[c.value()] += 1;
    suit_to_vmap[c.suit()] |= 1 << c.value();
    suit_to_count[c.suit()] += 1;
    vmap |= 1 << c.value();
  }

  for (auto it = value_to_count.begin(); it != value_to_count.end(); it++) {
    auto count = *it;
    // no need to keep track of the cards that
    // aren't in the hand. This is preformance improvement.
    if (count == 0) {
      continue;
    }
    auto value = std::distance(value_to_count.begin(), it);
    count_to_vmap[count] |= 1 << value;
  }

  // Check to see if there is a flush
  auto flush = FindFlush(suit_to_count);

  if (flush) {
    if (auto straight_rank = RankStraight(suit_to_vmap[*flush])) {
      return kStraightFlush | *straight_rank;
    }
    return kFlush | Bits::KeepNHighest(suit_to_vmap[*flush], 5);
  }

  // Check if there are four of a kind.
  if (count_to_vmap[4] != 0) {
    auto card = count_to_vmap[4];
    auto other = Bits::KeepHighest(vmap ^ count_to_vmap[4]);
    return kFourOfAKind | card << 13 | other;
  }

  // If we have two sets then we can have a full house.
  if (count_to_vmap[3] != 0 && Bits::popcnt(count_to_vmap[3]) >= 2) {
    // If we have two sets then a full house is the best we can do.
    auto set_card = Bits::KeepHighest(count_to_vmap[3]);
    auto pair = count_to_vmap[3] ^ set_card;
    return kFullHouse | set_card << 13 | pair;
  }
  // It's also possible to have a normal full house. So check for that.
  if (count_to_vmap[3] != 0 && count_to_vmap[2] != 0) {
    // This is the normal full house.
    // Keep the set
    // Then keep the highest pair.
    return kFullHouse | count_to_vmap[3] << 13 |
           Bits::KeepHighest(count_to_vmap[2]);
  }

  // Check to see if we have a straight.
  if (auto straight_rank = RankStraight(vmap)) {
    // This is a straight.
    return kStraight | *straight_rank;
  }

  // Do we have three of a kind ?
  if (count_to_vmap[3] != 0) {
    // Three of a kind.
    // Keep the set
    // Keep the highest cards other than the set.
    return kThreeOfAKind | count_to_vmap[3] << 13 |
           Bits::KeepNHighest(vmap ^ count_to_vmap[3], 2);
  }

  // If we have at least a pair then determine if we have two pair.
  if (count_to_vmap[2] != 0) {
    // If there are any pairs then it's either a single pair or
    // two pair.
    if (Bits::popcnt(count_to_vmap[2]) >= 2) {
      // Two pair
      // Keep the two highest pair
      // Keep the highest other card.
      auto two_pair = Bits::KeepNHighest(count_to_vmap[2], 2);
      auto other = Bits::KeepHighest(vmap ^ two_pair);
      return kTwoPair | two_pair << 13 | other;
    } else {
      return kOnePair | count_to_vmap[2] << 13 |
             Bits::KeepNHighest(vmap ^ count_to_vmap[2], 3);
    }
  }

  // Otherwise this is only the highest cards.
  return kHighCard | Bits::KeepNHighest(vmap, 5);
}

bool Hand::operator<(const Hand &rhs) const { return Rank() < rhs.Rank(); }
bool Hand::operator<=(const Hand &rhs) const { return Rank() <= rhs.Rank(); }
bool Hand::operator>(const Hand &rhs) const { return Rank() > rhs.Rank(); }
bool Hand::operator>=(const Hand &rhs) const { return Rank() >= rhs.Rank(); }
bool Hand::operator==(const Hand &rhs) const { return Rank() == rhs.Rank(); }

string Hand::str() const {
  return cards_[0].str() + cards_[1].str() + cards_[2].str() + cards_[3].str() +
         cards_[4].str();
}

ostream &operator<<(ostream &os, const Hand &hand) {
  return os << hand.str() << "[" << hand.Rank() << "]";
}

}  // namespace yg
