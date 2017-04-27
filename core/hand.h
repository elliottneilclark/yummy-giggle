#pragma once

#include <boost/optional.hpp>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "core/card.h"

namespace yg {

constexpr auto kStraightFlush = 1ul << 63;
constexpr auto kFourOfAKind = 1ul << 62;
constexpr auto kFullHouse = 1ul << 61;
constexpr auto kFlush = 1ul << 60;
constexpr auto kStraight = 1ul << 59;
constexpr auto kThreeOfAKind = 1ul << 58;
constexpr auto kTwoPair = 1ul << 57;
constexpr auto kOnePair = 1ul << 56;
constexpr auto kHighCard = 1ul << 55;

class Hand {
 public:
  Hand();
  Hand(const std::string& str);
  Hand(const Hand &rhs);
  void AddCard(Card c);
  void RemoveLast();
  void Clear();
  uint64_t Rank() const;
  int size() const { return cards_.size(); }
  friend std::ostream &operator<<(::std::ostream &os, const Hand &hand);
  bool operator<(const Hand &rhs) const;
  bool operator>(const Hand &rhs) const;
  bool operator<=(const Hand &rhs) const;
  bool operator>=(const Hand &rhs) const;
  bool operator==(const Hand &rhs) const;

 private:
  std::string str() const;
  uint64_t ComputeRank() const;
  std::vector<Card> cards_;
  mutable boost::optional<uint64_t> computed_rank_;
};

std::ostream &operator<<(::std::ostream &os, const Hand &hand);

}  // namespace yg
